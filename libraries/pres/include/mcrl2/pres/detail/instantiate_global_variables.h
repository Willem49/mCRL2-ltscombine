// Author(s): Jan Friso Groote. Based on pbes/detail/instantiate_global_variables.h by Wieger Wesselink
// Copyright: see the accompanying file COPYING or copy at
// https://github.com/mCRL2org/mCRL2/blob/master/COPYING
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
/// \file mcrl2/pres/detail/instantiate_global_variables.h
/// \brief add your file description here.

#ifndef MCRL2_PRES_DETAIL_INSTANTIATE_GLOBAL_VARIABLES_H
#define MCRL2_PRES_DETAIL_INSTANTIATE_GLOBAL_VARIABLES_H

#include "mcrl2/data/representative_generator.h"
#include "mcrl2/pres/replace.h"

namespace mcrl2
{

namespace pres_system
{

namespace detail
{

/// \brief Applies a global variable substitution to a PRES.
inline
void replace_global_variables(pres& p, const data::mutable_map_substitution<>& sigma)
{
  pres_system::replace_free_variables(p.equations(), sigma);
  p.initial_state() = pres_system::replace_free_variables(p.initial_state(), sigma);
  p.global_variables().clear();
}

/// \brief Eliminates the global variables of a PRES, by substituting
/// a constant value for them. If no constant value is found for one of the variables,
/// an exception is thrown.
inline
data::mutable_map_substitution<> instantiate_global_variables(pres& p)
{
  data::mutable_map_substitution<> sigma;

  if (p.global_variables().empty())
  {
    return sigma;
  }

  data::representative_generator default_expression_generator(p.data());
  std::set<data::variable> to_be_removed;
  for (const data::variable& v: p.global_variables())
  {
    data::data_expression d = default_expression_generator(v.sort());
    if (!d.defined())
    {
      throw mcrl2::runtime_error("Error in pres::instantiate_global_variables: could not instantiate " + data::pp(v));
    }
    sigma[v] = d;
    to_be_removed.insert(v);
  }

  mCRL2log(log::debug) << "instantiating global PRES variables " << sigma << std::endl;
  replace_global_variables(p, sigma);

  return sigma;
}

} // namespace detail

} // namespace pres_system

} // namespace mcrl2

#endif // MCRL2_PRES_DETAIL_INSTANTIATE_GLOBAL_VARIABLES_H
