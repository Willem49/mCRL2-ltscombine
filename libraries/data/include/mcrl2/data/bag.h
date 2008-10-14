#ifndef MCRL2_DATA_BAG_H
#define MCRL2_DATA_BAG_H

#include "mcrl2/data/basic_sort.h"
#include "mcrl2/data/function_sort.h"
#include "mcrl2/data/function_symbol.h"
#include "mcrl2/data/application.h"
#include "mcrl2/data/data_equation.h"
#include "mcrl2/data/utility.h"
#include "mcrl2/data/bool.h"
#include "mcrl2/data/nat.h"
#include "mcrl2/data/set.h"


namespace mcrl2 {

  namespace data {

    namespace sort_bag {

      // Sort expression Bag(s)
      inline
      container_sort bag(const sort_expression& s)
      {
        static container_sort bag("bag", s);
        return bag;
      }

      // Recogniser for sort expression Bag(s)
      inline
      bool is_bag(const sort_expression& e)
      {
        if (e.is_container_sort())
        {
          return static_cast<const container_sort&>(e).name() == "bag";
        }
        return false;
      }

      // Function symbol @bag
      inline
      function_symbol bag_comprehension(const sort_expression& s)
      {
        static function_symbol bag_comprehension("@bag", function_sort(s, bag(s)));
        return bag_comprehension;
      }

      // Recogniser for @bag
      inline
      bool is_bag_comprehension_function_symbol(const data_expression& e)
      {
        if (e.is_function_symbol())
        {
          return static_cast<const function_symbol&>(e).name() == "@bag";
        }
        return false;
      }

      // Application of @bag
      inline
      application bag_comprehension(const sort_expression& s, const data_expression& arg0)
      {
        assert(arg0.sort() == s);
        
        return application(bag_comprehension(s),arg0);
      }

      // Recogniser for application of @bag
      inline
      bool is_bag_comprehension_application(const data_expression& e)
      {
        if (e.is_application())
        {
          return is_bag_comprehension_function_symbol(static_cast<const application&>(e).head());
        }
        return false;
      }

      // Function symbol {}
      inline
      function_symbol emptybag(const sort_expression& s)
      {
        static function_symbol emptybag("{}", bag(s));
        return emptybag;
      }

      // Recogniser for {}
      inline
      bool is_emptybag_function_symbol(const data_expression& e)
      {
        if (e.is_function_symbol())
        {
          return static_cast<const function_symbol&>(e).name() == "{}";
        }
        return false;
      }

      // Function symbol count
      inline
      function_symbol count(const sort_expression& s)
      {
        static function_symbol count("count", function_sort(s, bag(s), nat()));
        return count;
      }

      // Recogniser for count
      inline
      bool is_count_function_symbol(const data_expression& e)
      {
        if (e.is_function_symbol())
        {
          return static_cast<const function_symbol&>(e).name() == "count";
        }
        return false;
      }

      // Application of count
      inline
      application count(const sort_expression& s, const data_expression& arg0, const data_expression& arg1)
      {
        assert(arg0.sort() == s);
        assert(is_bag(arg1.sort()));
        
        return application(count(s),arg0, arg1);
      }

      // Recogniser for application of count
      inline
      bool is_count_application(const data_expression& e)
      {
        if (e.is_application())
        {
          return is_count_function_symbol(static_cast<const application&>(e).head());
        }
        return false;
      }

      // Function symbol in
      inline
      function_symbol in(const sort_expression& s)
      {
        static function_symbol in("in", function_sort(s, bag(s), bool_()));
        return in;
      }

      // Recogniser for in
      inline
      bool is_in_function_symbol(const data_expression& e)
      {
        if (e.is_function_symbol())
        {
          return static_cast<const function_symbol&>(e).name() == "in";
        }
        return false;
      }

      // Application of in
      inline
      application in(const sort_expression& s, const data_expression& arg0, const data_expression& arg1)
      {
        assert(arg0.sort() == s);
        assert(is_bag(arg1.sort()));
        
        return application(in(s),arg0, arg1);
      }

      // Recogniser for application of in
      inline
      bool is_in_application(const data_expression& e)
      {
        if (e.is_application())
        {
          return is_in_function_symbol(static_cast<const application&>(e).head());
        }
        return false;
      }

      // Function symbol <=
      inline
      function_symbol subbag_or_equal(const sort_expression& s)
      {
        static function_symbol subbag_or_equal("<=", function_sort(bag(s), bag(s), bool_()));
        return subbag_or_equal;
      }

      // Recogniser for <=
      inline
      bool is_subbag_or_equal_function_symbol(const data_expression& e)
      {
        if (e.is_function_symbol())
        {
          return static_cast<const function_symbol&>(e).name() == "<=";
        }
        return false;
      }

      // Application of <=
      inline
      application subbag_or_equal(const sort_expression& s, const data_expression& arg0, const data_expression& arg1)
      {
        assert(is_bag(arg0.sort()));
        assert(is_bag(arg1.sort()));
        
        return application(subbag_or_equal(s),arg0, arg1);
      }

      // Recogniser for application of <=
      inline
      bool is_subbag_or_equal_application(const data_expression& e)
      {
        if (e.is_application())
        {
          return is_subbag_or_equal_function_symbol(static_cast<const application&>(e).head());
        }
        return false;
      }

      // Function symbol <
      inline
      function_symbol subbag(const sort_expression& s)
      {
        static function_symbol subbag("<", function_sort(bag(s), bag(s), bool_()));
        return subbag;
      }

      // Recogniser for <
      inline
      bool is_subbag_function_symbol(const data_expression& e)
      {
        if (e.is_function_symbol())
        {
          return static_cast<const function_symbol&>(e).name() == "<";
        }
        return false;
      }

      // Application of <
      inline
      application subbag(const sort_expression& s, const data_expression& arg0, const data_expression& arg1)
      {
        assert(is_bag(arg0.sort()));
        assert(is_bag(arg1.sort()));
        
        return application(subbag(s),arg0, arg1);
      }

      // Recogniser for application of <
      inline
      bool is_subbag_application(const data_expression& e)
      {
        if (e.is_application())
        {
          return is_subbag_function_symbol(static_cast<const application&>(e).head());
        }
        return false;
      }

      // Function symbol +
      inline
      function_symbol union_(const sort_expression& s)
      {
        static function_symbol union_("+", function_sort(bag(s), bag(s), bag(s)));
        return union_;
      }

      // Recogniser for +
      inline
      bool is_union__function_symbol(const data_expression& e)
      {
        if (e.is_function_symbol())
        {
          return static_cast<const function_symbol&>(e).name() == "+";
        }
        return false;
      }

      // Application of +
      inline
      application union_(const sort_expression& s, const data_expression& arg0, const data_expression& arg1)
      {
        assert(is_bag(arg0.sort()));
        assert(is_bag(arg1.sort()));
        
        return application(union_(s),arg0, arg1);
      }

      // Recogniser for application of +
      inline
      bool is_union__application(const data_expression& e)
      {
        if (e.is_application())
        {
          return is_union__function_symbol(static_cast<const application&>(e).head());
        }
        return false;
      }

      // Function symbol -
      inline
      function_symbol difference(const sort_expression& s)
      {
        static function_symbol difference("-", function_sort(bag(s), bag(s), bag(s)));
        return difference;
      }

      // Recogniser for -
      inline
      bool is_difference_function_symbol(const data_expression& e)
      {
        if (e.is_function_symbol())
        {
          return static_cast<const function_symbol&>(e).name() == "-";
        }
        return false;
      }

      // Application of -
      inline
      application difference(const sort_expression& s, const data_expression& arg0, const data_expression& arg1)
      {
        assert(is_bag(arg0.sort()));
        assert(is_bag(arg1.sort()));
        
        return application(difference(s),arg0, arg1);
      }

      // Recogniser for application of -
      inline
      bool is_difference_application(const data_expression& e)
      {
        if (e.is_application())
        {
          return is_difference_function_symbol(static_cast<const application&>(e).head());
        }
        return false;
      }

      // Function symbol *
      inline
      function_symbol intersection(const sort_expression& s)
      {
        static function_symbol intersection("*", function_sort(bag(s), bag(s), bag(s)));
        return intersection;
      }

      // Recogniser for *
      inline
      bool is_intersection_function_symbol(const data_expression& e)
      {
        if (e.is_function_symbol())
        {
          return static_cast<const function_symbol&>(e).name() == "*";
        }
        return false;
      }

      // Application of *
      inline
      application intersection(const sort_expression& s, const data_expression& arg0, const data_expression& arg1)
      {
        assert(is_bag(arg0.sort()));
        assert(is_bag(arg1.sort()));
        
        return application(intersection(s),arg0, arg1);
      }

      // Recogniser for application of *
      inline
      bool is_intersection_application(const data_expression& e)
      {
        if (e.is_application())
        {
          return is_intersection_function_symbol(static_cast<const application&>(e).head());
        }
        return false;
      }

      // Function symbol Bag2Set
      inline
      function_symbol bag2set(const sort_expression& s)
      {
        static function_symbol bag2set("Bag2Set", function_sort(bag(s), set(s)));
        return bag2set;
      }

      // Recogniser for Bag2Set
      inline
      bool is_bag2set_function_symbol(const data_expression& e)
      {
        if (e.is_function_symbol())
        {
          return static_cast<const function_symbol&>(e).name() == "Bag2Set";
        }
        return false;
      }

      // Application of Bag2Set
      inline
      application bag2set(const sort_expression& s, const data_expression& arg0)
      {
        assert(is_bag(arg0.sort()));
        
        return application(bag2set(s),arg0);
      }

      // Recogniser for application of Bag2Set
      inline
      bool is_bag2set_application(const data_expression& e)
      {
        if (e.is_application())
        {
          return is_bag2set_function_symbol(static_cast<const application&>(e).head());
        }
        return false;
      }

      // Function symbol Set2Bag
      inline
      function_symbol set2bag(const sort_expression& s)
      {
        static function_symbol set2bag("Set2Bag", function_sort(set(s), bag(s)));
        return set2bag;
      }

      // Recogniser for Set2Bag
      inline
      bool is_set2bag_function_symbol(const data_expression& e)
      {
        if (e.is_function_symbol())
        {
          return static_cast<const function_symbol&>(e).name() == "Set2Bag";
        }
        return false;
      }

      // Application of Set2Bag
      inline
      application set2bag(const sort_expression& s, const data_expression& arg0)
      {
        assert(is_set(arg0.sort()));
        
        return application(set2bag(s),arg0);
      }

      // Recogniser for application of Set2Bag
      inline
      bool is_set2bag_application(const data_expression& e)
      {
        if (e.is_application())
        {
          return is_set2bag_function_symbol(static_cast<const application&>(e).head());
        }
        return false;
      }

      // Function for projecting out right
      inline
      data_expression right(const data_expression& e)
      {
        assert(is_count_application(e) || is_in_application(e) || is_subbag_or_equal_application(e) || is_subbag_application(e) || is_union__application(e) || is_difference_application(e) || is_intersection_application(e));
        
        if (is_count_application(e))
        {
          return static_cast<const application&>(e).arguments()[1];
        }

        if (is_in_application(e))
        {
          return static_cast<const application&>(e).arguments()[1];
        }

        if (is_subbag_or_equal_application(e))
        {
          return static_cast<const application&>(e).arguments()[1];
        }

        if (is_subbag_application(e))
        {
          return static_cast<const application&>(e).arguments()[1];
        }

        if (is_union__application(e))
        {
          return static_cast<const application&>(e).arguments()[1];
        }

        if (is_difference_application(e))
        {
          return static_cast<const application&>(e).arguments()[1];
        }

        if (is_intersection_application(e))
        {
          return static_cast<const application&>(e).arguments()[1];
        }

        // This should never be reached, otherwise something is severely wrong.
        assert(false); 
      }

      // Function for projecting out left
      inline
      data_expression left(const data_expression& e)
      {
        assert(is_count_application(e) || is_in_application(e) || is_subbag_or_equal_application(e) || is_subbag_application(e) || is_union__application(e) || is_difference_application(e) || is_intersection_application(e));
        
        if (is_count_application(e))
        {
          return static_cast<const application&>(e).arguments()[0];
        }

        if (is_in_application(e))
        {
          return static_cast<const application&>(e).arguments()[0];
        }

        if (is_subbag_or_equal_application(e))
        {
          return static_cast<const application&>(e).arguments()[0];
        }

        if (is_subbag_application(e))
        {
          return static_cast<const application&>(e).arguments()[0];
        }

        if (is_union__application(e))
        {
          return static_cast<const application&>(e).arguments()[0];
        }

        if (is_difference_application(e))
        {
          return static_cast<const application&>(e).arguments()[0];
        }

        if (is_intersection_application(e))
        {
          return static_cast<const application&>(e).arguments()[0];
        }

        // This should never be reached, otherwise something is severely wrong.
        assert(false); 
      }

      // Function for projecting out arg
      inline
      data_expression arg(const data_expression& e)
      {
        assert(is_bag_comprehension_application(e) || is_bag2set_application(e) || is_set2bag_application(e));
        
        if (is_bag_comprehension_application(e))
        {
          return static_cast<const application&>(e).arguments()[0];
        }

        if (is_bag2set_application(e))
        {
          return static_cast<const application&>(e).arguments()[0];
        }

        if (is_set2bag_application(e))
        {
          return static_cast<const application&>(e).arguments()[0];
        }

        // This should never be reached, otherwise something is severely wrong.
        assert(false); 
      }

      // Give all system defined equations for Bag
      inline
      data_equation_list bag_generate_equations_code(const sort_expression& s)
      {
        data_equation_list result;
        result.push_back(data_equation(make_vector(variable("g", function_sort(s, nat())), variable("f", function_sort(s, nat()))), true_(), equal_to(bag_comprehension(variable("f", function_sort(s, nat()))), bag_comprehension(variable("g", function_sort(s, nat())))), equal_to(variable("f", function_sort(s, nat())), variable("g", function_sort(s, nat())))));
        result.push_back(data_equation(variable_list(), true_(), emptybag(), bag_comprehension(lambda(make_vector(variable("x", s)),c0()))));
        result.push_back(data_equation(make_vector(variable("d", s), variable("f", function_sort(s, nat()))), true_(), count(variable("d", s), bag_comprehension(variable("f", function_sort(s, nat())))), variable("f", function_sort(s, nat()))(variable("d", s))));
        result.push_back(data_equation(make_vector(variable("s", bag(s)), variable("d", s)), true_(), in(variable("d", s), variable("s", bag(s))), greater(count(variable("d", s), variable("s", bag(s))), c0())));
        result.push_back(data_equation(make_vector(variable("g", function_sort(s, nat())), variable("f", function_sort(s, nat()))), true_(), subbag_or_equal(bag_comprehension(variable("f", function_sort(s, nat()))), bag_comprehension(variable("g", function_sort(s, nat())))), forall(make_vector(variable("x", s)),subbag_or_equal(variable("f", function_sort(s, nat()))(variable("x", s)), variable("g", function_sort(s, nat()))(variable("x", s))))));
        result.push_back(data_equation(make_vector(variable("s", bag(s)), variable("t", bag(s))), true_(), subbag(variable("s", bag(s)), variable("t", bag(s))), and_(subbag_or_equal(variable("s", bag(s)), variable("t", bag(s))), not_equal_to(variable("s", bag(s)), variable("t", bag(s))))));
        result.push_back(data_equation(make_vector(variable("g", function_sort(s, nat())), variable("f", function_sort(s, nat()))), true_(), union_(bag_comprehension(variable("f", function_sort(s, nat()))), bag_comprehension(variable("g", function_sort(s, nat())))), bag_comprehension(lambda(make_vector(variable("x", s)),union_(variable("f", function_sort(s, nat()))(variable("x", s)), variable("g", function_sort(s, nat()))(variable("x", s)))))));
        result.push_back(data_equation(make_vector(variable("g", function_sort(s, nat())), variable("f", function_sort(s, nat()))), true_(), difference(bag_comprehension(variable("f", function_sort(s, nat()))), bag_comprehension(variable("g", function_sort(s, nat())))), bag_comprehension(lambda(make_vector(variable("x", s)),if_(greater(variable("f", function_sort(s, nat()))(variable("x", s)), variable("g", function_sort(s, nat()))(variable("x", s))), gtesubt(variable("f", function_sort(s, nat()))(variable("x", s)), variable("g", function_sort(s, nat()))(variable("x", s))), c0())))));
        result.push_back(data_equation(make_vector(variable("g", function_sort(s, nat())), variable("f", function_sort(s, nat()))), true_(), intersection(bag_comprehension(variable("f", function_sort(s, nat()))), bag_comprehension(variable("g", function_sort(s, nat())))), bag_comprehension(lambda(make_vector(variable("x", s)),min(variable("f", function_sort(s, nat()))(variable("x", s)), variable("g", function_sort(s, nat()))(variable("x", s)))))));
        result.push_back(data_equation(make_vector(variable("s", bag(s))), true_(), bag2set(variable("s", bag(s))), set_comprehension(lambda(make_vector(variable("x", s)),in(variable("x", s), variable("s", bag(s)))))));
        result.push_back(data_equation(make_vector(variable("u", set(s))), true_(), set2bag(variable("u", set(s))), bag_comprehension(lambda(make_vector(variable("x", s)),if_(in(variable("x", s), variable("u", set(s))), cnat(c1()), c0())))));

        return result;
      }

    } // namespace bag
  } // namespace data
} // namespace mcrl2

#endif // MCRL2_DATA_BAG_H
