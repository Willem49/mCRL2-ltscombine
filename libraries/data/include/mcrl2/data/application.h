// Author(s): Jeroen Keiren
// Copyright: see the accompanying file COPYING or copy at
// https://svn.win.tue.nl/trac/MCRL2/browser/trunk/COPYING
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
/// \file mcrl2/data/application.h
/// \brief The class application.

#ifndef MCRL2_DATA_APPLICATION_H
#define MCRL2_DATA_APPLICATION_H

#include "mcrl2/atermpp/aterm_appl.h"
#include "mcrl2/atermpp/aterm_list.h"
#include "mcrl2/atermpp/aterm_traits.h"
#include "mcrl2/atermpp/vector.h"
#include "mcrl2/data/utility.h"
#include "mcrl2/core/detail/constructors.h"
#include "mcrl2/data/data_expression.h"

namespace mcrl2 {
  
  namespace data {

    /// \brief function symbol.
    ///
    class application: public data_expression
    {
      protected:
        data_expression_list m_arguments; ///< The list of arguments of the application.

      public:

        /// \brief Constructor.
        ///
        application()
          : data_expression(core::detail::constructDataAppl())
        {}

        /// \brief Constructor.
        ///
        /// \param[in] d A data expression.
        /// \pre d has the internal structure of an application.
        application(const data_expression& d)
          : data_expression(d),
            m_arguments(atermpp::term_list<data_expression>(atermpp::list_arg2(d)).begin(), atermpp::term_list<data_expression>(atermpp::list_arg2(d)).end())
        {
          assert(d.is_application());
        }

        /// \brief Constructor.
        ///
        /// \param[in] head The data expression that is applied.
        /// \param[in] arguments The data expressions that head is applied to.
        /// \pre head.sort() is a function sort.
        /// \pre arguments is not empty.
        application(const data_expression& head, 
                    const boost::iterator_range<data_expression_list::const_iterator>& arguments)
          : data_expression(core::detail::gsMakeDataAppl(head, atermpp::term_list<data_expression>(arguments.begin(), arguments.end()))),
            m_arguments(arguments.begin(), arguments.end())
        {
          assert(head.sort().is_function_sort());
          assert(!arguments.empty());
        }

        /// \brief Convenience constructor for application with one argument
        ///
        /// \param[in] head The data expression that is applied
        /// \param[in] arg1 The argument head is applied to
        /// \post \this represents head(arg1)
        application(const data_expression& head,
                    const data_expression& arg1)
          : data_expression(core::detail::gsMakeDataAppl(head, atermpp::term_list<data_expression>(atermpp::make_list(arg1)))),
            m_arguments(make_vector(arg1))
        { }

        /// \brief Convenience constructor for application with two arguments
        ///
        /// \param[in] head The data expression that is applied
        /// \param[in] arg1 The first argument head is applied to
        /// \param[in] arg2 The second argument head is applied to
        /// \post \this represents head(arg1, arg2)
        application(const data_expression& head,
                    const data_expression& arg1,
                    const data_expression& arg2)
          : data_expression(core::detail::gsMakeDataAppl(head, atermpp::term_list<data_expression>(atermpp::make_list(arg1, arg2)))),
            m_arguments(make_vector(arg1, arg2))
        { }

        /// \brief Convenience constructor for application with three arguments
        ///
        /// \param[in] head The data expression that is applied
        /// \param[in] arg1 The first argument head is applied to
        /// \param[in] arg2 The second argument head is applied to
        /// \param[in] arg3 The third argument head is applied to
        /// \post \this represents head(arg1, arg2, arg3)
        application(const data_expression& head,
                    const data_expression& arg1,
                    const data_expression& arg2,
                    const data_expression& arg3)
          : data_expression(core::detail::gsMakeDataAppl(head, atermpp::term_list<data_expression>(atermpp::make_list(arg1, arg2, arg3)))),
            m_arguments(make_vector(arg1, arg2, arg3))
        { }

        /* Should be enabled when the implementation in data_expression is
         * removed
        /// \overload
        inline
        sort_expression sort() const
        {
          return static_cast<const function_sort>(head().sort()).codomain();
        }
        */

        /// \brief Returns the head of the application
        inline
        data_expression head() const
        {
          return atermpp::arg1(*this);
        }

        /// \brief Returns the arguments of the application
        inline
        boost::iterator_range<data_expression_list::const_iterator> arguments() const
        {
          return boost::make_iterator_range(m_arguments);
        }

        /// \brief Returns the first argument of the application
        /// \pre head() is a binary operator
        /// \ret arguments()
        inline
        data_expression left() const
        {
          assert(m_arguments.size() == 2);
          return m_arguments[0];
        }

        /// \brief Returns the second argument of the application
        /// \pre head() is a binary operator
        inline
        data_expression right() const
        {
          assert(m_arguments.size() == 2);
          return m_arguments[1];
        }

    }; // class application

    /// \brief list of applications
    ///
    typedef atermpp::vector<application> application_list;

  } // namespace data

} // namespace mcrl2

/// \cond INTERNAL_DOCS
MCRL2_ATERM_TRAITS_SPECIALIZATION(mcrl2::data::application)
/// \endcond

#endif // MCRL2_DATA_APPLICATION_H

