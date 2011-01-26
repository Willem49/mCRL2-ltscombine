// Author(s): Wieger Wesselink
// Copyright: see the accompanying file COPYING or copy at
// https://svn.win.tue.nl/trac/MCRL2/browser/trunk/COPYING
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
/// \file mcrl2/data/normalize_sorts.h
/// \brief add your file description here.

#ifndef MCRL2_DATA_NORMALIZE_SORTS_H
#define MCRL2_DATA_NORMALIZE_SORTS_H

#include <functional>
#include "mcrl2/data/builder.h"

namespace mcrl2 {

namespace data {

  // Prototype.
  class data_specification;

  // The implementation of this function can be found in mcrl2/data/detail/normalize_sorts_implementation.h
  template <typename T>
  void normalize_sorts(T& x,
                       const data::data_specification& data_spec,
                       typename boost::disable_if<typename boost::is_base_of<atermpp::aterm_base, T>::type>::type* = 0
                      );

  template <typename T>
  T normalize_sorts(const T& x,
                    const data::data_specification& data_spec,
                    typename boost::enable_if<typename boost::is_base_of<atermpp::aterm_base, T>::type>::type* = 0
                   );

} // namespace data

} // namespace mcrl2

#endif // MCRL2_DATA_NORMALIZE_SORTS_H
