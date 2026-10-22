#include "Servicio.hpp"

Servicio::Servicio(string nombre)
{
    this->nombre = nombre;
    this->pacientes = new List<Paciente*>();
}

string Servicio::getNombre() { return this->nombre; }
void Servicio::agregarPaciente(Paciente* p) { this->pacientes->insertLast(p); }
List <Paciente*>* Servicio::getPacientes() { return this->pacientes; }
Servicio::~Servicio() { delete this->pacientes; }

