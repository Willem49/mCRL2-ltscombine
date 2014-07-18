// Author(s): Wieger Wesselink
// Copyright: see the accompanying file COPYING or copy at
// https://svn.win.tue.nl/trac/MCRL2/browser/trunk/COPYING
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
/// \file mcrl2/process/untyped_action.h
/// \brief add your file description here.

#ifndef MCRL2_PROCESS_UNTYPED_ACTION_H
#define MCRL2_PROCESS_UNTYPED_ACTION_H

#include "mcrl2/data/data_expression.h"

namespace mcrl2 {

namespace process {

//--- start generated class untyped_action ---//
/// \brief An untyped action
class untyped_action: public atermpp::aterm_appl
{
  public:
    /// \brief Default constructor.
    untyped_action()
      : atermpp::aterm_appl(core::detail::default_values::UntypedAction)
    {}

    /// \brief Constructor.
    /// \param term A term
    explicit untyped_action(const atermpp::aterm& term)
      : atermpp::aterm_appl(term)
    {
      assert(core::detail::check_term_UntypedAction(*this));
    }

    /// \brief Constructor.
    untyped_action(const core::identifier_string& name, const data::data_expression_list& arguments)
      : atermpp::aterm_appl(core::detail::function_symbol_UntypedAction(), name, arguments)
    {}

    /// \brief Constructor.
    untyped_action(const std::string& name, const data::data_expression_list& arguments)
      : atermpp::aterm_appl(core::detail::function_symbol_UntypedAction(), core::identifier_string(name), arguments)
    {}

    const core::identifier_string& name() const
    {
      return atermpp::down_cast<core::identifier_string>((*this)[0]);
    }

    const data::data_expression_list& arguments() const
    {
      return atermpp::down_cast<data::data_expression_list>((*this)[1]);
    }
};

/// \brief list of untyped_actions
typedef atermpp::term_list<untyped_action> untyped_action_list;

/// \brief vector of untyped_actions
typedef std::vector<untyped_action>    untyped_action_vector;

/// \brief Test for a untyped_action expression
/// \param x A term
/// \return True if \a x is a untyped_action expression
inline
bool is_untyped_action(const atermpp::aterm_appl& x)
{
  return x.function() == core::detail::function_symbols::UntypedAction;
}

// prototype declaration
std::string pp(const untyped_action& x);

/// \brief Outputs the object to a stream
/// \param out An output stream
/// \return The output stream
inline
std::ostream& operator<<(std::ostream& out, const untyped_action& x)
{
  return out << process::pp(x);
}

/// \brief swap overload
inline void swap(untyped_action& t1, untyped_action& t2)
{
  t1.swap(t2);
}
//--- end generated class untyped_action ---//

} // namespace process

} // namespace mcrl2

#endif // MCRL2_PROCESS_UNTYPED_ACTION_H
