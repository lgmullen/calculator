#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL

using namespace std;

template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  //EFFECTS:  returns true if the list is empty
    bool empty() const {
        if (List::first == nullptr) {
            return true;
        }
        return false;
    }

  //EFFECTS: returns the number of elements in this List
    int size() const {
        if (first == nullptr) {return 0;}
        int counter = 0;
        Node *tmp = first;
        while(tmp != nullptr) {
            counter++;
            tmp = tmp->next;
        }
        return counter;
    }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
    T & front() {
        return first->datum;
    }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
    T & back() {
        return last->datum;
    }

  //EFFECTS:  inserts datum into the front of the list
    void push_front(const T &datum) {
    List::Node *tmp = new Node();
        tmp->datum = datum;
        tmp->next = first;
        tmp->prev = nullptr;
            if (first != nullptr) {
                first->prev = tmp;
            }
        if(List::empty()) {
            last = tmp;
        }
        first = tmp;
        }

  //EFFECTS:  inserts datum into the back of the list
    void push_back(const T &datum) {
        List::Node *tmp = new Node();
        tmp->datum = datum;
        tmp->prev = last;
        tmp->next = nullptr;
        if(last != nullptr) {
            last->next = tmp;
        }
        if(empty()) {
            first = tmp;
        }
        last = tmp;
    }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
    void pop_front() {
        if (empty()) {
            return;
        }
        Node * tmp = first;
        if (first->next != nullptr) {
            first->next->prev = nullptr;
        }
        else {
            last = first->next;
        }
        first = first->next;
        delete tmp;
        return;
    }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
    void pop_back() {
        if (empty()) {
            return;
        }
        Node *tmp = last;
        if (last->prev != nullptr) {
            last->prev->next = nullptr;
        }
        else {
            first = last->prev;
        }
        last = last->prev;
        delete tmp;
        return;
    }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists
    ~List() {}
    List() {
        Node *node = new Node;
        node = nullptr;
        first = nullptr;
        last = nullptr;
    }
    List(const List &oldList) {
         Node *node = new Node;
         Node *l1 = oldList.first;
         
         if(oldList.empty()) {
             return;
         }
         else {
             while(l1 != nullptr) {
                 node->datum = l1->datum;
                 node->next = new Node;
                 node->next->prev = node;
                 node = node->next;
                 l1 = l1->next;
             }
         }
        first = oldList.first;
        last = oldList.last;
    }
private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other);

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all nodes
  void pop_all();

  Node *first = nullptr;   // points to first Node in list, or nullptr if list is empty
  Node *last = nullptr;    // points to last Node in list, or nullptr if list is empty

public:
  ////////////////////////////////////////
  class Iterator {
      friend class List;
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
      Iterator() : node_ptr(nullptr) {}
      T & operator*() const {
          assert(node_ptr);
          return node_ptr->datum;
      }

      Iterator &operator++() {
          assert(node_ptr);
          node_ptr = node_ptr->next;
          return *this;
      }

        Iterator& operator--() {
         assert(node_ptr);
         node_ptr = node_ptr->prev;
         return *this;
        }
        bool operator==(Iterator rhs) const {
            return node_ptr == rhs.node_ptr;
        }
        bool operator!=(Iterator rhs) const {
          return node_ptr != rhs.node_ptr;
        }
    
  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
      
    // construct an Iterator at a specific position
    Iterator(Node *p) : node_ptr(p) {
        
    }

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
      return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
    Iterator end() const {
    return Iterator(nullptr);
    }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
    void erase(Iterator i) {
        Iterator it = begin();
        while(it != end()) {
            if(it.node_ptr->next == i.node_ptr) {
                it.node_ptr->next = i.node_ptr->next;
            }
            ++it;
        }
    }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
    void insert(Iterator i, const T &datum) {
        Iterator it = begin();
        while(it != end()) {
        if(it.node_ptr->next == i.node_ptr) {
            Node *tmp = new Node;
            tmp->datum = datum;
            tmp->prev = it.node_ptr;
            tmp->next = it.node_ptr->next;
            it.node_ptr->next = tmp;
            return;
        }
        ++it;
        }
    }
};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.
