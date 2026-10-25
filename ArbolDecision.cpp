#include "ArbolDecision.hpp"
#include <iostream>

using namespace std;

ArbolDecision::ArbolDecision() {
    construirArbol();
}

void ArbolDecision::construirArbol() 
{
    NodoDecision* pediatria = new NodoDecision("Es paciente pediatrico", "Pediatria");
    NodoDecision* cirugia = new NodoDecision("Requiere cirugia urgente", "Cirugia");
    NodoDecision* traumatologia = new NodoDecision("Trauma sin cirugia", "Traumatologia");
    NodoDecision* neurologia = new NodoDecision("Presenta sintomas neurologicos", "Neurologia");
    NodoDecision* cardiologia = new NodoDecision("Dolor de pecho", "Cardiologia");
    NodoDecision* urgencias = new NodoDecision("Alta temperatura o mucho dolor", "Urgencias");
    NodoDecision* hospitalizacion = new NodoDecision("Requiere mas de 1 dia", "Hospitalizacion");
    NodoDecision* medicinaGeneral = new NodoDecision("Atencion basica", "Medicina General");

    NodoDecision* nodoDias = new NodoDecision("DiasHospitalizacion >= 2");
    nodoDias->izquierdo = hospitalizacion;
    nodoDias->derecho = medicinaGeneral;

    NodoDecision* nodoTempDolor = new NodoDecision("Temperatura >= 38.5 o Dolor >= 8");
    nodoTempDolor->izquierdo = urgencias;
    nodoTempDolor->derecho = nodoDias;

    NodoDecision* nodoDolorPecho = new NodoDecision("TipoDolor == pecho");
    nodoDolorPecho->izquierdo = cardiologia;
    nodoDolorPecho->derecho = nodoTempDolor;

    NodoDecision* nodoNeuro = new NodoDecision("SintomasNeurologicos == 1");
    nodoNeuro->izquierdo = neurologia;
    nodoNeuro->derecho = nodoDolorPecho;

    NodoDecision* nodoCirugia = new NodoDecision("RequiereCirugia == 1");
    nodoCirugia->izquierdo = cirugia;
    nodoCirugia->derecho = traumatologia;

    NodoDecision* nodoTrauma = new NodoDecision("Trauma == 1");
    nodoTrauma->izquierdo = nodoCirugia;
    nodoTrauma->derecho = nodoNeuro;

    raiz = new NodoDecision("Edad < 14");
    raiz->izquierdo = pediatria;
    raiz->derecho = nodoTrauma;
}

string ArbolDecision::evaluarNodo(NodoDecision* nodo, Paciente* p, string& ruta) 
{
    if (nodo == nullptr) return "Medicina General";

    if (nodo->esHoja) 
    {
        return nodo->servicioResultante;
    }

    if (nodo->condicion == "Edad < 14") 
    {
        ruta += "Edad (" + to_string(p->getEdad()) + ") ";
        if (p->getEdad() < 14) 
        {
            ruta += "< 14 -> ";
            return evaluarNodo(nodo->izquierdo, p, ruta);
        } 
        else 
        {
            ruta += ">= 14 -> ";
            return evaluarNodo(nodo->derecho, p, ruta);
        }
    } 
    else if (nodo->condicion == "Trauma == 1") 
    {
        ruta += "Trauma ";
        if (p->getTrauma() == 1) 
        {
            ruta += "== 1 -> ";
            return evaluarNodo(nodo->izquierdo, p, ruta);
        } 
        else 
        {
            ruta += "== 0 -> ";
            return evaluarNodo(nodo->derecho, p, ruta);
        }
    }
    else if (nodo->condicion == "RequiereCirugia == 1") 
    {
        ruta += "RequiereCirugia ";
        if (p->getRequiereCirugia() == 1) 
        {
            ruta += "== 1 -> ";
            return evaluarNodo(nodo->izquierdo, p, ruta);
        } 
        else 
        {
            ruta += "== 0 -> ";
            return evaluarNodo(nodo->derecho, p, ruta);
        }
    }
    else if (nodo->condicion == "SintomasNeurologicos == 1") 
    {
        ruta += "SintomasNeuro ";
        if (p->getSintomasNeurologicos() == 1) 
        {
            ruta += "== 1 -> ";
            return evaluarNodo(nodo->izquierdo, p, ruta);
        } 
        else 
        {
            ruta += "== 0 -> ";
            return evaluarNodo(nodo->derecho, p, ruta);
        }
    }
    else if (nodo->condicion == "TipoDolor == pecho") 
    {
        ruta += "TipoDolor ";
        if (p->getTipoDolor() == "pecho" || p->getTipoDolor() == " pecho ") 
        {
            ruta += "== pecho -> ";
            return evaluarNodo(nodo->izquierdo, p, ruta);
        } 
        else 
        {
            ruta += "!= pecho -> ";
            return evaluarNodo(nodo->derecho, p, ruta);
        }
    }
    else if (nodo->condicion == "Temperatura >= 38.5 o Dolor >= 8") 
    {
        ruta += "Temp o Dolor ";
        if (p->getTemperatura() >= 38.5 || p->getDolor() >= 8) 
        {
            ruta += "Altos -> ";
            return evaluarNodo(nodo->izquierdo, p, ruta);
        } 
        else 
        {
            ruta += "Normales -> ";
            return evaluarNodo(nodo->derecho, p, ruta);
        }
    }
    else if (nodo->condicion == "DiasHospitalizacion >= 2") 
    {
        ruta += "DiasHosp ";
        if (p->getDiasHospitalizacion() >= 2) {
            ruta += ">= 2 -> ";
            return evaluarNodo(nodo->izquierdo, p, ruta);
        } 
        else 
        {
            ruta += "< 2 -> ";
            return evaluarNodo(nodo->derecho, p, ruta);
        }
    }

    return "Medicina General";
}

string ArbolDecision::clasificarPaciente(Paciente* p, string& rutaGenerada) 
{
    rutaGenerada = "";
    return evaluarNodo(raiz, p, rutaGenerada);
}

void ArbolDecision::inordenRecursivo(NodoDecision* nodo) 
{
    if (nodo == nullptr) return;
    inordenRecursivo(nodo->izquierdo);
    cout << "[" << (nodo->esHoja ? nodo->servicioResultante : nodo->condicion) << "] ";
    inordenRecursivo(nodo->derecho);
}

void ArbolDecision::preordenRecursivo(NodoDecision* nodo) 
{
    if (nodo == nullptr) return;
    cout << "[" << (nodo->esHoja ? nodo->servicioResultante : nodo->condicion) << "] ";
    preordenRecursivo(nodo->izquierdo);
    preordenRecursivo(nodo->derecho);
}

void ArbolDecision::postordenRecursivo(NodoDecision* nodo) 
{
    if (nodo == nullptr) return;
    postordenRecursivo(nodo->izquierdo);
    postordenRecursivo(nodo->derecho);
    cout << "[" << (nodo->esHoja ? nodo->servicioResultante : nodo->condicion) << "] ";
}

void ArbolDecision::mostrarInorden() { inordenRecursivo(raiz); cout << endl; }
void ArbolDecision::mostrarPreorden() { preordenRecursivo(raiz); cout << endl; }
void ArbolDecision::mostrarPostorden() { postordenRecursivo(raiz); cout << endl; }

void ArbolDecision::destruirArbol(NodoDecision* nodo) 
{
    if (nodo == nullptr) return;
    destruirArbol(nodo->izquierdo);
    destruirArbol(nodo->derecho);
    delete nodo;
}

ArbolDecision::~ArbolDecision() 
{
    destruirArbol(raiz);
}



