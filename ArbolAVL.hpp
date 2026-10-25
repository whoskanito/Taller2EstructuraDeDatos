#pragma once
#include "NodoAVL.hpp"
#include <string>
#include <iostream>

class ArbolAVL 
{
private:
    NodoAVL* raiz;

    int altura(NodoAVL* N);
    int max(int a, int b);
    int obtenerBalance(NodoAVL* N);

    NodoAVL* rotacionDerecha(NodoAVL* y);    
    NodoAVL* rotacionIzquierda(NodoAVL* x);  

    NodoAVL* insertarRecursivo(NodoAVL* nodo, Paciente* paciente);
    NodoAVL* buscarRecursivo(NodoAVL* nodo, std::string id);
    NodoAVL* eliminarRecursivo(NodoAVL* nodo, std::string id);
    NodoAVL* nodoValorMinimo(NodoAVL* nodo);
    NodoAVL* buscarPorNombreRecursivo(NodoAVL* nodo, std::string nombre);

    void inordenRecursivo(NodoAVL* nodo);
    void preordenRecursivo(NodoAVL* nodo);
    void postordenRecursivo(NodoAVL* nodo);

    void destruirArbol(NodoAVL* nodo);

public:
    ArbolAVL();
    ~ArbolAVL();

    void insertar(Paciente* paciente);
    bool eliminar(std::string id);
    Paciente* buscar(std::string id);
    Paciente* buscarPorNombre(std::string nombre);

    void mostrarInorden();
    void mostrarPreorden();
    void mostrarPostorden();
    
    int obtenerAlturaArbol();
    int obtenerBalanceRaiz();
    bool estaVacio();
};