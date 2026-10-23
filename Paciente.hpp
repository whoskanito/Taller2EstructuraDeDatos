#pragma once
#include "Persona.hpp"
#include <string>

class Paciente : public Persona
{
    private:
        std::string id;
        std::string servicio;
        float temperatura;
        float presionArterial;
        int dolor;
        std::string tipoDolor;
        int trauma;
        int sintomasNeurologicos;
        int requiereCirugia;
        int diasHospitalizacion;

    public:
        Paciente(std::string id, std::string nombre, int edad, 
                 float temperatura, float presionArterial, int dolor, 
                 std::string tipoDolor, int trauma, int sintomasNeurologicos, 
                 int requiereCirugia, int diasHospitalizacion);
                 
        std::string getId();
        std::string getServicio();
        void setServicio(std::string servicioAsignado); 
        float getTemperatura();
        float getPresionArterial();
        int getDolor();
        std::string getTipoDolor();
        int getTrauma();
        int getSintomasNeurologicos();
        int getRequiereCirugia();
        int getDiasHospitalizacion();
        ~Paciente();
};