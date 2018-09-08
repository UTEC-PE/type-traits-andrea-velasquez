#ifndef SLIST_H
#define SLIST_H

#include "iterator.h"

template <class T>
class SListIterator : public Iterator<T> {     
    public: 
        SListIterator() : Iterator<T>() {};
        SListIterator(Node<T> *current) : Iterator<T>(current) {};
        SListIterator<T> operator++();
          this->current = this->current->next;
          return *this;
        };
};

template <typename Tr>
class SList {     
    public:
        typedef typename Tr::T T;
        typedef typename Tr::Operation Operation;
        typedef SListIterator<T> iterator;
      
    private:
        Node<T>* head;
        Operation cmp;
              
    public:
        SList() {
            head = nullptr;
        };

        bool find(T search, Node<T> **&pointer) {
          while (*pointer) {
            if (cmp(search, (*pointer)->data)) {
              return (*pointer)->data == search;
            }
            pointer = &((*pointer)->next);
          }
          return false;
        }
             
        bool insert(T data) {
          Node<T>* newnode = new Node<T>(data);
          if (!head){ //empty
            head = newnode;
            return true;
          }
          Node<T> **selectednode = &head;
          if (find(data, selectednode)) {return false;} //data already in list
          if (*selectednode==head){ //insertar al principio
            newnode->next = *selectednode;
            head = newnode;
          }
          else if (!*selectednode){ //insertar al final
            *selectednode = newnode;
          }
          else{ //insertar al medio
            newnode->next = *selectednode;
            *selectednode = newnode;
          }

          return true;
        }
             
        bool remove(T item) {
             
          Node<T> **selectednode = &head;
          if (!find(item, selectednode)) return false; //item not in list
          delete *selectednode;
          *selectednode = (*selectednode)->next;

          return true;
        }

        iterator begin() {
          iterator it(head);
          return it;
        }
             
        iterator end() {
          iterator it(nullptr);
          return it;
        }
             
        ~SList() {
            if (head) {
                head->killSelf();
            } 
        }         
};

#endif