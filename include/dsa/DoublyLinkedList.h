#ifndef DoublyLinkedList_H
#define DoublyLinkedList_H

//#if __cplusplus >= 201103L
    #include <functional>
//#endif

namespace DSA
{
    template<class T> class Node final
    {
        public:
            T data;
            Node* next, *prev;
            explicit Node(T& data);
    };

    template<class T>
    Node<T>::Node(T &data): data(data) { this->next = nullptr; this->prev = nullptr;}
    
    template<class T>
    class DoublyLinkedList
    {
        public:
            DoublyLinkedList ();

            void push (T& data);
            void push_back (T& data);
            void push_after (Node<T>* node, T& data);
            void push_before (Node<T>* node, T& data);

            void pop ();
            void pop_back ();
            void remove (Node<T>* node);
            void remove_if (void(*callBack)(const Node<T>*));
            
            bool is_empty ();
            Node<T>* contains (bool(*callBack)(const Node<T>*));
            void for_each (void(*callBack)(const Node<T>*));
//#if __cplusplus >= 201103L
            void for_each(std::function<void(const Node<T>*)> call_back);
            void for_each(std::function<void(T&)> call_back);
//#endif
            Node<T>* begin ();
            Node<T>* end ();
        private:
            Node<T>* head, *tail;

            inline bool is_null_case (Node<T>*);
            inline bool is_null_case ();
    };

    template<class T>
    void DoublyLinkedList<T>::for_each(std::function<void(T&)> call_back)
    {
        Node<T>* itr = head;
        while (itr != nullptr)
        {
            call_back(itr->data);
            itr = itr->next;
        }
    }

//#if __cplusplus >= 201103L
    template<class T>
    void DoublyLinkedList<T>::for_each(std::function<void(const Node<T>*)> call_back)
    {
        Node<T>* itr = head;
        while (itr != nullptr)
        {
            call_back(itr);
            itr = itr->next;
        }
    }
//#endif


    template<class T>
    void DoublyLinkedList<T>::for_each(void (*callBack)(const Node<T> *))
    {
        Node<T>* itr = head;
        while (itr != nullptr)
        {
            callBack (itr);
            itr = itr->next;
        }
    }

    template<class T>
    void DoublyLinkedList<T>::remove_if(void (*callBack)(const Node<T> *))
    {
        Node<T>* itr = head;
        while (itr != nullptr)
        {
            if (callBack (itr)) remove(itr);
            itr = itr->next;
        }
    }

    template<class T>
    Node<T>* DoublyLinkedList<T>::begin()
    {
        return head;
    }

    template<class T>
    Node<T>* DoublyLinkedList<T>::end()
    {
        return tail;
    }

    template<class T>
    Node<T>* DoublyLinkedList<T>::contains (bool(*callBack)(const Node<T>*))
    {
        if (is_null_case()) return;

        Node<T>* itr = head;
        while (itr != nullptr)
        {
            if (callBack (itr))
                return itr;
            itr = itr->next;
        }

        return nullptr;
    }

    template<class T>
    inline bool DoublyLinkedList<T>::is_null_case(Node<T>* node)
    {
        bool isNull = head == nullptr && tail == nullptr;
        if (isNull)
        {
            head = node;
            tail = node;
        }
        return isNull;
    }

    template<class T>
    inline bool DoublyLinkedList<T>::is_null_case()
    {
        return head == nullptr && tail == nullptr;
    }

    template<class T>
    DoublyLinkedList<T>::DoublyLinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    template<class T>
    void DoublyLinkedList<T>::push (T& data)
    {
        Node<T>* node = new Node<T> (data);
        if (is_null_case(node)) return;

        head->prev = node;
        node->next = head;
        head = node;
    }

    template<class T>
    void DoublyLinkedList<T>::push_back(T &data)
    {
        Node<T>* node = new Node<T> (data);
        if (is_null_case(node)) return;

        tail->next = node;
        node->prev = tail;
        tail = node;
    }

    template<class T>
    void DoublyLinkedList<T>::pop()
    {
        if(is_null_case()) return;

        Node<T>* pop_node = head;
        head = head->next;
        head->prev = nullptr;
        delete pop_node;
    }

    template<class T>
    void DoublyLinkedList<T>::pop_back()
    {
        if(is_null_case()) return;

        Node<T>* pop_node = tail;
        head = tail->prev;
        tail->next = nullptr;
        delete pop_node;
    }

    template<class T>
    void DoublyLinkedList<T>::push_after(Node<T>* node, T& data)
    {
       if (node == nullptr) return;

       if (node == tail)
       {
           push_back(data);
           return;
       }

       Node<T>* newNode = new Node<T>(data);
       newNode->next = node->next;
       newNode->prev = node;

       node->next->prev = newNode;
       node->next = newNode;
    }

    template<class T>
    void DoublyLinkedList<T>::push_before(Node<T>* node, T& data)
    {
        if (node == nullptr) return;

        if (node == head)
        {
            push(data);
            return;
        }

        Node<T>* newNode = new Node<T> (data);
        newNode->prev = node->prev;
        newNode->next = node;

        node->prev->next = newNode;
        node->prev = newNode;
    }

    template<class T>
    void DoublyLinkedList<T>::remove(Node<T> *node)
    {
        if (node == nullptr) return;

        if (node == head)   head = head->next;
        if (node == tail)   tail = tail->prev;

        if (node->prev != nullptr)  node->prev->next = node->next;
        if (node->next != nullptr)  node->next->prev = node->prev;

        delete node;
    }

    template<class T>
    bool DoublyLinkedList<T>::is_empty ()
    {
        return is_null_case();
    }
}

#endif // DoublyLinkedList_H


