#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Paciente.hpp"
#include "Servicio.hpp"
#include "Queue.hpp"
#include "Stack.hpp"
#include "List.hpp"
#include "ArbolDecision.hpp"
using namespace std;

Paciente* extraerPaciente(string linea)
{
    stringstream ss(linea);
    string dato;
    string id, nombre, tipoDolor;
    int edad, dolor, trauma, sintomasNeurologicos, requiereCirugia, diasHospitalizacion;
    float temperatura, presionArterial;
    getline(ss, id, ';');
    getline(ss, nombre, ';');
    getline(ss, dato, ';');
    edad = stoi(dato);
    getline(ss, dato, ';');
    temperatura = stof(dato);
    getline(ss, dato, ';');
    presionArterial = stof(dato);
    getline(ss, dato, ';');
    dolor = stoi(dato);
    getline(ss, tipoDolor, ';');
    getline(ss, dato, ';');
    trauma = stoi(dato);
    getline(ss, dato, ';');
    sintomasNeurologicos = stoi(dato);
    getline(ss, dato, ';');
    requiereCirugia = stoi(dato);
    getline(ss, dato, ';');
    diasHospitalizacion = stoi(dato);
    return new Paciente(id, nombre, edad, temperatura, presionArterial, dolor, 
                        tipoDolor, trauma, sintomasNeurologicos, requiereCirugia, diasHospitalizacion);
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
    ArbolDecision arbol;

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
            if (linea.empty()) continue; 

            Paciente* nuevo = extraerPaciente(linea);
            filaEspera.push(nuevo);
        }
        archivo.close();
        cout << "Archivo pacientes.txt cargado correctamente.\n";
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
        cout << "3. Buscar paciente" << endl;
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
                    cout << "\nID: " << p->getId() << "\nNombre: " << p->getNombre() 
                         << "\nEdad: " << p->getEdad() << endl;

                    string ruta = "";
                    string servicioAsignado = arbol.clasificarPaciente(p, ruta);
                    p->setServicio(servicioAsignado); 
                    cout << "Ruta de clasificacion: " << ruta << endl;
                    cout << "Servicio asignado: " << p->getServicio() << endl;
                    Servicio* s = buscarServicio(hospital, p->getServicio());
                    if (s != nullptr) 
                    {
                        s->agregarPaciente(p);
                        cout << "Paciente insertado en el servicio de " << s->getNombre() << ".\n" << endl;
                        historial.push(p);
                    } 
                    else 
                    {
                        cout << "Error: El servicio '" << p->getServicio() << "' generado por el arbol no existe.\n";
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
                    ArbolAVL* arbol = s->getPacientes(); 
                    
                    cout << "\n=== ESTADO " << s->getNombre() << " ===" << endl;
                    
                    if (arbol->estaVacio()) 
                    {
                        cout << "Sin pacientes\n";
                    } 
                    else 
                    {
                        cout << "Altura del arbol AVL: " << arbol->obtenerAlturaArbol() << endl;
                        cout << "Factor de balance raiz: " << arbol->obtenerBalanceRaiz() << endl;
                        cout << "\n--- Pacientes (Recorrido Inorden) ---" << endl;
                        arbol->mostrarInorden();
                    }
                }
                break;
            }
            case 3: 
            {
                cout << "\n=== BUSCAR PACIENTE ===" << endl;
                string busqueda;
                cout << "Indique el ID o Nombre del paciente: ";
                cin.ignore(); 
                getline(cin, busqueda);
                cout << "Buscando en AVL..." << endl;
                Paciente* encontrado = nullptr;
                Servicio* servicioEncontrado = nullptr;
                for (int i = 0; i < hospital.getSize(); i++) 
                {
                    Servicio* s = hospital.get(i);
                    ArbolAVL* arbol = s->getPacientes();
                    encontrado = arbol->buscar(busqueda);
                    if (encontrado == nullptr) 
                    {
                        encontrado = arbol->buscarPorNombre(busqueda);
                    }
                    if (encontrado != nullptr) 
                    {
                        servicioEncontrado = s;
                        break;
                    }
                }
                if (encontrado != nullptr) 
                {
                    cout << "Paciente encontrado :\n";
                    cout << "------\n";
                    cout << "ID: " << encontrado->getId() << "\n";
                    cout << "Nombre : " << encontrado->getNombre() << "\n";
                    cout << "Edad: " << encontrado->getEdad() << "\n";
                    cout << "Departamento : " << servicioEncontrado->getNombre() << "\n";
                    cout << "T: " << encontrado->getTemperatura() << " | ";
                    cout << "D: " << encontrado->getDolor() << " | ";
                    cout << "TD: " << encontrado->getTipoDolor() << " | ";
                    cout << "T: " << (encontrado->getTrauma() ? "Si" : "No") << " | ";
                    cout << "SN: " << (encontrado->getSintomasNeurologicos() ? "Si" : "No") << " | ";
                    cout << "RC: " << (encontrado->getRequiereCirugia() ? "Si" : "No") << " | ";
                    cout << "DH: " << encontrado->getDiasHospitalizacion() << "\n";
                    cout << "------\n";
                } 
                else 
                {
                    cout << "Paciente no encontrado en ningun servicio del hospital.\n";
                }
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
