#include "List.h"

template<typename T>
List<T>::List()
{
    size = 0;
    head = nullptr;
    tail = nullptr;
    fastarr = nullptr;
    arrsize = 0;
}

template<typename T>
List<T>::~List()
{
    if (this->head != nullptr)
    {
        Node<T> *current = this->head;
        Node<T> *temp = current;
        while (current->next != nullptr)
        {
            current = current->next;
            delete temp;
            temp = current;
        }
        delete current;
    }
    delete[] fastarr;
}

template<typename T>
void List<T>::print()
{
    if(this->head == nullptr) return;
    Node<T> *current = this->head;
    while (current->next != nullptr)
    {
        cout << current->value << endl;
        current = current->next;
    }
    cout << current->value << endl;
}

template<typename T>
void List<T>::clear()
{
    Node<T> *current = this->head;
    Node<T> *temp = current;
    while (current->next != nullptr)
    {
        current = current->next;
        delete temp;
        temp = current;
    }
    delete current;
    this->head = nullptr;
    this->tail = nullptr;
    size = 0;
    delete[] fastarr;
    fastarr = nullptr;
}

template<typename T>
int List<T>::GetSize()
{
    return this->size;
}

template<typename T>
void List<T>::insert(const iterator it, const T value)
{
    Node<T> *current = it.node;
    current->prev->next = new Node<T>(value, current, current->prev);
}

template<typename T>
void List<T>::erase(const iterator it)
{
    Node<T> *current = it.node;
    current->prev->next = current->next;
    delete current;
    size--;
}

template<typename T>
void List<T>::push_back(const T value)
{
    if (head == nullptr) head = tail = new Node<T>(value);
    else
    {
        Node<T> *current = this->tail;
        current->next = new Node<T>(value, current->next, current);
        this->tail = current->next;
    }
    if (size % 10 == 0) 
    {
        if (fastarr == nullptr)
        {
            fastarr = new Node<T>*[1];
            fastarr[0] = this->tail;
        }
        else
        {
            Node<T>** temparr = fastarr;
            fastarr = new Node<T>*[size / 10 + 1];
            for (int i = 0; i < size / 10; i++) fastarr[i] = temparr[i];
            fastarr[size / 10] = this->tail;
        }
        arrsize++;
    }
    size++;
}

template<typename T>
void List<T>::pop_back()
{
    if (this->head == nullptr) return; // need exception
    Node<T> *current = this->tail;
    this->tail = current->prev;
    current->prev->next = nullptr;
    delete current;
    size--;
}

template<typename T>
void List<T>::push_front(const T value)
{
    if (this->head == nullptr) head = tail = new Node<T>(value);
    else
    {
        Node<T> *newhead = new Node<T>(value, this->head);
        this->head->prev = newhead;
        this->head = newhead;
    }
    /*if (++size % 10 == 0) 
    {
        T** temparr = fastarr;
        fastarr = new T*[strlen(temparr) + 1];
        fastarr[0] = 
    } */
}

template<typename T>
void List<T>::pop_front()
{
    if (this->head == nullptr) return; // need exception
    Node<T> *current = this->head;
    this->head = current->next;
    delete current;
    size--;
}

template <typename T>
void List<T>::printarr()
{
    for (int i = 0; i < arrsize; i++)
    {
        cout << fastarr[i]->value << endl;
    }
}
