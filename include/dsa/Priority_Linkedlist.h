#ifndef Priority_Linkedlist_H
#define Priority_Linkedlist_H

#include "DoublyLinkedList.h"

namespace DSA
{
    template<class T>
    class  Priority_Linkedlist
    {
        public:
            void prioritize (T& data);
            DoublyLinkedList<T> list;
    };
    
    template<class T>
    void Priority_Linkedlist<T>::prioritize (T& data)
    {
        if (list.is_empty ())
        {
            list.push(data);
            return;
        }

        Node<T>* itr = list.begin ();
        while (itr != nullptr)
        {
            if (data <= itr->data)
            {
                list.push_before (itr, data);
                return;
            }
            itr = itr->next;
        }

        list.push_back (data);
    }
}

#endif // Priority_Linkedlist_H