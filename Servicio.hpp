#pragma once
#include <string>
#include "List.hpp"
#include "Paciente.hpp"
using namespace std;

class Servicio 
{
    private:
        string nombre;
        List<Paciente*>* pacientes; 
        
    public:
        Servicio(string nombre);
        string getNombre();
        void agregarPaciente(Paciente* p);
        List<Paciente*>* getPacientes();
        ~Servicio();
};