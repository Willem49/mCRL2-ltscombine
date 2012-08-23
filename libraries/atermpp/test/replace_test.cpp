// Author(s): Wieger Wesselink
// Copyright: see the accompanying file COPYING or copy at
// https://svn.win.tue.nl/trac/MCRL2/browser/trunk/COPYING
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
/// \file replace_test.cpp
/// \brief Add your file description here.

#include <iostream>
#include <iterator>
#include <boost/test/minimal.hpp>

#include "mcrl2/atermpp/algorithm.h"
#include "mcrl2/atermpp/aterm_init.h"
#include "mcrl2/atermpp/aterm_appl.h"
#include "mcrl2/atermpp/aterm_list.h"
#include "mcrl2/atermpp/vector.h"
#include "mcrl2/atermpp/utility.h"

using namespace std;
using namespace atermpp;

// function object to test if it is an aterm_appl with function symbol "f"
struct is_f
{
  bool operator()(aterm_appl t) const
  {
    return t.function().name() == "f";
  }
};

// function object to test if it is an aterm_appl with function symbol "a" or "b"
struct is_a_or_b
{
  bool operator()(aterm_appl t) const
  {
    return t.function().name() == "a" || t.function().name() == "b";
  }
};

// replaces function names f by g and vice versa
struct fg_replacer
{
  aterm_appl operator()(aterm_appl t) const
  {
    if (t.function().name() == "f")
    {
      return aterm_appl(function_symbol("g", t.function().arity()), aterm_list(t.begin(), t.end()));
    }
    else if (t.function().name() == "g")
    {
      return aterm_appl(function_symbol("f", t.function().arity()), aterm_list(t.begin(), t.end()));
    }
    else
    {
      return t;
    }
  }
};

// replaces function names f by g and vice versa, but stops the recursion once an f or g term is found
struct fg_partial_replacer
{
  std::pair<aterm_appl, bool> operator()(aterm_appl t) const
  {
    if (t.function().name() == "f")
    {
      return std::make_pair(aterm_appl(function_symbol("g", t.function().arity()), aterm_list(t.begin(), t.end())), false);
    }
    else if (t.function().name() == "g")
    {
      return std::make_pair(aterm_appl(function_symbol("f", t.function().arity()), aterm_list(t.begin(), t.end())), false);
    }
    else
    {
      return std::make_pair(t, true);
    }
  }
};

void test_find()
{
  aterm_appl a = make_term("h(g(x),f(y),p(a(x,y),q(f(z))))");

  aterm_appl t = find_if(a, is_f());
  BOOST_CHECK(t == make_term("f(y)"));

  atermpp::vector<aterm_appl> v;
  find_all_if(a, is_f(), back_inserter(v));
  BOOST_CHECK(v.front() == make_term("f(y)"));
  BOOST_CHECK(v.back() == make_term("f(z)"));
}

void test_replace()
{
  BOOST_CHECK(replace(make_term("x"), make_term("x"), make_term("f(a)")) == make_term("f(a)"));
  BOOST_CHECK(replace(make_term("x"), make_term("x"), make_term("f(x)")) == make_term("f(x)"));
  BOOST_CHECK(replace(make_term("[x]"), make_term("x"), make_term("f(x)")) == make_term("[f(x)]"));

  aterm_appl a = make_term("f(f(x))");
  aterm_appl b = replace(a, make_term("f(x)"), make_term("x"));
  BOOST_CHECK(b == make_term("f(x)"));

  atermpp::aterm f = make_term("[]");
  aterm_appl g = replace(f, a, b);
  BOOST_CHECK(f == make_term("[]"));
  BOOST_CHECK(f == g);

  atermpp::aterm x = make_term("g(f(x),f(y),h(f(x)))");
  atermpp::aterm y = replace(x, fg_replacer());

  BOOST_CHECK(y == make_term("f(f(x),f(y),h(f(x)))"));
}

int test_main(int argc, char* argv[])
{
  MCRL2_ATERMPP_INIT(argc, argv)

  test_find();
  test_replace();

  return 0;
}
