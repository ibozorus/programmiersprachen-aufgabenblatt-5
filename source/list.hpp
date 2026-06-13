#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP

#include "list_node.hpp"
#include "list_iterator.hpp"

#include <cassert>
#include <cstddef>  //ptrdiff_t
#include <iterator> //std::bidirectional_iterator_tag
#include <iostream>

#include <initializer_list>

// forward declaration of template list class
template<typename T>
class List;

// forward declaration of free function "reverse"
template<typename T>
List<T> reverse(List<T> const& list_to_reverse);

template<typename T>
List<T> operator+(List<T> const& lhs, List<T> const& rhs);

template<typename T>
class List {
public:
  //friend declarations for testing the members
  template<typename TEST_TYPE>
  friend size_t get_size(List<TEST_TYPE> const& list_to_test);

  template<typename TEST_TYPE>
  friend ListNode<TEST_TYPE>*
  get_first_pointer(List<TEST_TYPE> const& list_to_test);

  template<typename TEST_TYPE>
  friend ListNode<TEST_TYPE>*
  get_last_pointer(List<TEST_TYPE> const& list_to_test);

  using value_type = T;
  using pointer = T*;
  using const_pointer = T const*;
  using reference = T&;
  using const_reference = T const&;
  using iterator = ListIterator<T>;

  /* Declaration of Default Constructor */
  List();

  /* Declaration of Copy Constructor using Deep-Copy Semantics */
  List(List const& rhs);

  /* Declaration of Move Constructor */
  List(List&& rhs);

  /* Declaration of Initializer-List-based Constructor */
  List(std::initializer_list<T> ini_list);

  /* Declaration of Destructor */
  ~List();

  /* Declaration of Unifying Assignment Operator - see: Vorlesung 10, pp. 11-13, watch video explanation!*/
  List& operator=(List rhs);

  /* Declaration of built-in Member-Swap method used by Unifying Assignment Operator */
  void swap(List& rhs);

  /* Declaration of list-comparison-operator in terms of equality */
  bool operator==(List const& rhs) const;

  /* Declaration of list-comparison-operator in terms of inequality */
  bool operator!=(List const& rhs) const;

  /* Declaration of size-Method */
  std::size_t size() const;

  /* Declaration of empty-Method */
  bool empty() const;

  /* Declaration of push_front-Method */
  void push_front(T const& element);

  /* Declaration of pop_front-Method */
  void pop_front();

  /* Declaration of push_front-Method */
  void push_back(T const& element);

  /* Declaration of push_front-Method */
  void pop_back();

  /* Declaration of emplace_front-Method */
  template<class... Args>
  void emplace_front(Args&&... args);

  /* Declaration of emplace_back-Method */
  template<class... Args>
  void emplace_back(Args&&... args);

  /* Declaration of front-Method */
  T& front();

  /* Declaration of back-Method */
  T& back();

  /* Declaration of clear-Method */
  void clear();

  /* Declaration of reverse-Method*/
  void reverse();

  /* Declaration of begin-Method returning a ListIterator refering to the first list_node */
  ListIterator<T> begin();
  ListIterator<T> begin() const;

  /* Declaration of end-Method returning a ListIterator refering to the past-the-end-element which marks the end of the list*/
  ListIterator<T> end();
  ListIterator<T> end() const;

  /* Declaration of insert-Method */
  ListIterator<T> insert(ListIterator<T> const& position, T const& value);

  /* Declaration of emplace-Method */
  template<class... Args>
  ListIterator<T> emplace(ListIterator<T> const& position, Args&&... args);

  /* Declaration of erase-Method */
  ListIterator<T> erase(ListIterator<T> const& position);

  // list members
private:
  std::size_t size_;
  ListNode<T>* first_;
  ListNode<T>* last_;
};

/* ======================================== *
 * BEGIN COMMENTING AND IMPLEMENTATION HERE *
 * ======================================== */

//=========================
// not fully implemented yet
/* Aufgabe 5.2 - Teil 1 */
/* Setzt die Größe auf 0 und das erste und letzte Element auf nullptr */
template<typename T>
List<T>::List() :
  size_{ 0 }, first_{ nullptr }, last_{ nullptr } {
}

//=========================
// test and implement
/* Aufgabe 5.2 - Teil 2 */
/* Gibt die Größe der Liste zurück */
template<typename T>
std::size_t List<T>::size() const {
  return size_;
};

//=========================
// test and implement
/* Aufgabe 5.2 - Teil 3 */
/* Returns true, if list empty, otherwise false */
template<typename T>
bool List<T>::empty() const {
  return size_ == 0;
};

//=========================
/* Aufgabe 5.3 - Teil 1 */
/* Fügt ein neues Element am Anfang der Liste ein, indem das neue Element als Nachgänger auf first_ zeigt und
 * das erste Element (falls vorhanden) als Vorgänger auf das neue element zeigt.
 */
template<typename T>
void List<T>::push_front(T const& element) {
  ListNode<T>* new_node = new ListNode<T>{ element, nullptr, first_ };
  if (empty()) {
    last_ = new_node;
  } else {
    first_->prev = new_node;
  }
  first_ = new_node;
  size_++;
}

//=========================
/* Aufgabe 5.3 - Teil 2 */
/* Entfernt das erste Element von der Liste */
template<typename T>
void List<T>::pop_front() {
  if (empty()) {
    throw "List is empty";
  }
  ListNode<T>* to_delete = first_;
  first_ = first_->next;
  if (first_ == nullptr) {
    last_ = nullptr;
  } else {
    first_->prev = nullptr;
  }
  delete to_delete;
  size_--;
}

//=========================
/* Aufgabe 5.3 - Teil 3 */
/* Fügt ein Element am Ende der Liste ein */
template<typename T>
void List<T>::push_back(T const& element) {
  ListNode<T>* new_node = new ListNode<T>{ element, last_, nullptr };
  if (empty()) {
    first_ = new_node;
  } else {
    last_->next = new_node;
  }
  last_ = new_node;
  size_++;
}

//=========================
/* Aufgabe 5.3 - Teil 4 */
/* Entfernt das letzte Element der Liste */
template<typename T>
void List<T>::pop_back() {
  if (empty()) {
    throw "List is empty";
  }
  ListNode<T>* to_delete = last_;
  last_ = last_->prev;
  if (last_ == nullptr) {
    first_ = nullptr;
  } else {
    last_->next = nullptr;
  }
  delete to_delete;
  size_--;
}

//=========================
/* Aufgabe 5.3 - Teil 5 */
/* Konstruiert ein neues Element am Ende der Liste mit den übergebenen Argumenten */
template<typename T>
template<class... Args> //Variadic Template
void List<T>::emplace_back(Args&&... args) {
  push_back(T{ std::forward<Args>(args)... });
}

//=========================
/* Aufgabe 5.3 - Teil 6 */
/* Konstruiert ein neues Element am Anfang der Liste mit den übergebenen Argumenten */
template<typename T>
template<class... Args> //Variadic Template
void List<T>::emplace_front(Args&&... args) {
  push_front(T{ std::forward<Args>(args)... });
  //Argumente werden 1:1 weitergereicht an Konstruktor
}


//=========================
/* Aufgabe 5.3 - Teil 6 */
/* Gibt das erste Element zurück, falls vorhanden */
template<typename T>
T& List<T>::front() {
  if (empty()) {
    throw "List is empty";
  }
  return first_->value;
}

//=========================
/* Aufgabe 5.3 - Teil 8 */
/* Gibt das letzte Element zurück, falls vorhanden */
template<typename T>
T& List<T>::back() {
  if (empty()) {
    throw "List is empty";
  }
  return last_->value;
}

/** push_back/push_front nimmt eine Objektreferenz und speichert diese in der Liste
 * emplace_back/emplace_front konstruiert zuerst ein neues Objekt mit den übergebenen Werten
 * speichert dann dieses in der Liste
 */


//=========================
// test and implement:
// Aufgabe 5.4 - Teil 1
/* Entfernt das letzte Element, bis die Liste leer ist */
template<typename T>
void List<T>::clear() {
  while (!empty()) {
    pop_back();
  }
}

//=========================
// test and implement:
// Aufgabe 5.4 - Teil 2
/* Destruktor */
template<typename T>
List<T>::~List() {
  clear();
} //can not be tested with unit tests

//=========================
// test and implement:
//
// Aufgabe 5.5
/* Konstruiert eine tiefe Kopie von der übergebenen Liste */
template<typename T>
List<T>::List(List<T> const& rhs) :
  size_{ 0 }, first_{ nullptr }, last_{ nullptr } {
  ListNode<T>* current = rhs.first_;
  while (current != nullptr) {
    push_back(current->value);
    current = current->next;
  }
}

//=========================
// test and implement:
// Aufgabe 5.6 - Teil 1
/* Tauscht die Attribute der Listen */
template<typename T>
void List<T>::swap(List<T>& rhs) {
  std::swap(size_, rhs.size_);
  std::swap(first_, rhs.first_);
  std::swap(last_, rhs.last_);
}

//=========================
// test and implement:
// Das Objekt übernimmt die Attribute von rhs, rhs wird beim verlassen des scope freigegeben
// Aufgabe 5.6 - Teil 2
/* ... */
template<typename T>
List<T>& List<T>::operator=(List<T> rhs) {
  swap(rhs);
  return *this;
}

//=========================
// Aufgabe 5.7 - Teil 1
/* Kehrt die Liste um, indem prev und next zeiger getauscht werden. */
template<typename T>
void List<T>::reverse() {
  ListNode<T>* current = first_;
  while (current != nullptr) {
    std::swap(current->next, current->prev);
    current = current->prev;
  }
  std::swap(first_, last_);
}

//=========================
// Aufgabe 5.7 - Teil 2
/* Erzeugt eine Kopie von der übergebenen Liste, kehrt die reihenfolge und gibt diese zurück */
template<typename T>
List<T> reverse(List<T> const& list_to_reverse) {
  List<T> result{ list_to_reverse };
  result.reverse();
  return result;
}

//=========================
// Aufgabe 5.8 - Teil 1
/* Gibt true zurück falls die Listeninhalt gleich ist, sonst false */
template<typename T>
bool List<T>::operator==(List const& rhs) const {
  if (this->size() != rhs.size()) {
    return false;
  }
  ListNode<T>* current_lhs = this->first_;
  ListNode<T>* current_rhs = rhs.first_;
  while (current_lhs != nullptr && current_rhs != nullptr) {
    if (current_lhs->value != current_rhs->value)
      return false;
    current_lhs = current_lhs->next;
    current_rhs = current_rhs->next;
  }
  return true;
}

//=========================
// Aufgabe 5.8 - Teil 2
/* Gibt true zurück falls die Listeninhalt ungleich ist, sonst false */
template<typename T>
bool List<T>::operator!=(List const& rhs) const {
  return !(*this == rhs);
}

//=========================
// Aufgabe 5.9 - Teil 1
/* Gibt einen Iterator auf das erste Element der Liste zurück. Falls liste leer, dann nullptr */
template<typename T>
ListIterator<T> List<T>::begin() {
  return ListIterator<T>{ this->first_ };
}
template<typename T>
ListIterator<T> List<T>::begin() const{
  return ListIterator<T>{ this->first_ };
}

//=========================
// Aufgabe 5.9 - Teil 2
/* Gibt einen Iterator mit nullptr zurück, hinter letztes Element*/
template<typename T>
ListIterator<T> List<T>::end() {
  return ListIterator<T>{ nullptr };
}
template<typename T>
ListIterator<T> List<T>::end() const{
  return ListIterator<T>{ nullptr };
}

//=========================
// Aufgabe 5.11
/* Fügt ein neues Element mit value vor der übergebenen position */
template<typename T>
ListIterator<T> List<
  T>::insert(ListIterator<T> const& position, T const& value) {
  ListNode<T>* new_node = new ListNode<T>{ value, nullptr, nullptr };
  if (position == end()) {
    if (empty()) {
      first_ = new_node;
      last_ = new_node;
    } else {
      last_->next = new_node;
      new_node->prev = last_;
      last_ = new_node;
    }
  } else {
    ListNode<T>* next_node = position.node();
    ListNode<T>* prev_node = next_node->prev;

    new_node->next = next_node;
    new_node->prev = prev_node;
    next_node->prev = new_node;

    if (prev_node == nullptr) {
      first_ = new_node;
    } else {
      prev_node->next = new_node;
    }
  }

  size_++;
  return ListIterator<T>{ new_node };
}

template<typename T>
template<class... Args>
ListIterator<T> List<T>::emplace(ListIterator<T> const& position,
                                 Args&&... args) {
  return insert(position, T(std::forward<Args>(args)...));
}

//=========================
// Aufgabe 5.12
/* Entfernt das Element an der übergebenen Position */
template<typename T>
ListIterator<T> List<T>::erase(ListIterator<T> const& position) {
  ListNode<T>* current_node = position.node();
  ListNode<T>* prev_node = current_node->prev;
  ListNode<T>* next_node = current_node->next;
  if (size_ == 1) {
    last_ = nullptr;
    first_ = nullptr;
  }else {
    if (prev_node == nullptr) {
      first_ = next_node;
      first_->prev = nullptr;
    }else if (next_node == nullptr) {
      last_ = prev_node;
      last_->next = nullptr;
    }else {
      prev_node->next = next_node;
      next_node->prev = prev_node;
    }
  }
  size_--;
  delete current_node;
  return ListIterator<T>{next_node};
}

//=========================
// Aufgabe 5.13 is a copy test and should be implemented in a cpp file

//=========================
// test and implement:
// TODO: Move-Konstruktor (Aufgabe 5.14)
/* Verschiebt den Zustand der anderen Liste in die linke Liste*/
template<typename T>
List<T>::List(List<T>&& rhs) :
  first_{ rhs.first_ },
  last_{ rhs.last_ },
  size_{ rhs.size_ } {
  rhs.first_ = nullptr;
  rhs.last_ = nullptr;
  rhs.size_ = 0;
}

//=========================
// test and implement:
//TODO: Initializer - List Konstruktor (5.15 - Teil 1)
/* Erzeugt eine Liste aus der übergebenen brace-enclosed initializer list  */
template<typename T>
List<T>::List(std::initializer_list<T> ini_list) :
  first_{ nullptr }, last_{ nullptr },
  size_(0) {
  for (T const& val: ini_list) {
    push_back(val);
  }
}

//=========================
// Aufgabe 5.15 - Teil 2
/* Fügt 2 übergebene Liste zu einer dritten Liste hinzu und gibt diese zurück */
template<typename T>
List<T> operator+(List<T> const& lhs, List<T> const& rhs) {
  List<T> result{ lhs };
  for (T const& val: rhs) {
    result.push_back(val);
  }
  return result;
}
/**
 * Aufgabe 15:
 * 0-Mal
 */


#endif // #ifndef BUW_LIST_HPP
