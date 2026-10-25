#pragma once
#include <string>

struct NodoDecision 
{
    std::string condicion;
    bool esHoja;
    std::string servicioResultante;
    
    NodoDecision* izquierdo;
    NodoDecision* derecho;   

    NodoDecision(std::string cond) 
        : condicion(cond), esHoja(false), servicioResultante(""), izquierdo(nullptr), derecho(nullptr) {}

    NodoDecision(std::string cond, std::string servicio) 
        : condicion(cond), esHoja(true), servicioResultante(servicio), izquierdo(nullptr), derecho(nullptr) {}
};