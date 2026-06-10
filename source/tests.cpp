#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest.h>

#include "list.hpp"


// Hilfsfunktionen, um indirekt auf die Member der Klasse List zuzugreifen (nur für die Tests!)
template<typename T>
size_t get_size(List<T> const& list_to_test) { return list_to_test.size_; }

template<typename T>
ListNode<T>* get_first_pointer(List<T> const& list_to_test) {
  return list_to_test.first_;
}

template<typename T>
ListNode<T>* get_last_pointer(List<T> const& list_to_test) {
  return list_to_test.last_;
}

template<typename T>
ListNode<T>* get_node_pointer(ListIterator<T> const& list_iterator_to_test) {
  return list_iterator_to_test.node_;
}


//test case definitions for default constructor of list as well as empty and size for empty list
#include "sub_tests/default_constructed_list.test"

//test case definitions for push methods of list
#include "sub_tests/push_front.test"
#include "sub_tests/push_back.test"
#include "sub_tests/emplace_front.test"
#include "sub_tests/emplace_back.test"

//test case definitions for pop methods of list
#include "sub_tests/pop_front.test"
#include "sub_tests/pop_back.test"

//test case definitions for

//test cases for element access of list
#include "sub_tests/front.test"
#include "sub_tests/back.test"
//
// //test cases for retrieving iterators
// #include "sub_tests/begin.test"
// #include "sub_tests/end.test"
//
// //iterator tests
// #include "sub_tests/iterators/operator_star.test"
// #include "sub_tests/iterators/operator_arrow.test"
// #include "sub_tests/iterators/operator_equals.test"
// #include "sub_tests/iterators/operator_does_not_equal.test"
// #include "sub_tests/iterators/operator_iterate_forward.test"
//

#include <map>

TEST_CASE("clear") {
  List<int> list{};
  list.push_front(1);
  list.push_front(2);
  list.clear();
  REQUIRE(list.empty());
}

TEST_CASE("Copy Konstruktor") {
  SUBCASE("Freie Kopie") {

    List<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    List<int> copy{ original };

    copy.push_back(99);

    CHECK(original.size() == 3);
    CHECK(copy.size() == 4);
  }
  SUBCASE("Leere Liste") {
    List<int> empty_list;
    List<int> copy{ empty_list };
    CHECK(copy.empty());
  }
  SUBCASE("Pointer sind verschieden") {
    List<int> a;
    a.push_back(1);
    List<int> b{ a };
    CHECK(get_first_pointer(a) != get_first_pointer(b));
  }
}

int main(int argc, char* argv[]) {
  doctest::Context ctx;
  ctx.applyCommandLine(argc, argv);
  return ctx.run();
}
