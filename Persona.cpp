#include "Persona.hpp"

Persona::Persona(string nombre, int edad) 
{
    this->nombre = nombre;
    this->edad = edad;
}

string Persona::getNombre() { return this->nombre; }
int Persona::getEdad() { return this->edad; }
Persona::~Persona() {}