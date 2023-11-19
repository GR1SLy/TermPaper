#include "List.h"

template <typename T>
void List<T>::setfastarr()
{
    Node<T> *current = this->head;
    delete[] fastarr;
    Node<T>** fastarr = new Node<T>*[arrsize];
    int j = 0;
    fastarr[j++] = this->head;
    int i = 1;
    while (current->next != nullptr)
    {
        current = current->next;
        if (i++ % 10 == 0) fastarr[j++] = current;
    }
}

template <typename T>
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

template<typename T>//
void List<T>::insert(iterator &it, const T value)
{
    Node<T> *current = it.node;
    if (current == this->head)
    { 
        this->head = new Node<T>(value, current);
        current->prev = this->head;
        it.node = this->head;
    }
    else current->prev->next = new Node<T>(value, current, current->prev);
    size++;
    this->setfastarr();
}

template<typename T>//
void List<T>::erase(iterator& it)
{
    Node<T> *current = it.node;
    if (current == this->head) 
    {
        this->head = current->next;
        current->next->prev = nullptr;
        it.node = this->head;
    }
    else current->prev->next = current->next;
    delete current;
    size--;
    this->setfastarr();
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
            delete[] temparr;
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
    if (fastarr[size / 10] == this->tail)
    {
        arrsize--;
        Node<T>** temparr = fastarr;
        fastarr = new Node<T>*[arrsize];
        for (int i = 0; i < arrsize; i++) fastarr[i] = temparr[i];
        delete[] temparr;
    }
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
    if (size % 10 == 0)
    {
        if (fastarr == nullptr)
        {
            fastarr = new Node<T>*[1];
            fastarr[0] = this->tail;
        }
        else
        {
            Node<T> **temparr = fastarr;
            fastarr = new Node<T>*[size / 10 + 1];
            for (int i = 0; i < size / 10; i++) fastarr[i] = temparr[i]->prev;
            fastarr[size / 10] = this->tail;
            delete[] temparr;
        }
        arrsize++;
    }
    else if (fastarr != nullptr) for (int i = 0; i < arrsize; i++) fastarr[i] = fastarr[i]->prev;


    size++;
}

template<typename T>
void List<T>::pop_front()
{
    if (this->head == nullptr) return; // need exception
    if (fastarr[size / 10] == this->tail)
    {
        arrsize--;
        Node<T>** temparr = fastarr;
        fastarr = new Node<T>*[arrsize];
        for (int i = 0; i < arrsize; i++) fastarr[i] = temparr[i]->next;
        delete[] temparr;   
    }
    else if (fastarr != nullptr) for (int i = 0; i < arrsize; i++) fastarr[i] = fastarr[i]->next;
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

template <typename T>
void List<T>::sort() // сортировка вставками
{
    Node<T>* current = this->head;
    while (current->next != nullptr)
    {
        if (current->next->value < current->value)
        {
            Node<T>* curprev = current;
            Node<T>* curnext = current->next;
            while (curnext->value < curprev->value && curprev->prev != nullptr) curprev = curprev->prev;
            curnext->prev->next = curnext->next;//оборвали связь со взятым элементом
            curnext->next->prev = curnext->prev;
            curnext->next = curprev->next;//Добавили взятый элемент на его место
            curprev->next->prev = curnext;
            curprev->next = curnext;
            curnext->prev = curprev;
        }
        current = current->next;
    }
}
