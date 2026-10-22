#pragma once

template <class T> 

class Node 
{
private:
    T value;       
    Node* next;    
public:
    Node(T value) 
    {
        this->value = value;
        this->next = nullptr; 
    }
    
    T getValue() { return this->value; }
    Node<T>* getNext() { return this->next; }
    
    void setValue(T value) { this->value = value; }
    void setNext(Node<T>* next) { this->next = next; }
    
    ~Node() { }
};