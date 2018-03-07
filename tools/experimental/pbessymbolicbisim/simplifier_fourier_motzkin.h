// Author(s): Thomas Neele
// Copyright: see the accompanying file COPYING or copy at
// https://svn.win.tue.nl/trac/MCRL2/browser/trunk/COPYING
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
/// \file simplify_dbm.h


#ifndef MCRL2_LPSSYMBOLICBISIM_SIMPLIFIER_FOURIER_MOTZKIN_H
#define MCRL2_LPSSYMBOLICBISIM_SIMPLIFIER_FOURIER_MOTZKIN_H

#include "mcrl2/data/detail/linear_inequalities_utilities.h"

#include "simplifier.h"
#include "simplifier_finite_domain.h"

namespace mcrl2
{
namespace data
{

class simplifier_fourier_motzkin : public simplifier
{
  typedef simplifier super;
  using super::rewr;
  using super::proving_rewr;

protected:
  simplifier_finite_domain simpl_discr;

  data_expression simplify_expression(const data_expression& expr)
  {
    // Split the expression into two equally sized lists of
    // expressions over real numbers and expressions over other
    // data sorts.
    std::vector < data_expression_list > real_conditions;
    std::vector < data_expression > non_real_conditions;
    detail::split_condition(expr, real_conditions, non_real_conditions);

    data_expression result = sort_bool::false_();
    for(uint32_t i = 0; i < real_conditions.size(); i++)
    {
      std::vector< linear_inequality > linear_inequalities;
      for(const data_expression& d: real_conditions[i])
      {
        linear_inequalities.emplace_back(d, rewr);
      }
      std::vector< linear_inequality > resulting_inequalities;
      remove_redundant_inequalities(linear_inequalities, resulting_inequalities, rewr);

      // If the resulting list of inequalities is false, we don't add it
      // to the result (which is a disjunction).
      if(!(resulting_inequalities.size() == 1 && resulting_inequalities[0].is_false(rewr)))
      {
        data_expression real_con = sort_bool::true_();
        for(uint32_t j = 0; j < resulting_inequalities.size(); j++)
        {
          real_con = lazy::and_(real_con, resulting_inequalities[j].transform_to_data_expression());
        }
        result = lazy::or_(result, lazy::and_(simpl_discr.apply(non_real_conditions[i]), real_con));
      }
    }

    return result;
  }

public:
  simplifier_fourier_motzkin(const rewriter& r, const rewriter& pr, const data_specification& dataspec_)
  : super(r, pr)
  , simpl_discr(r, pr, dataspec_)
  {}

};


} // namespace mcrl2
} // namespace data

#endif // MCRL2_LPSSYMBOLICBISIM_SIMPLIFIER_FOURIER_MOTZKIN_H