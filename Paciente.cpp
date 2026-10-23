#include "Paciente.hpp"
using namespace std;

Paciente::Paciente(string id, string nombre, int edad, 
                   float temperatura, float presionArterial, int dolor, 
                   string tipoDolor, int trauma, int sintomasNeurologicos, 
                   int requiereCirugia, int diasHospitalizacion) 
    : Persona(nombre, edad) 
{
    this->id = id;
    this->servicio = "No asignado"; 
    this->temperatura = temperatura;
    this->presionArterial = presionArterial;
    this->dolor = dolor;
    this->tipoDolor = tipoDolor;
    this->trauma = trauma;
    this->sintomasNeurologicos = sintomasNeurologicos;
    this->requiereCirugia = requiereCirugia;
    this->diasHospitalizacion = diasHospitalizacion;
}

string Paciente::getId() { return id; }
string Paciente::getServicio() { return servicio; }
void Paciente::setServicio(string servicioAsignado) { this->servicio = servicioAsignado; }
float Paciente::getTemperatura() { return temperatura; }
float Paciente::getPresionArterial() { return presionArterial; }
int Paciente::getDolor() { return dolor; }
string Paciente::getTipoDolor() { return tipoDolor; }
int Paciente::getTrauma() { return trauma; }
int Paciente::getSintomasNeurologicos() { return sintomasNeurologicos; }
int Paciente::getRequiereCirugia() { return requiereCirugia; }
int Paciente::getDiasHospitalizacion() { return diasHospitalizacion; }
Paciente::~Paciente() { }