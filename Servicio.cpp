#include "Servicio.hpp"
using namespace std;

Servicio::Servicio(string nombre)
{
    this->nombre = nombre;
    this->pacientes = new ArbolAVL();
}

string Servicio::getNombre() { return this->nombre; }

void Servicio::agregarPaciente(Paciente* p) 
{ 
    this->pacientes->insertar(p); 
}

ArbolAVL* Servicio::getPacientes() { return this->pacientes; }

Servicio::~Servicio() { delete this->pacientes; }

