#pragma once
#include "Persona.hpp"
#include <string>
using namespace std;

class Paciente : public Persona
{
    private:
        string id;
        string servicio;
    public:
        Paciente(string id, string nombre, int edad, string servicio);
        string getId();
        string getServicio();
        ~Paciente();
};