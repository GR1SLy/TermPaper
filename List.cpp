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
    if (deserializeflag) this->clear_deserialized_objects();
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
    int i = 0;
    while (current->next != nullptr)
    {
        cout << i++ << ": " << *current->value << endl;
        current = current->next;
    }
    cout << i << ": " << *current->value << endl;
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
void List<T>::insert(iterator &it, const T* value)
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

    if (arrsize > it.count / 10) for (int i = it.count / 10 + 1; i < arrsize; i++) fastarr[i] = fastarr[i]->prev;
}

template<typename T>
void List<T>::erase(iterator& it)
{
    if (fastarr[arrsize - 1] == this->tail)
    {
        Node<T>** temp = fastarr;
        arrsize--;
        fastarr = new Node<T>*[arrsize];
        for (int i = 0; i < arrsize; i++) fastarr[i] = temp[i];
    }
    Node<T> *current = it.node;
    it.node = it.node->next;
    if (current == this->head) 
    {
        this->head = current->next;
        current->next->prev = nullptr;
        it.node = this->head;
    }
    else { current->prev->next = current->next; current->next->prev = current->prev; }
    delete current;
    size--;

    if (arrsize > it.count / 10) for (int i = it.count / 10 + 1; i < arrsize; i++) if (fastarr[i]->next != nullptr) fastarr[i] = fastarr[i]->next;
}

template<typename T>
void List<T>::push_back(T* value)
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
void List<T>::push_front(T* value)
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
    bool headflag, tailflag;
    while (current->next != nullptr)
    {
        if (*current->next->value <= *current->value)
        {
            Node<T>* curprev = current;
            Node<T>* curnext = current->next;

            headflag = tailflag = 0;

            if (curnext == this->tail) tailflag = 1;

            while (*curnext->value < *curprev->value)
            {
                if (curprev->prev == nullptr) { headflag = 1; break; }
                if (*curprev->prev->value <= *curnext->value) break;
                curprev = curprev->prev;
            }
            //curprev = curprev->next;

            if (tailflag) 
            {
                this->tail = curnext->prev;
                curnext->prev->next = nullptr;
            }
            else 
            {
                curnext->prev->next = curnext->next;//оборвали связь со взятым элементом
                curnext->next->prev = curnext->prev;
            }

            curnext->next = curprev;//Добавили взятый элемент на его место
            if (headflag) 
            { 
                this->head = curnext;
                curnext->prev = nullptr;
                curprev->prev = curnext;
            }
            else 
            {
                curnext->prev = curprev->prev;
                curprev->prev->next = curnext;
                curprev->prev = curnext;
            }

        }
        if (tailflag) break;
        if (current->value < current->next->value) current = current->next;
    }
    this->setfastarr();
}

template <typename T>
void List<T>::serialize(char *filename)
{
    ofstream ofs(filename, ios::binary);
    if (!ofs.is_open()) { cout << "Cannot open " << filename << " for writing" << endl; return; }
    this->serialize(ofs);
}
template <typename T>
void List<T>::serialize(ofstream& ofs)
{
    ofs.write((char*)&size, sizeof(unsigned int));
    Node<T>* current = this->head;
    while (current->next != nullptr) { ofs.write((char*)current->value, sizeof(T)); current = current->next; }
    ofs.write((char*)current->value, sizeof(T));
    ofs.close();
}

template <typename T>
void List<T>::deserialize(char *filename)
{
    ifstream ifs(filename, ios::binary);
    if (!ifs.is_open()) { cout << "Cannot open " << filename << " for reading" << endl; return; }
    this->deserialize(ifs);

}

template<typename T>
void List<T>::deserialize(ifstream& ifs)
{
    ifs.read((char*)&size, sizeof(unsigned int));
    T value;
    ifs.read((char*)&value, sizeof(T));
    T* valptr = new T(value);
    this->head = new Node<T>(valptr);
    Node<T>* current = this->head;
    for (int i = 1; i < size - 1; i++) 
    { 
        ifs.read((char*)&value, sizeof(T));
        valptr = new T(value);
        current->next = new Node<T>(valptr, current, 0);
        current = current->next;
    }
    ifs.read((char*)&value, sizeof(T));
    valptr = new T(value);
    this->tail = new Node<T>(valptr, current, 0);
    current->next = this->tail;
    ifs.close();
    this->setfastarr();
    deserializeflag = 1;
}

template <typename T>
void List<T>::clear_deserialized_objects()
{
    Node<T>* current = this->head;
    while (current->next != nullptr) { delete current->value; current = current->next; }
    delete current->value;
}
