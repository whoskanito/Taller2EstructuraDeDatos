#include "Paciente.hpp"

Paciente::Paciente(string id, string nombre, int edad, string servicio) : Persona(nombre, edad) 
{
    this->id = id;
    this->servicio = servicio;
}

string Paciente::getId() { return this->id; }
string Paciente::getServicio() { return this->servicio; }
Paciente::~Paciente() {}