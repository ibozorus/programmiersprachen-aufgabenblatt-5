#ifndef BUW_LIST_ITERATOR_HPP
#define BUW_LIST_ITERATOR_HPP

#include "list_node.hpp"

//TODO: Implementierung der Methoden des Iterators (Aufgabe 3.10)
template <typename T>
struct ListIterator {
public:

    //friend declarations for testing the members   
    template <typename TEST_TYPE>
    friend ListNode<TEST_TYPE>* get_node_pointer(ListIterator<TEST_TYPE> const& list_iterator_to_test);

    using Self = ListIterator<T>;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;

    //default constructor with default-member initialization will not be implemented
    ListIterator() = default;
    //user defined constructor implementation is provided below
    ListIterator(ListNode<T>* node);

    //getter for list - node
    ListNode<T>* node() const;

    /* Declaration of operator*() */
    T& operator*()  const;

    /* Declaration of operator->() */
    T* operator->() const;

    /* Declaration of PREINCREMENT-operator, call: ++it, advances one element forward */
    ListIterator<T>& operator++();

    /* Declaration of POSTINCREMENT (signature distinguishes the iterators),
                      call:  it++, advances one element forward */
    ListIterator<T> operator++(int);

    /* Declaration of comparison-operator in terms of equality */
    bool operator==(ListIterator<T> x) const;

    /* Declaration of comparison-operator in terms of inequality */
    bool operator!=(ListIterator<T> x) const;

    /* Advances Iterator */
    ListIterator<T> next() const;

private:
    //only member variable, pointer to the underlying node (see list_node.hpp)
    ListNode <T>* node_ = nullptr;
};

//getter for list-node
template <typename T>
ListNode<T>* ListIterator<T>::node() const { return node_;}

//user-defined constructor is already completely implemented
template<typename T>
ListIterator<T>::ListIterator(ListNode<T>* node) : node_{ node } 
{}

/* ======================================== *
 * BEGIN COMMENTING AND IMPLEMENTATION HERE *
 * ======================================== */

//(Aufgabe 3.10 - Teil 1)
/* Definition of Dereferenceing operator*() /
/* Gibt die Referenz auf den Wert des Listenelements zurück */
// not implemented yet
template <typename T>
T& ListIterator<T>::operator*() const {
    if (nullptr == node_) {
        throw "Iterator does not point to valid node";
    }
  return node_->value;


} //call: *it

//=========================
//(Aufgabe 3.10 - Teil 2)
/* Definition of Dereferenceing operator->() /
/* ... */
// not implemented yet
template <typename T>
T* ListIterator<T>::operator->() const {
    if (nullptr == node_) {
        throw "Iterator does not point to valid node";
    }
  return &node_->value;
}  //call it->method() or it->member

//=========================
// (Aufgabe 3.10 - Teil 3)
/* Definition of preincrement operator ++it /
/* Geht zum nächsten knoten und gibt *this zurück */
// not implemented yet
template <typename T>
ListIterator<T>& ListIterator<T>::operator++() {
    if (nullptr == node_) {
        throw "Iterator does not point to valid node";
    }
  node_ = node_->next;
  return *this;
}

//=========================
//  (Aufgabe 3.10 - Teil 4)
/* Definition of postincrement operator it++ /
/* Geht zum nächsten Knoten und gibt den Vorgänger zurück */
// not implemented yet
template <typename T>
ListIterator<T> ListIterator<T>::operator++(int) {
    if (nullptr == node_) {
        throw "Iterator does not point to valid node";
    }
  ListIterator<T> old{node_};
  node_ = node_->next;
  return old;
}

//=========================
//  (Aufgabe 3.10 - Teil 5)
/* Definition of comparison-operator for iterators in terms of equality */
/* Gibt true zurück, falls Knoten gleich sind. Sonst false. */
// not implemented yet
template <typename T>
bool ListIterator<T>::operator==(ListIterator<T> x) const {
    return this->node_ == x.node_;
} // call it: == it

//=========================
//  (Aufgabe 3.10 - Teil 6)
/* Definition of comparison-operator for iterators in terms of inequality */
/* Gibt true zurück. falls Knoten ungleich sind. Sonst false. */
// not implemented yet
template <typename T>
bool ListIterator<T>::operator!=(ListIterator<T> x) const {
    return !(*this == x);
} // call it: != it

//=========================
// is already implemented
template <typename T>
ListIterator<T> ListIterator<T>::next() const {
    if (nullptr != node_) {
        return ListIterator{ node_->next };
    }
    else {
        return ListIterator{ nullptr };
    }
}

#endif // #ifndef BUW_LIST_ITERATOR_HPP