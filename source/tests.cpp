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

TEST_CASE("swap and operator=") {
  List<int> a, b;
  SUBCASE("swap") {
    a.push_back(1); a.push_back(2);
    b.push_back(10); b.push_back(20); b.push_back(30);
    a.swap(b);
    CHECK(a.size()  == 3);
    CHECK(a.front() == 10);
    CHECK(a.back()  == 30);
    CHECK(b.size()  == 2);
    CHECK(b.front() == 1);
    CHECK(b.back()  == 2);
  }
  SUBCASE("swap mit einer leeren Liste") {
    a.push_back(42);
    a.swap(b);
    CHECK(a.empty());
    CHECK(b.size()  == 1);
    CHECK(b.front() == 42);
  }
  SUBCASE("swap mit 2 leeren Listen") {
    a.swap(b);
    CHECK(a.empty());
    CHECK(b.empty());
  }
  SUBCASE("operator= kopiert korrekt") {
    a.push_back(1); a.push_back(2); a.push_back(3);
    b = a;
    CHECK(b.size()  == 3);
    CHECK(b.front() == 1);
    CHECK(b.back()  == 3);
  }
  SUBCASE("operator= erzeugt freie Kopie") {
    a.push_back(10);
    b = a;
    b.push_back(99);
    CHECK(a.size() == 1);
    CHECK(b.size() == 2);
  }
  SUBCASE("operator= überschreibt lhs") {
    b.push_back(99); b.push_back(100);  // b hat vorher Inhalt
    a.push_back(1); a.push_back(2); a.push_back(3);
    b = a;
    CHECK(b.size()  == 3);
    CHECK(b.front() == 1);
  }
  SUBCASE("Self Zuweisung") {
    List<int> a;
    a.push_back(1); a.push_back(2);
    a = a;
    CHECK(a.size()  == 2);
    CHECK(a.front() == 1);
    CHECK(a.back()  == 2);
  }
  SUBCASE("operator= mit leerer Liste") {
    a.push_back(5);
    a = b;
    CHECK(a.empty());
    CHECK(a.size() == 0);
  }
  SUBCASE("Chain Zuwesiung") {
    List<int> a, b, c;
    c.push_back(7);
    a = b = c;
    CHECK(a.size()  == 1);
    CHECK(a.front() == 7);
    CHECK(b.size()  == 1);
    CHECK(b.front() == 7);
  }
}
TEST_CASE("reverse") {
    List<int> list;
  SUBCASE("reverse mit mehreren Elementen") {
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.reverse();
    CHECK(list.size()  == 3);
    CHECK(list.front() == 3);
    CHECK(list.back()  == 1);
  }

  SUBCASE("reverse mit einem Element") {
    list.push_back(42);
    list.reverse();
    CHECK(list.front() == 42);
    CHECK(list.size()  == 1);
  }

  SUBCASE("reverse mit leerer Liste") {
    list.reverse();
    CHECK(list.empty());
  }

  SUBCASE("2-mal reverse") {
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.reverse();
    list.reverse();
    CHECK(list.front() == 1);
    CHECK(list.back()  == 3);
  }

  SUBCASE("reverse gibt Kopie zurück") {
    List<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);
    List<int> reversed = reverse(original);
    CHECK(reversed.front() == 3);
    CHECK(reversed.back()  == 1);
    CHECK(reversed.size()  == 3);
    CHECK(original.front() == 1);
    CHECK(original.back()  == 3);
  }
}
int main(int argc, char* argv[]) {
  doctest::Context ctx;
  ctx.applyCommandLine(argc, argv);
  return ctx.run();
}
