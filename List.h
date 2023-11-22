#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <fstream>
using namespace std;

#pragma once

template<typename T>
class List
{
    template<typename T1>
    struct Node
    {
    public:
        T1* value;
        Node* next;
        Node* prev;
        Node() { value = T1(); next = nullptr; prev = nullptr; }
        Node(T1* value) { this->value = value; next = nullptr; prev = nullptr; }
        Node(T1* value, Node* next):Node(value) { this->next = next; prev = nullptr; }
        Node(T1* value, Node* prev, int k):Node(value) { this->prev = prev; next = nullptr; }
        Node(T1* value, Node* next, Node* prev):Node(value, next) { this->prev = prev; }

    };

    bool deserializeflag = 0;
    unsigned int size;
    unsigned int arrsize;
    Node<T> *tail;
    Node<T> *head;
    Node<T>** fastarr;

    void setfastarr(); //use after sort
    void clear_deserialized_objects(); // use in destructor to delete created objects in the heap after deserialize

public:

    struct iterator
    {
        iterator() { node = nullptr; count = 0; }
        iterator(Node<T> *node) { count = 0; this->node = node; }
        
        T& operator* () { return *this->node->value; }
        T& operator=(const T* value) { return *this->node->value = *value; }

        iterator& operator++()
        {
            if (this->node->next != nullptr) { this->node = this->node->next; count++; return *this; }
            else throw ListEx("Iterator out of range. Upper bound");
        }
        iterator operator++(int) { iterator old = *this; ++(*this); return old; }
        iterator& operator--()
        {
            if (this->node->prev != nullptr) { this->node = this->node->prev; count--; return *this; }
            else throw ListEx("Iterator out of range. Lower bound");;
        }
        iterator operator--(int) { iterator old = *this; --(*this); return old; }
        
        int get_count() { return count; } // debug

        bool operator<(const iterator& other) { return *this->node->value < *other.node->value; }
        bool operator>(const iterator& other) { return *this->node->value > *other.node->value; }
        
        friend ostream& operator<< (const ostream& os, const iterator& it) { return os << it.node; }
        friend class List;
    
    private:
        int count;
        Node<T> *node;
    };

    class ListEx : public exception
    {
        const char* info;
    public:
        ListEx() { this->info = static_cast<const char*>("No exception thrown"); }
        ListEx(char* info) { this->info = static_cast<char*>(info); }
        const char* what() const noexcept override{ return info; }
    };

    List();
    ~List();
    void print();
    void clear();
    int GetSize();
    iterator begin() { return iterator(this->head); }
    iterator end() { return iterator(this->tail); }
    void insert(iterator& it, const T* value);
    void erase(iterator& it);
    void push_back(T* value);
    void pop_back();
    void push_front(T* value);
    void pop_front();
    void printarr(); // for debug
    void sort();
    void serialize(char* filename);
    void serialize(ofstream& ofs);
    void deserialize(char* filename);
    void deserialize(ifstream& ifs);
    friend void advance(iterator& it, int index, List<T>& lst) { it.node = lst.fastarr[index / 10]; for (int i = 0; i < index % 10; i++) ++it; } // fast iteration
    friend void advance(iterator& it, int index) { for (int i = 0; i < index / 10; i++) ++it; } // slow iteration
    

};


#endif