//  Author(s): Jeroen van der Wulp
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  LICENSE_1_0.txt)
//
/// \file tipi/detail/command_line_interface.hpp

#ifndef TIPI_COMMAND_LINE_INTERFACE_H
#define TIPI_COMMAND_LINE_INTERFACE_H

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

#include "tipi/tool.hpp"
#include "tipi/detail/schemes.hpp"

/// \cond INTERNAL_DOCS
namespace tipi {

  namespace messaging {
    template < typename M >
    class scheme;
  }

  namespace command_line_interface {

    /** \brief Convenience type for hiding boost shared pointers */
    typedef boost::shared_ptr < tipi::messaging::scheme< tipi::message > > scheme_ptr;

    /**
     * \brief Class used for extraction of protocol related command line arguments
     *
     * This class provides functionality to extract protocol specific arguments
     * from the list of command line arguments that a tool receives.
     **/
    class argument_extractor : public boost::noncopyable {
      private:

        /** \brief The list of known of options */
        static const char*  known_options[];

        /** \brief The list of known of schemes */
        static const char*  known_schemes[];

        /** \brief The number of options in known_options[] */
        static const size_t known_option_number;

        /** \brief The number of schemes in known_schemes[] */
        static const size_t known_scheme_number;

        /** \brief The number of the last matched known_option or known_scheme. */
        size_t              last_matched;

        /** \brief the scheme that was last parsed successfully */
        scheme_ptr          selected_scheme;

        /** \brief A unique number that identifies this instance */
        long int            identifier;

      private:

        /** \brief Parses a minimum prefix of argument to search for a known option */
        char* parse_option(char* const);

        /** \brief Parses a minimum prefix of argument to search for a known scheme */
        char* parse_scheme(char* const);

      public:

        /** \brief Constructor that performs extraction */
        argument_extractor(int&, char** const);

        /** \brief Constructor that performs extraction (unparsed command line) */
        argument_extractor(char*);

        /** \brief Removes protocol specific options and adjusts the argument count */
        void process(int&, char** const);

        /** \brief Get the arguments for the selected scheme */
        scheme_ptr get_scheme() const;

        /** \brief Get the identifier */
        long get_identifier() const;
    };

    /** Constructor */
    inline argument_extractor::argument_extractor(int& argc, char** const argv) : identifier(-1) {
      process(argc, argv);
    }
  }
}
/// \endcond
#endif
