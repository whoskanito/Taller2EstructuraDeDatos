#pragma once
#include "Node.hpp"

template <class T>
class Stack 
{   
    private:
        Node <T>* tope;
    public:
        Stack() { this->tope = nullptr; }
        bool isEmpty() { return this->tope == nullptr; }
        
        void push(T value) 
        {
            Node<T>* nuevo = new Node<T>(value);
            nuevo->setNext(this->tope);
            this->tope = nuevo;
        }

        T top()
        {
            if (this->isEmpty()) 
            {
                throw "La pila está vacía";
            }
            return this->tope->getValue();
        }

        void pop() 
        {
            if (this->isEmpty()) 
            {
                throw "La pila está vacía";
                return;
            }
            Node<T>* nodoABorrar = this->tope;
            this->tope = this->tope->getNext();
            delete nodoABorrar;
        }

        void clear() 
        {
            while (!this->isEmpty()) 
            {
                this->pop();
            }
        }

        void mostrarHistorial()
        {
            if (this->isEmpty()) 
            {
                cout << "No se han realizado ateniones." << endl;
                return;
            }

            Stack<T> aux;
            while (!this->isEmpty()) 
            {
                T paciente = this->top();
                this->pop();

                cout << "Nombre: " << paciente->getNombre() 
                     << " | Edad: " << paciente->getEdad() 
                     << " | Departamento: " << paciente->getServicio() << endl;
            
                aux.push(paciente);

            }

            while (!aux.isEmpty()) 
            {
                this->push(aux.top());
                aux.pop();
            }
        }

        

        ~Stack() 
        {
            this->clear();
        }

};
