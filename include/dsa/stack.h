#ifndef STACK_H
#define STACK_H

#include "DoublyLinkedList.h"

namespace DSA
{
    template<class T>
    class Stack
    {
        public:
            explicit Stack();
            void push (T& data);
            void pop ();
            bool empty ();
            Node<T>* top();
        private:
            DoublyLinkedList<T> list;
    };

    template<class T>
    Stack<T>::Stack() {}

    template<class T>
    void Stack<T>::push(T &data)
    {   return list.push(data); }

    template<class T>
    bool Stack<T>::empty()
    {   return list.is_empty(); }

    template<class T>
    void Stack<T>::pop ()
    {   return list.pop();  }

    template<class T>
    Node<T>* Stack<T>::top ()
    {   return list.begin(); }

}



#endif // STACK_H