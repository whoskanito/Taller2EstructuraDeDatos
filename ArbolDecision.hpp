#pragma once
#include "NodoDecision.hpp"
#include "Paciente.hpp"
#include <string>

class ArbolDecision 
{
private:
    NodoDecision* raiz;
    void construirArbol();
    void destruirArbol(NodoDecision* nodo);
    std::string evaluarNodo(NodoDecision* nodo, Paciente* p, std::string& ruta);
    
    void inordenRecursivo(NodoDecision* nodo);
    void preordenRecursivo(NodoDecision* nodo);
    void postordenRecursivo(NodoDecision* nodo);

public:
    ArbolDecision();
    ~ArbolDecision();

    std::string clasificarPaciente(Paciente* p, std::string& rutaGenerada);
    void mostrarInorden();
    void mostrarPreorden();
    void mostrarPostorden();
};