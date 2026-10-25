#include "ArbolAVL.hpp"
using namespace std;

ArbolAVL::ArbolAVL() 
{
    raiz = nullptr;
}

ArbolAVL::~ArbolAVL() 
{
    destruirArbol(raiz);
}

void ArbolAVL::destruirArbol(NodoAVL* nodo) 
{
    if (nodo != nullptr) 
    {
        destruirArbol(nodo->izquierdo);
        destruirArbol(nodo->derecho);
        delete nodo; 
    }
}

int ArbolAVL::altura(NodoAVL* N) 
{
    if (N == nullptr) return 0;
    return N->altura;
}

int ArbolAVL::max(int a, int b) 
{
    return (a > b) ? a : b;
}

int ArbolAVL::obtenerBalance(NodoAVL* N) 
{
    if (N == nullptr) return 0;
    return altura(N->izquierdo) - altura(N->derecho);
}

NodoAVL* ArbolAVL::rotacionDerecha(NodoAVL* y) 
{
    NodoAVL* x = y->izquierdo;
    NodoAVL* T2 = x->derecho;
    x->derecho = y;
    y->izquierdo = T2;
    y->altura = max(altura(y->izquierdo), altura(y->derecho)) + 1;
    x->altura = max(altura(x->izquierdo), altura(x->derecho)) + 1;

    return x;
}

NodoAVL* ArbolAVL::rotacionIzquierda(NodoAVL* x) 
{
    NodoAVL* y = x->derecho;
    NodoAVL* T2 = y->izquierdo;

    y->izquierdo = x;
    x->derecho = T2;

    x->altura = max(altura(x->izquierdo), altura(x->derecho)) + 1;
    y->altura = max(altura(y->izquierdo), altura(y->derecho)) + 1;

    return y; 
}

void ArbolAVL::insertar(Paciente* paciente) 
{
    raiz = insertarRecursivo(raiz, paciente);
}

NodoAVL* ArbolAVL::insertarRecursivo(NodoAVL* nodo, Paciente* paciente) 
{
    if (nodo == nullptr)
        return new NodoAVL(paciente);

    if (paciente->getId() < nodo->paciente->getId())
        nodo->izquierdo = insertarRecursivo(nodo->izquierdo, paciente);
    else if (paciente->getId() > nodo->paciente->getId())
        nodo->derecho = insertarRecursivo(nodo->derecho, paciente);
    else
        return nodo; 

    nodo->altura = 1 + max(altura(nodo->izquierdo), altura(nodo->derecho));

    int balance = obtenerBalance(nodo);

    if (balance > 1 && paciente->getId() < nodo->izquierdo->paciente->getId())
        return rotacionDerecha(nodo);

    if (balance < -1 && paciente->getId() > nodo->derecho->paciente->getId())
        return rotacionIzquierda(nodo);

    if (balance > 1 && paciente->getId() > nodo->izquierdo->paciente->getId()) 
    {
        nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
        return rotacionDerecha(nodo);
    }

    if (balance < -1 && paciente->getId() < nodo->derecho->paciente->getId()) 
    {
        nodo->derecho = rotacionDerecha(nodo->derecho);
        return rotacionIzquierda(nodo);
    }

    return nodo; 
}

Paciente* ArbolAVL::buscar(string id) 
{
    NodoAVL* resultado = buscarRecursivo(raiz, id);
    if (resultado != nullptr) return resultado->paciente;
    return nullptr;
}

Paciente* ArbolAVL::buscarPorNombre(string nombre) 
{
    NodoAVL* resultado = buscarPorNombreRecursivo(raiz, nombre);
    if (resultado != nullptr) return resultado->paciente;
    return nullptr;
}

NodoAVL* ArbolAVL::buscarPorNombreRecursivo(NodoAVL* nodo, string nombre) 
{
    if (nodo == nullptr) return nullptr;
    if (nodo->paciente->getNombre() == nombre) return nodo;
    NodoAVL* izq = buscarPorNombreRecursivo(nodo->izquierdo, nombre);
    if (izq != nullptr) return izq;
    return buscarPorNombreRecursivo(nodo->derecho, nombre);
}

NodoAVL* ArbolAVL::buscarRecursivo(NodoAVL* nodo, string id) 
{
    if (nodo == nullptr || nodo->paciente->getId() == id)
        return nodo;

    if (nodo->paciente->getId() < id)
        return buscarRecursivo(nodo->derecho, id);

    return buscarRecursivo(nodo->izquierdo, id);
}

bool ArbolAVL::eliminar(string id) 
{
    Paciente* p = buscar(id);
    if (p == nullptr) return false; 
    
    raiz = eliminarRecursivo(raiz, id);
    return true;
}

NodoAVL* ArbolAVL::nodoValorMinimo(NodoAVL* nodo) 
{
    NodoAVL* actual = nodo;
    while (actual->izquierdo != nullptr)
        actual = actual->izquierdo;
    return actual;
}

NodoAVL* ArbolAVL::eliminarRecursivo(NodoAVL* nodo, string id) 
{
    if (nodo == nullptr) return nodo;

    if (id < nodo->paciente->getId())
        nodo->izquierdo = eliminarRecursivo(nodo->izquierdo, id);
    else if (id > nodo->paciente->getId())
        nodo->derecho = eliminarRecursivo(nodo->derecho, id);
    else 
    {
        if ((nodo->izquierdo == nullptr) || (nodo->derecho == nullptr)) 
        {
            NodoAVL* temp = nodo->izquierdo ? nodo->izquierdo : nodo->derecho;
            if (temp == nullptr)
            { 
                temp = nodo;
                nodo = nullptr;
            } 
            else 
                *nodo = *temp; 
            delete temp;
        } 
        else 
        {
            NodoAVL* temp = nodoValorMinimo(nodo->derecho);
            nodo->paciente = temp->paciente;
            nodo->derecho = eliminarRecursivo(nodo->derecho, temp->paciente->getId()); 
        }
    }

    if (nodo == nullptr) return nodo;

    nodo->altura = 1 + max(altura(nodo->izquierdo), altura(nodo->derecho));

    int balance = obtenerBalance(nodo);

    if (balance > 1 && obtenerBalance(nodo->izquierdo) >= 0)
        return rotacionDerecha(nodo);
    if (balance > 1 && obtenerBalance(nodo->izquierdo) < 0) 
    {
        nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
        return rotacionDerecha(nodo);
    }

    if (balance < -1 && obtenerBalance(nodo->derecho) <= 0)
        return rotacionIzquierda(nodo);
    if (balance < -1 && obtenerBalance(nodo->derecho) > 0) 
    {
        nodo->derecho = rotacionDerecha(nodo->derecho);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

void ArbolAVL::inordenRecursivo(NodoAVL* nodo) 
{
    if (nodo != nullptr) 
    {
        inordenRecursivo(nodo->izquierdo);
        cout << nodo->paciente->getId() << " - " << nodo->paciente->getNombre() << " (H:" << nodo->altura << ")\n";
        inordenRecursivo(nodo->derecho);
    }
}

void ArbolAVL::preordenRecursivo(NodoAVL* nodo) 
{
    if (nodo != nullptr) 
    {
        cout << nodo->paciente->getId() << " - " << nodo->paciente->getNombre() << "\n";
        preordenRecursivo(nodo->izquierdo);
        preordenRecursivo(nodo->derecho);
    }
}

void ArbolAVL::postordenRecursivo(NodoAVL* nodo) 
{
    if (nodo != nullptr) 
    {
        postordenRecursivo(nodo->izquierdo);
        postordenRecursivo(nodo->derecho);
        cout << nodo->paciente->getId() << " - " << nodo->paciente->getNombre() << "\n";
    }
}

void ArbolAVL::mostrarInorden() { inordenRecursivo(raiz); }
void ArbolAVL::mostrarPreorden() { preordenRecursivo(raiz); }
void ArbolAVL::mostrarPostorden() { postordenRecursivo(raiz); }

int ArbolAVL::obtenerAlturaArbol() { return altura(raiz); }
int ArbolAVL::obtenerBalanceRaiz() { return obtenerBalance(raiz); }
bool ArbolAVL::estaVacio() { return raiz == nullptr; }