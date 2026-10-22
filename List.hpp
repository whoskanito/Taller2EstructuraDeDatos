#pragma once
#include "Node.hpp"

template <class T>
class List
{
    private:
        Node<T>* start;
    
    public:
        List()
        {
            this->start = nullptr;
        }
    
        bool isEmpty()
        {
            return this->start == nullptr;
        }

        void insertLast(T value)
        {
            if (this->isEmpty())
            {
                this->start = new Node<T>(value);
                return;
            }

            Node<T>* cursor = this->start;

            while (cursor->getNext() != nullptr)
            {
                cursor = cursor->getNext();
            }

            cursor->setNext(new Node<T>(value));
        }

        T get(int index)
        {
            if (this->isEmpty() || index < 0)
            {
                throw "Índice inválido ó lista vacía";
            } 
            Node<T>* cursor = this->start;  
            for (int i = 0; i < index; i++)
            {
                cursor = cursor->getNext();
                if (cursor == nullptr)
                {
                    throw "Índice fuera de rango";
                }
                
            }
            return cursor->getValue();

        }

        int getSize()
        {
            int lenght = 0;
            Node<T>* cursor = this->start;
            while (cursor != nullptr)
            {
                lenght++;
                cursor = cursor->getNext();
            }
            return lenght;
        }

        void clear()
        {
            while (this->start != nullptr)
            {
                Node<T>* temp = this->start->getNext();
                delete this->start;
                this->start = temp;
            }                
        }
        
        ~List()
        {
            this->clear();
        }
    
};


