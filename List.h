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
        T1 value;
        Node* next;
        Node* prev;
        Node() { value = T1(); next = nullptr; prev = nullptr; }
        Node(const T1 value) { this->value = value; next = nullptr; prev = nullptr; }
        Node(const T1 value, Node* next):Node(value) { this->next = next; prev = nullptr; }
        Node(const T1 value, Node* next, Node* prev):Node(value, next) { this->prev = prev; }

    };

    unsigned int size;
    unsigned int arrsize;
    Node<T> *tail;
    Node<T> *head;
    Node<T>** fastarr;

    void setfastarr(); //use after sort

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
    void insert(iterator& it, const T value);// можно добавить индекс каждому узлу и тем самым уменьшить радиус поиска смещения
    void erase(iterator& it);
    void push_back(const T value);
    void pop_back();// need exception
    void push_front(const T value);
    void pop_front();//need exception
    void printarr();//Нужно будет поменять на возврат массива const
    void sort();
    friend void advance(iterator& it, const int index) { for (int i = 0; i < index; i++) ++it; }
    
};

#endif