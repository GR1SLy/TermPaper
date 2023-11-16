#ifndef LIST_H
#define LIST_H

#include <iostream>
using namespace std;

#pragma once

template<typename T>
class List
{
    template<typename T1>
    struct Node
    {
    public:
        Node* next;
        Node* prev;
        T1 value;
        Node() { value = T1(); next = nullptr; prev = nullptr; }
        Node(const T1 value) { this->value = value; next = nullptr; prev = nullptr; }
        Node(const T1 value, Node* next):Node(value) { this->next = next; prev = nullptr; }
        Node(const T1 value, Node* next, Node* prev):Node(value, next) { this->prev = prev; }

    };

    Node<T> *tail;
    Node<T> *head;
    unsigned int size;
    Node<T>** fastarr;
    unsigned int arrsize;

public:

    struct iterator
    {
        iterator() { node = nullptr;}
        iterator(Node<T> *node) { this->node = node; }
        
        T& operator* () { return this->node->value; }
        T& operator=(const T value) { return this->node->value = value; }

        iterator& operator++() //need exception
        {
            if (this->node->next != nullptr) { this->node = this->node->next; return *this; }
            else return *this;
        }
        iterator operator++(int) { iterator old = *this; ++(*this); return old; }
        iterator& operator--() //need exceptioin
        {
            if (this->node->prev != nullptr) { this->node = this->node->prev; return *this; }
            else return *this;
        }
        iterator operator--(int) { iterator old = *this; --(*this); return old; }
        
        bool operator<(const iterator& other) { return this->node->value < other.node->value; }
        bool operator>(const iterator& other) { return this->node->value > other.node->value; }
        
        friend ostream& operator<< (const ostream& os, const iterator& it) { return os << it.node; }
        friend class List;
    
    private:
        Node<T> *node;
    };

    List();
    ~List();
    void print();
    void clear();
    int GetSize();
    iterator begin() { return iterator(this->head); }
    iterator end() { return iterator(this->tail); }
    void insert(const iterator it, const T value);
    void erase(const iterator it);
    void push_back(const T value);
    void pop_back();
    void push_front(const T value);
    void pop_front();
    void printarr();
    friend void advance(iterator& it, const int index) { for (int i = 0; i < index; i++) ++it; }
    
};

#endif