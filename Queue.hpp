#pragma once
#include "Node.hpp"

template <class T>
class Queue
{   
    private:
        Node<T>* inicio;
        Node<T>* fin;

    public:
        Queue() 
        {
            this->inicio = nullptr;
            this->fin = nullptr;
        }
    
        bool isEmpty() 
        {
            return this->inicio == nullptr;
        }

        void push(T value) 
        {
            Node<T>* nuevo = new Node<T>(value);

            if (this->isEmpty()) 
            {
                this->inicio = nuevo;
                this->fin = nuevo;
            } 
            else 
            {
                this->fin->setNext(nuevo);
                this->fin = nuevo;
            }
        }

        T front()
        {
            if (this->isEmpty()) 
            {
                throw "La cola está vacía. No se puede acceder al elemento.";
            }
            return this->inicio->getValue();
        }

        void pop() 
        {
            if (this->isEmpty())
            {
                return;
            }
            Node<T>* NodoABorrar = this->inicio;
            this->inicio = this->inicio->getNext();

            if (this->inicio == nullptr) 
            {
                this->fin = nullptr;
            }
            delete NodoABorrar;
        }

        void mostrarYContar()
        {
            if (this->isEmpty()) 
            {
                cout << "No hay pacientes en espera" << endl;
                return;
            }

            Node<T>* cursor = this->inicio;
            int contador = 1;
            while (cursor != nullptr)
            {
                Paciente* p = cursor->getValue();
                cout << contador << ". " << p->getId() << " - " << p->getNombre() << endl;
                cursor = cursor->getNext();
                contador++;
            }

        }

        ~Queue() 
        {
            while (!this->isEmpty())
            {
                this->pop();
            }
        }

};












