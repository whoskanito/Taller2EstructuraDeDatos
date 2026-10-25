#pragma once
#include <string>
#include "ArbolAVL.hpp"
#include "Paciente.hpp"

class Servicio 
{
    private:
        std::string nombre;
        ArbolAVL* pacientes;
        
    public:
        Servicio(std::string nombre);
        std::string getNombre();
        void agregarPaciente(Paciente* p);
        ArbolAVL* getPacientes();
        ~Servicio();
};
