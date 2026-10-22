#include <iostream>
#include <fstream>
#include <string>
#include "Paciente.hpp"
#include "Servicio.hpp"
#include "Queue.hpp"
#include "Stack.hpp"
#include "List.hpp"
using namespace std;

Paciente* extraerPaciente(string linea)
{
    string datos[4];
    int indice = 0;

    const char* inicio = linea.c_str(); 
    const char* actual = inicio;

    while (*actual != '\0') 
    {
        if (*actual == ';') 
        {
            datos[indice].assign(inicio, actual - inicio); 
            indice++;
            actual++;
            
            if (*actual == ' ') 
            {
                actual++; 
            }
            inicio = actual;
        } 
        else 
        {
            actual++; 
        }
    }
    datos[indice].assign(inicio, actual - inicio);

    return new Paciente(datos[0], datos[1], stoi(datos[2]), datos[3]);
}

Servicio* buscarServicio(List<Servicio*>& hospital, string nombre) 
{
    for (int i = 0; i < hospital.getSize(); i++) 
    {
        Servicio* s = hospital.get(i);
        if (s->getNombre() == nombre) 
        {
            return s;
        }
    }
    return nullptr;
}

int main() 
{
    Queue<Paciente*> filaEspera;
    Stack<Paciente*> historial;
    List<Servicio*> hospital;

    hospital.insertLast(new Servicio("Urgencias"));
    hospital.insertLast(new Servicio("Medicina General"));
    hospital.insertLast(new Servicio("Cardiologia"));
    hospital.insertLast(new Servicio("Neurologia"));
    hospital.insertLast(new Servicio("Traumatologia"));
    hospital.insertLast(new Servicio("Cirugia"));
    hospital.insertLast(new Servicio("Pediatria"));
    hospital.insertLast(new Servicio("Hospitalizacion"));

    ifstream archivo("pacientes.txt");
    string linea;
    if (archivo.is_open()) 
    {
        while (getline(archivo, linea)) 
        {
            Paciente* nuevo = extraerPaciente(linea);
            filaEspera.push(nuevo);
        }
        archivo.close();
    } 
    else 
    {
        cout << "Error: No se pudo abrir el archivo pacientes.txt" << endl;
    }

    int opcion = 0;
    while (opcion != 4) 
    {
        cout << "\n=== HOSPITAL MARMAJA ===" << endl;
        cout << "1. Atender pacientes" << endl;
        cout << "2. Ver departamento" << endl;
        cout << "3. Revisar historial de atencion" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccionar opcion: ";
        cin >> opcion;

        switch (opcion) 
        {
            case 1: 
            {
                if (filaEspera.isEmpty()) 
                {
                    cout << "No hay pacientes en espera." << endl;
                    break;
                }
                
                cout << "\n=== PACIENTES EN ESPERA ===" << endl;
                filaEspera.mostrarYContar();

                int cantidad;
                cout << "Indique la cantidad de pacientes a atender: ";
                cin >> cantidad;

                cout << "\n=== ATENDIENDO PACIENTES ===" << endl;
                for (int i = 0; i < cantidad; i++) 
                {
                    if (filaEspera.isEmpty()) break; 
                    Paciente* p = filaEspera.front();
                    filaEspera.pop();

                    cout << "ID: " << p->getId() << "\nNombre: " << p->getNombre() 
                         << "\nEdad: " << p->getEdad() << "\nServicio: " << p->getServicio() << endl;

                    Servicio* s = buscarServicio(hospital, p->getServicio());
                    if (s != nullptr) 
                    {
                        s->agregarPaciente(p);
                        cout << "Paciente enviado a " << s->getNombre() << ".\n" << endl;
                        historial.push(p);
                    } 
                    else 
                    {
                        cout << "Error: Servicio '" << p->getServicio() << "' no encontrado." << endl;
                    }
                }
                break;
            }
            case 2: 
            {
                cout << "\n=== DEPARTAMENTOS/SERVICIOS ===" << endl;
                for (int i = 0; i < hospital.getSize(); i++) 
                {
                    cout << i + 1 << ". " << hospital.get(i)->getNombre() << endl;
                }
                int dep;
                cout << "Seleccionar opcion: ";
                cin >> dep;

                if (dep > 0 && dep <= hospital.getSize()) 
                {
                    Servicio* s = hospital.get(dep - 1);
                    List<Paciente*>* listaPacientes = s->getPacientes();
                    
                    cout << "\n=== ESTADO " << s->getNombre() << " ===" << endl;
                    cout << "Pacientes en el departamento: " << listaPacientes->getSize() << endl;
                    
                    for (int i = 0; i < listaPacientes->getSize(); i++) 
                    {
                        Paciente* p = listaPacientes->get(i);
                        cout << "- " << p->getNombre() << " (" << p->getEdad() << ")" << endl;
                    }
                }
                break;
            }
            case 3: 
            {
                cout << "\n=== HISTORIAL DE ÚLTIMAS ATENCIONES DEL HOSPITAL ===" << endl;
                historial.mostrarHistorial();
                break;
            }
            case 4:
                cout << "Adios :3" << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
        }
    }

    for (int i = 0; i < hospital.getSize(); i++) 
    {
        delete hospital.get(i); 
    }

    return 0;
}
















