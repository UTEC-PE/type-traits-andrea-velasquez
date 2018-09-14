#ifndef DLIST_H
#define DLIST_H

#include "iterator.h"

template <typename T>
class DListIterator : public Iterator<T> {     
    public: 
        DListIterator() : Iterator<T>() {};
        DListIterator(Node<T> *current) : Iterator<T>(current) {};
        DListIterator<T> operator++(){
          this->current = this->current->next;
          return *this;
        };
        DListIterator<T> operator--(){
          this->current = this->current->prev;
          return *this;
        };
};

template <typename Tr>
class DList {     
    public:
        typedef typename Tr::T T;
        typedef DListIterator<T> iterator;
      
    private:
        Node<T>* head;
        Node<T>* tail;
              
    public:
        DList() {
            head = tail = nullptr;
        };

        void push_front(T data) {
          //Create new node
          Node<T>* newnode = new Node<T>(data);
          newnode->next = head;
          newnode->prev = nullptr;
          //Change prev head
          if (head){ head->prev = newnode; }
          else { this->tail=newnode; }
          //Change head for new node
          this->head=newnode;
        }

        void push_back(T data) {
          Node<T>* newnode = new Node<T>(data);
          newnode->prev = tail;
          newnode->next = nullptr;

          //Make tail point new node
          if (head) { tail->next = newnode; }
          else{ head=newnode; }

          //Change tail for new node
          this->tail=newnode;
        }
             
        void pop_front() {
          if (!head) throw "Can not delete element in empty list";
          Node<T>* secondnode = head->next;
          secondnode->prev = nullptr;
          head=nullptr;
          delete head; // Aquí no estás borrando, el delete debería ser antes
          head = secondnode;
        }
             
        void pop_back() {
          if (!head) throw "Can not delete element in empty list";
          Node<T>* secondlast = tail->prev;
          //Erase content of previous tail
          tail = nullptr;
          delete tail; // Aquí no estás borrando, el delete debería ser antes
          //Change tail for second last node
          tail = secondlast;
        }
             
        iterator begin() {
          iterator it(head);
          return it;
        }
             
        iterator end() {
          iterator it(nullptr);
          return it;
        }
             
        ~DList() {
            if (head) {
                head->killSelf();
            } 
        }         
};

#endif