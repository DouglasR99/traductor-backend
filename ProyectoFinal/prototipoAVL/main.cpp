#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <windows.h>
#include <set>
#include<stdlib.h>
#include<cstdlib>
#include <sys/stat.h>
#include<conio.h>
#include<iomanip>
#include <vector>
#include <algorithm>
#include <map>
#include <direct.h>

using namespace std;

string usuarioAutenticado = "";

//INGLES
// Nodo que representa una palabra en el diccionario AVL
struct NodoAVL {
    string palabraEspanol;
    string palabraIngles;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
    int altura;

    NodoAVL(const string& espanol, const string& ingles)
        : palabraEspanol(espanol), palabraIngles(ingles), izquierdo(NULL), derecho(NULL), altura(1) {}
};

// Clase que representa el diccionario AVL
class DiccionarioAVL {
private:
    NodoAVL* raiz;

public:
    DiccionarioAVL() : raiz(NULL) {}

    ~DiccionarioAVL() {
        destruirArbol(raiz);
    }
    
    NodoAVL* obtenerRaiz() const {
        return raiz;
    }

    // Funci�n auxiliar para destruir el �rbol
    void destruirArbol(NodoAVL* nodo) {
        if (nodo) {
            destruirArbol(nodo->izquierdo);
            destruirArbol(nodo->derecho);
            delete nodo;
        }
    }

    // Agrega una palabra al diccionario AVL
    void agregarPalabra(const string& espanol, const string& ingles) {
        raiz = agregarPalabraRec(raiz, espanol, ingles);
    }
    
    void agregarPalabrasIngles(const string& rutaCarpeta, const string& nombreArchivo, const string& espanol, const string& ingles) {
   
    // Construye la ruta completa del archivo
    string rutaCompleta = rutaCarpeta + "\\" + nombreArchivo;
    // Abre el archivo en modo de apertura para agregar al final
    ofstream archivo(rutaCompleta, ios::app);

    // Verifica si el archivo se abri� correctamente
    if (archivo.is_open()) {
        // Escribe las palabras en el archivo
        archivo << espanol << " " << ingles << endl;
        // Cierra el archivo despu�s de escribir
        archivo.close();
        // Muestra un mensaje de �xito
        cout << "Palabras agregadas"<< endl;
    } else {
        // Muestra un mensaje de error si no se puede abrir el archivo
        cerr << "Error al abrir el archivo: " << rutaCompleta << endl;
    }
    
    
}

    // Funci�n auxiliar para agregar una palabra recursivamente
    NodoAVL* agregarPalabraRec(NodoAVL* nodo, const string& espanol, const string& ingles) {
        if (nodo == NULL) {
            return new NodoAVL(espanol, ingles);
        }

        if (espanol < nodo->palabraEspanol) {
            nodo->izquierdo = agregarPalabraRec(nodo->izquierdo, espanol, ingles);
        } else if (espanol > nodo->palabraEspanol) {
            nodo->derecho = agregarPalabraRec(nodo->derecho, espanol, ingles);
        } else {
            // Si la palabra ya existe, se puede manejar de acuerdo a los requerimientos
            // Aqu� simplemente se actualiza la palabra inglesa
            nodo->palabraIngles = ingles;
            return nodo;
        }

        nodo->altura = 1 + max(altura(nodo->izquierdo), altura(nodo->derecho));

        int balance = obtenerBalance(nodo);

        // Casos de rotaci�n
        if (balance > 1 && espanol < nodo->izquierdo->palabraEspanol) {
            return rotarDerecha(nodo);
        }
        if (balance < -1 && espanol > nodo->derecho->palabraEspanol) {
            return rotarIzquierda(nodo);
        }
        if (balance > 1 && espanol > nodo->izquierdo->palabraEspanol) {
            nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
            return rotarDerecha(nodo);
        }
        if (balance < -1 && espanol < nodo->derecho->palabraEspanol) {
            nodo->derecho = rotarDerecha(nodo->derecho);
            return rotarIzquierda(nodo);
        }

        return nodo;
    }

    // Funci�n para obtener la altura de un nodo
    int altura(NodoAVL* nodo) {
        if (nodo == NULL) return 0;
        return nodo->altura;
    }

    // Funci�n para obtener el balance de un nodo
    int obtenerBalance(NodoAVL* nodo) {
        if (nodo == NULL) return 0;
        return altura(nodo->izquierdo) - altura(nodo->derecho);
    }

    // Rotaci�n simple a la derecha
    NodoAVL* rotarDerecha(NodoAVL* y) {
        NodoAVL* x = y->izquierdo;
        NodoAVL* T2 = x->derecho;

        x->derecho = y;
        y->izquierdo = T2;

        y->altura = 1 + max(altura(y->izquierdo), altura(y->derecho));
        x->altura = 1 + max(altura(x->izquierdo), altura(x->derecho));

        return x;
    }

    // Rotaci�n simple a la izquierda
    NodoAVL* rotarIzquierda(NodoAVL* x) {
        NodoAVL* y = x->derecho;
        NodoAVL* T2 = y->izquierdo;

        y->izquierdo = x;
        x->derecho = T2;

        x->altura = 1 + max(altura(x->izquierdo), altura(x->derecho));
        y->altura = 1 + max(altura(y->izquierdo), altura(y->derecho));

        return y;
    }

    // Funci�n para traducir una palabra de espa�ol a ingl�s
    string traducirEspanolIngles(const string& palabra) {
        NodoAVL* actual = raiz;
        while (actual) {
            if (actual->palabraEspanol == palabra) {
                return actual->palabraIngles;
            } else if (palabra < actual->palabraEspanol) {
                actual = actual->izquierdo;
            } else {
                actual = actual->derecho;
            }
        }
        return "Palabra no encontrada";
    }

    // Funci�n para mostrar las palabras en orden (inorder traversal)
    void mostrarPalabras() {
        mostrarPalabrasRec(raiz);
    }

    // Funci�n auxiliar para mostrar las palabras en orden
    void mostrarPalabrasRec(NodoAVL* nodo) {
        if (nodo != NULL) {
            mostrarPalabrasRec(nodo->izquierdo);
            cout << "Espa�ol: " << nodo->palabraEspanol << ", Ingl�s: " << nodo->palabraIngles << endl;
            mostrarPalabrasRec(nodo->derecho);
        }
    }
    void eliminarPalabra(const string& espanol) {
    raiz = eliminarPalabraRec(raiz, espanol);
}

NodoAVL* eliminarPalabraRec(NodoAVL* nodo, const string& espanol) {
    if (nodo == NULL) {
        return nodo;
    }

    if (espanol < nodo->palabraEspanol) {
        nodo->izquierdo = eliminarPalabraRec(nodo->izquierdo, espanol);
    } else if (espanol > nodo->palabraEspanol) {
        nodo->derecho = eliminarPalabraRec(nodo->derecho, espanol);
    } else {
        // Caso 1: Nodo con 0 o 1 hijo
        if (nodo->izquierdo == NULL || nodo->derecho == NULL) {
            NodoAVL* temp = nodo->izquierdo ? nodo->izquierdo : nodo->derecho;

            // Caso 1a: Nodo sin hijos
            if (temp == NULL) {
                temp = nodo;
                nodo = NULL;
            } else { // Caso 1b: Nodo con un hijo
                *nodo = *temp; // Copia los datos del hijo no nulo al nodo actual
            }

            delete temp;
        } else { // Caso 2: Nodo con 2 hijos
            NodoAVL* temp = nodo->derecho;
            while (temp->izquierdo != NULL) {
                temp = temp->izquierdo;
            }

            nodo->palabraEspanol = temp->palabraEspanol;
            nodo->palabraIngles = temp->palabraIngles;

            nodo->derecho = eliminarPalabraRec(nodo->derecho, temp->palabraEspanol);
        }
    }

    if (nodo == NULL) {
        return nodo;
    }

    nodo->altura = 1 + max(altura(nodo->izquierdo), altura(nodo->derecho));

    int balance = obtenerBalance(nodo);

    // Casos de rotaci�n
    if (balance > 1 && obtenerBalance(nodo->izquierdo) >= 0) {
        return rotarDerecha(nodo);
    }
    if (balance < -1 && obtenerBalance(nodo->derecho) <= 0) {
        return rotarIzquierda(nodo);
    }
    if (balance > 1 && obtenerBalance(nodo->izquierdo) < 0) {
        nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
        return rotarDerecha(nodo);
    }
    if (balance < -1 && obtenerBalance(nodo->derecho) > 0) {
        nodo->derecho = rotarDerecha(nodo->derecho);
        return rotarIzquierda(nodo);
    }

    return nodo;
}
void mostrarArbol(NodoAVL* nodo, int nivel = 0) const {
    if (nodo) {
        mostrarArbol(nodo->derecho, nivel + 1);
        for (int i = 0; i < nivel; i++) {
            cout << "   ";
        }
        cout << nodo->palabraEspanol << endl;
        mostrarArbol(nodo->izquierdo, nivel + 1);
    }
}
};

// Funci�n para leer las palabras del archivo de texto y agregarlas al diccionario AVL
void leerPalabras(DiccionarioAVL& diccionario) {
    ifstream archivo("palabrasIngles.txt");
    if (archivo.is_open()) {
        string espanol, ingles;
        while (archivo >> espanol >> ingles) {
            diccionario.agregarPalabra(espanol, ingles);
        }
        archivo.close();
    } else {
        cout << "Error al abrir el archivo" << endl;
    }
}

    void leerPalabrasUsuario(const string& rutaCarpeta, const string& nombreArchivo) {
        // Construye la ruta completa del archivo
        string rutaCompleta = rutaCarpeta + nombreArchivo;
        // Abre el archivo en modo de lectura
        ifstream archivo(rutaCompleta);

        // Verifica si el archivo se abri� correctamente
        if (archivo.is_open()) {
            string espanol, ingles;
            // Lee y muestra las palabras en el archivo
            while (archivo >> espanol >> ingles) {
                cout << "Espanol: " << espanol << " - Ingles: " << ingles << endl;
            }
            archivo.close();
        } else {
            // Muestra un mensaje de error si no se puede abrir el archivo
            cerr << "Error al abrir el archivo: " << rutaCompleta << endl;
        }
    }
// Funci�n para eliminar una palabra y su traducci�n del archivo de usuario
void eliminarPalabraUsuario(const string& rutaCarpeta, const string& nombreArchivo, const string& palabraEspanol) {
    // Construye la ruta completa del archivo
    string rutaCompleta = rutaCarpeta + nombreArchivo;
    string rutaTemporal = rutaCarpeta + "temp_" + nombreArchivo;
    
    ifstream archivo(rutaCompleta);
    ofstream archivoTemp(rutaTemporal);

    if (archivo.is_open() && archivoTemp.is_open()) {
        string espanol, ingles;
        bool palabraEncontrada = false;

        // Lee el archivo original y escribe en el archivo temporal
        while (archivo >> espanol >> ingles) {
            if (espanol != palabraEspanol) {
                archivoTemp << espanol << " " << ingles << endl;
            } else {
                palabraEncontrada = true;
            }
        }

        archivo.close();
        archivoTemp.close();

        // Reemplaza el archivo original con el archivo temporal si la palabra fue encontrada
        if (palabraEncontrada) {
            remove(rutaCompleta.c_str());
            rename(rutaTemporal.c_str(), rutaCompleta.c_str());
            cout << "Palabra '" << palabraEspanol << "' eliminada correctamente." << endl;
        } else {
            remove(rutaTemporal.c_str());
            cout << "Palabra '" << palabraEspanol << "' no encontrada en el archivo." << endl;
        }
    } else {
        cerr << "Error al abrir el archivo." << endl;
    }
}


// Clase que representa un nodo en el diccionario AVL
class NodoAVLalem {
public:
    string palabraEspanol;
    string palabraAleman;
    NodoAVLalem* izquierdo;
    NodoAVLalem* derecho;
    int altura;

    NodoAVLalem(const string& espanol, const string& aleman)
        : palabraEspanol(espanol), palabraAleman(aleman), izquierdo(nullptr), derecho(nullptr), altura(1) {}
};

// Clase que representa el diccionario AVL
class DiccionarioAVLalem {
private:
    NodoAVLalem* raiz;

public:
    DiccionarioAVLalem() : raiz(nullptr) {}

    ~DiccionarioAVLalem() {
        destruirArbol(raiz);
    }
    
    NodoAVLalem* obtenerRaiz() const {
        return raiz;
    }

    // Funci�n auxiliar para destruir el �rbol
    void destruirArbol(NodoAVLalem* nodo) {
        if (nodo) {
            destruirArbol(nodo->izquierdo);
            destruirArbol(nodo->derecho);
            delete nodo;
        }
    }

    // Agrega una palabra al diccionario AVL
    void agregarPalabra(const string& espanol, const string& aleman) {
        raiz = agregarPalabraRec(raiz, espanol, aleman);
    }
    
    void agregarPalabras(const string& rutaCarpeta, const string& nombreArchivo, const string& espanol, const string& aleman) {
   
    // Construye la ruta completa del archivo
    string rutaCompleta = rutaCarpeta + "\\" + nombreArchivo;
    // Abre el archivo en modo de apertura para agregar al final
    ofstream archivo(rutaCompleta, ios::app);

    // Verifica si el archivo se abri� correctamente
    if (archivo.is_open()) {
        // Escribe las palabras en el archivo
        archivo << espanol << " " << aleman << endl;
        // Cierra el archivo despu�s de escribir
        archivo.close();
        // Muestra un mensaje de �xito
        cout << "Palabras agregadas"<< endl;
    } else {
        // Muestra un mensaje de error si no se puede abrir el archivo
        cerr << "Error al abrir el archivo: " << rutaCompleta << endl;
    }
    
    
}

    // Funci�n auxiliar para agregar una palabra recursivamente
    NodoAVLalem* agregarPalabraRec(NodoAVLalem* nodo, const string& espanol, const string& aleman) {
        if (nodo == nullptr) {
            return new NodoAVLalem(espanol, aleman);
        }

        if (espanol < nodo->palabraEspanol) {
            nodo->izquierdo = agregarPalabraRec(nodo->izquierdo, espanol, aleman);
        } else if (espanol > nodo->palabraEspanol) {
            nodo->derecho = agregarPalabraRec(nodo->derecho, espanol, aleman);
        } else {
            // Si la palabra ya existe, se puede manejar de acuerdo a los requerimientos
            // Aqu� simplemente se actualiza la palabra alemana
            nodo->palabraAleman = aleman;
            return nodo;
        }

        nodo->altura = 1 + max(altura(nodo->izquierdo), altura(nodo->derecho));

        int balance = obtenerBalance(nodo);

        // Casos de rotaci�n
        if (balance > 1 && espanol < nodo->izquierdo->palabraEspanol) {
            return rotarDerecha(nodo);
        }
        if (balance < -1 && espanol > nodo->derecho->palabraEspanol) {
            return rotarIzquierda(nodo);
        }
        if (balance > 1 && espanol > nodo->izquierdo->palabraEspanol) {
            nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
            return rotarDerecha(nodo);
        }
        if (balance < -1 && espanol < nodo->derecho->palabraEspanol) {
            nodo->derecho = rotarDerecha(nodo->derecho);
            return rotarIzquierda(nodo);
        }

        return nodo;
    }

    // Funci�n para obtener la altura de un nodo
    int altura(NodoAVLalem* nodo) {
        if (nodo == nullptr) return 0;
        return nodo->altura;
    }

    // Funci�n para obtener el balance de un nodo
    int obtenerBalance(NodoAVLalem* nodo) {
        if (nodo == nullptr) return 0;
        return altura(nodo->izquierdo) - altura(nodo->derecho);
    }

    // Rotaci�n simple a la derecha
    NodoAVLalem* rotarDerecha(NodoAVLalem* y) {
        NodoAVLalem* x = y->izquierdo;
        NodoAVLalem* T2 = x->derecho;

        x->derecho = y;
        y->izquierdo = T2;

        y->altura = 1 + max(altura(y->izquierdo), altura(y->derecho));
        x->altura = 1 + max(altura(x->izquierdo), altura(x->derecho));

        return x;
    }

    // Rotaci�n simple a la izquierda
    NodoAVLalem* rotarIzquierda(NodoAVLalem* x) {
        NodoAVLalem* y = x->derecho;
        NodoAVLalem* T2 = y->izquierdo;

        y->izquierdo = x;
        x->derecho = T2;

        x->altura = 1 + max(altura(x->izquierdo), altura(x->derecho));
        y->altura = 1 + max(altura(y->izquierdo), altura(y->derecho));

        return y;
    }

    // Funci�n para traducir una palabra de espa�ol a alem�n
    string traducirEspanolAleman(const string& palabra) {
        NodoAVLalem* actual = raiz;
        while (actual) {
            if (actual->palabraEspanol == palabra) {
                return actual->palabraAleman;
            } else if (palabra < actual->palabraEspanol) {
                actual = actual->izquierdo;
            } else {
                actual = actual->derecho;
            }
        }
        return "Palabra no encontrada";
    }

    // Funci�n para mostrar las palabras en orden (inorder traversal)
    void mostrarPalabras() {
        mostrarPalabrasRec(raiz);
    }

    // Funci�n auxiliar para mostrar las palabras en orden
    void mostrarPalabrasRec(NodoAVLalem* nodo) {
        if (nodo != nullptr) {
            mostrarPalabrasRec(nodo->izquierdo);
            cout << "Espa�ol: " << nodo->palabraEspanol << ", Alem�n: " << nodo->palabraAleman << endl;
            mostrarPalabrasRec(nodo->derecho);
        }
    }

    // Funci�n para eliminar una palabra del diccionario AVL
    void eliminarPalabra(const string& espanol) {
        raiz = eliminarPalabraRec(raiz, espanol);
    }

    // Funci�n auxiliar para eliminar una palabra recursivamente
    NodoAVLalem* eliminarPalabraRec(NodoAVLalem* nodo, const string& espanol) {
        if (nodo == nullptr) {
            return nodo;
        }

        if (espanol < nodo->palabraEspanol) {
            nodo->izquierdo = eliminarPalabraRec(nodo->izquierdo, espanol);
        } else if (espanol > nodo->palabraEspanol) {
            nodo->derecho = eliminarPalabraRec(nodo->derecho, espanol);
        } else {
            // Caso 1: Nodo con 0 o 1 hijo
            if (nodo->izquierdo == nullptr || nodo->derecho == nullptr) {
                NodoAVLalem* temp = nodo->izquierdo ? nodo->izquierdo : nodo->derecho;

                // Caso 1a: Nodo sin hijos
                if (temp == nullptr) {
                    temp = nodo;
                    nodo = nullptr;
                } else { // Caso 1b: Nodo con un hijo
                    *nodo = *temp; // Copia los datos del hijo no nulo al nodo actual
                }

                delete temp;
            } else { // Caso 2: Nodo con 2 hijos
                NodoAVLalem* temp = nodo->derecho;
                while (temp->izquierdo != nullptr) {
                    temp = temp->izquierdo;
                }

                nodo->palabraEspanol = temp->palabraEspanol;
                nodo->palabraAleman = temp->palabraAleman;

                nodo->derecho = eliminarPalabraRec(nodo->derecho, temp->palabraEspanol);
            }
        }

        if (nodo == nullptr) {
            return nodo;
        }

        nodo->altura = 1 + max(altura(nodo->izquierdo), altura(nodo->derecho));

        int balance = obtenerBalance(nodo);

        // Casos de rotaci�n
        if (balance > 1 && obtenerBalance(nodo->izquierdo) >= 0) {
            return rotarDerecha(nodo);
        }
        if (balance < -1 && obtenerBalance(nodo->derecho) <= 0) {
            return rotarIzquierda(nodo);
        }
        if (balance > 1 && obtenerBalance(nodo->izquierdo) < 0) {
            nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
            return rotarDerecha(nodo);
        }
        if (balance < -1 && obtenerBalance(nodo->derecho) > 0) {
            nodo->derecho = rotarDerecha(nodo->derecho);
            return rotarIzquierda(nodo);
        }

        return nodo;
    }

    // Funci�n para mostrar el �rbol AVL (inorder traversal)
    void mostrarArbol(NodoAVLalem* nodo, int nivel = 0) const {
        if (nodo) {
            mostrarArbol(nodo->derecho, nivel + 1);
            for (int i = 0; i < nivel; i++) {
                cout << "   ";
            }
            cout << nodo->palabraEspanol << endl;
            mostrarArbol(nodo->izquierdo, nivel + 1);
        }
    }
};

// Funci�n para leer las palabras del archivo de texto y agregarlas al diccionario AVL
void leerPalabras(DiccionarioAVLalem& diccionario) {
    ifstream archivo("palabrasAleman.txt");
    if (archivo.is_open()) {
        string espanol, aleman;
        while (archivo >> espanol >> aleman) {
            diccionario.agregarPalabra(espanol, aleman);
        }
        archivo.close();
    } else {
        cout << "Error al abrir el archivo" << endl;
    }
}

//FRANCES
// Clase que representa un nodo en el diccionario AVL para palabras en franc�s
class NodoAVLFran {
public:
    string palabraFrances;
    string palabraEspanol;
    NodoAVLFran* izquierdo;
    NodoAVLFran* derecho;
    int altura;

    // Constructor
    NodoAVLFran(const string& palabraFrances, const string& palabraEspanol)
        : palabraFrances(palabraFrances), palabraEspanol(palabraEspanol),
          izquierdo(nullptr), derecho(nullptr), altura(1) {}
};

// Clase que representa el diccionario AVL para palabras en franc�s
class DiccionarioAVLFran {
private:
    NodoAVLFran* raiz;

public:
    // Constructor
    DiccionarioAVLFran() : raiz(nullptr) {}

    // Destructor
    ~DiccionarioAVLFran() {
        destruirArbol(raiz);
    }

    // Funci�n auxiliar para destruir el �rbol
    void destruirArbol(NodoAVLFran* nodo) {
        if (nodo) {
            destruirArbol(nodo->izquierdo);
            destruirArbol(nodo->derecho);
            delete nodo;
        }
    }

    // Agrega una palabra al diccionario AVL
    void agregarPalabra(const string& palabraFrances, const string& palabraEspanol) {
        raiz = agregarPalabraRec(raiz, palabraFrances, palabraEspanol);
    }
    
       void agregarPalabras(const string& rutaCarpeta, const string& nombreArchivo, const string& espanol, const string& palabraFrances) {
   
    // Construye la ruta completa del archivo
    string rutaCompleta = rutaCarpeta + "\\" + nombreArchivo;
    // Abre el archivo en modo de apertura para agregar al final
    ofstream archivo(rutaCompleta, ios::app);

    // Verifica si el archivo se abri� correctamente
    if (archivo.is_open()) {
        // Escribe las palabras en el archivo
        archivo << espanol << " " << palabraFrances << endl;
        // Cierra el archivo despu�s de escribir
        archivo.close();
        // Muestra un mensaje de �xito
        cout << "Palabras agregadas"<< endl;
    } else {
        // Muestra un mensaje de error si no se puede abrir el archivo
        cerr << "Error al abrir el archivo: " << rutaCompleta << endl;
    }
    
    
}

    // Funci�n auxiliar para agregar una palabra recursivamente
    NodoAVLFran* agregarPalabraRec(NodoAVLFran* nodo, const string& palabraFrances, const string& palabraEspanol) {
        if (nodo == nullptr) {
            return new NodoAVLFran(palabraFrances, palabraEspanol);
        }

        if (palabraFrances < nodo->palabraFrances) {
            nodo->izquierdo = agregarPalabraRec(nodo->izquierdo, palabraFrances, palabraEspanol);
        } else if (palabraFrances > nodo->palabraFrances) {
            nodo->derecho = agregarPalabraRec(nodo->derecho, palabraFrances, palabraEspanol);
        } else {
            // Si la palabra ya existe, se puede manejar de acuerdo a los requerimientos
            // Aqu� simplemente se actualiza la palabra en espa�ol
            nodo->palabraEspanol = palabraEspanol;
            return nodo;
        }

        nodo->altura = 1 + max(altura(nodo->izquierdo), altura(nodo->derecho));

        int balance = obtenerBalance(nodo);

        // Casos de rotaci�n
        if (balance > 1 && palabraFrances < nodo->izquierdo->palabraFrances) {
            return rotarDerecha(nodo);
        }
        if (balance < -1 && palabraFrances > nodo->derecho->palabraFrances) {
            return rotarIzquierda(nodo);
        }
        if (balance > 1 && palabraFrances > nodo->izquierdo->palabraFrances) {
            nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
            return rotarDerecha(nodo);
        }
        if (balance < -1 && palabraFrances < nodo->derecho->palabraFrances) {
            nodo->derecho = rotarDerecha(nodo->derecho);
            return rotarIzquierda(nodo);
        }

        return nodo;
    }

    // Funci�n para obtener la altura de un nodo
    int altura(NodoAVLFran* nodo) {
        if (nodo == nullptr) return 0;
        return nodo->altura;
    }

    // Funci�n para obtener el balance de un nodo
    int obtenerBalance(NodoAVLFran* nodo) {
        if (nodo == nullptr) return 0;
        return altura(nodo->izquierdo) - altura(nodo->derecho);
    }

    // Rotaci�n simple a la derecha
    NodoAVLFran* rotarDerecha(NodoAVLFran* y) {
        NodoAVLFran* x = y->izquierdo;
        NodoAVLFran* T2 = x->derecho;

        x->derecho = y;
        y->izquierdo = T2;

        y->altura = 1 + max(altura(y->izquierdo), altura(y->derecho));
        x->altura = 1 + max(altura(x->izquierdo), altura(x->derecho));

        return x;
    }

    // Rotaci�n simple a la izquierda
    NodoAVLFran* rotarIzquierda(NodoAVLFran* x) {
        NodoAVLFran* y = x->derecho;
        NodoAVLFran* T2 = y->izquierdo;

        y->izquierdo = x;
        x->derecho = T2;

        x->altura = 1 + max(altura(x->izquierdo), altura(x->derecho));
        y->altura = 1 + max(altura(y->izquierdo), altura(y->derecho));

        return y;
    }

    // Funci�n para traducir una palabra de franc�s a espa�ol
    string traducirFrancesEspanol(const string& palabraFrances) {
        NodoAVLFran* actual = raiz;
        while (actual) {
            if (actual->palabraFrances == palabraFrances) {
                return actual->palabraEspanol;
            } else if (palabraFrances < actual->palabraFrances) {
                actual = actual->izquierdo;
            } else {
                actual = actual->derecho;
            }
        }
        return "Palabra no encontrada";
    }

    // Funci�n para mostrar las palabras en orden (inorder traversal)
    void mostrarPalabras() {
        mostrarPalabrasRec(raiz);
    }

    // Funci�n auxiliar para mostrar las palabras en orden
    void mostrarPalabrasRec(NodoAVLFran* nodo) {
        if (nodo != nullptr) {
            mostrarPalabrasRec(nodo->izquierdo);
            cout << "Franc�s: " << nodo->palabraFrances << ", Espa�ol: " << nodo->palabraEspanol << endl;
            mostrarPalabrasRec(nodo->derecho);
        }
    }

    // Funci�n para eliminar una palabra del diccionario AVL
    void eliminarPalabra(const string& palabraFrances) {
        raiz = eliminarPalabraRec(raiz, palabraFrances);
    }

    // Funci�n auxiliar para eliminar una palabra recursivamente
    NodoAVLFran* eliminarPalabraRec(NodoAVLFran* nodo, const string& palabraFrances) {
        if (nodo == nullptr) {
            return nodo;
        }

        if (palabraFrances < nodo->palabraFrances) {
            nodo->izquierdo = eliminarPalabraRec(nodo->izquierdo, palabraFrances);
        } else if (palabraFrances > nodo->palabraFrances) {
            nodo->derecho = eliminarPalabraRec(nodo->derecho, palabraFrances);
        } else {
            // Caso 1: Nodo con 0 o 1 hijo
            if (nodo->izquierdo == nullptr || nodo->derecho == nullptr) {
                NodoAVLFran* temp = nodo->izquierdo ? nodo->izquierdo : nodo->derecho;

                // Caso 1a: Nodo sin hijos
                if (temp == nullptr) {
                    temp = nodo;
                    nodo = nullptr;
                } else { // Caso 1b: Nodo con un hijo
                    *nodo = *temp; // Copia los datos del hijo no nulo al nodo actual
                }

                delete temp;
            } else { // Caso 2: Nodo con 2 hijos
                NodoAVLFran* temp = nodo->derecho;
                while (temp->izquierdo != nullptr) {
                    temp = temp->izquierdo;
                }

                nodo->palabraFrances = temp->palabraFrances;
                nodo->palabraEspanol = temp->palabraEspanol;

                nodo->derecho = eliminarPalabraRec(nodo->derecho, temp->palabraFrances);
            }
        }

        if (nodo == nullptr) {
            return nodo;
        }

        nodo->altura = 1 + max(altura(nodo->izquierdo), altura(nodo->derecho));

        int balance = obtenerBalance(nodo);

        // Casos de rotaci�n
        if (balance > 1 && obtenerBalance(nodo->izquierdo) >= 0) {
            return rotarDerecha(nodo);
        }
        if (balance < -1 && obtenerBalance(nodo->derecho) <= 0) {
            return rotarIzquierda(nodo);
        }
        if (balance > 1 && obtenerBalance(nodo->izquierdo) < 0) {
            nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
            return rotarDerecha(nodo);
        }
        if (balance < -1 && obtenerBalance(nodo->derecho) > 0) {
            nodo->derecho = rotarDerecha(nodo->derecho);
            return rotarIzquierda(nodo);
        }

        return nodo;
    }
    void mostrarArbol() const {
    mostrarArbol(raiz);
}

    void mostrarArbol(NodoAVLFran* nodo, int nivel = 0) const {
    if (nodo) {
        mostrarArbol(nodo->derecho, nivel + 1);
        for (int i = 0; i < nivel; i++) {
            cout << "   ";
        }
        cout << nodo->palabraFrances << endl;
        mostrarArbol(nodo->izquierdo, nivel + 1);
    }
}
};

// Funci�n para leer las palabras del archivo de texto y agregarlas al diccionario AVL
void leerPalabras(DiccionarioAVLFran& diccionario) {
    ifstream archivo("palabrasFrances.txt");
    if (archivo.is_open()) {
        string palabraFrances, palabraEspanol;
        while (archivo >> palabraFrances >> palabraEspanol) {
            diccionario.agregarPalabra(palabraFrances, palabraEspanol);
        }
        archivo.close();
    } else {
        cout << "Error al abrir el archivo" << endl;
    }
}


//ITALIANO
// Clase que representa un nodo en un �rbol AVL para palabras en italiano
class NodoAVLItal {
public:
    string palabraItaliana;
    string palabraEspanola;
    NodoAVLItal* izquierdo;
    NodoAVLItal* derecho;
    int altura;

    // Constructor
    NodoAVLItal(const string& palabraIt, const string& palabraEs) : palabraItaliana(palabraIt), palabraEspanola(palabraEs), izquierdo(nullptr), derecho(nullptr), altura(1) {}
};

// Clase que representa el diccionario AVL para palabras en italiano
class DiccionarioAVLItal {
private:
    NodoAVLItal* raiz;

public:
    // Constructor
    DiccionarioAVLItal() : raiz(nullptr) {}

    // Destructor
    ~DiccionarioAVLItal() {
        destruirArbol(raiz);
    }

    // Funci�n para destruir el �rbol
    void destruirArbol(NodoAVLItal* nodo) {
        if (nodo) {
            destruirArbol(nodo->izquierdo);
            destruirArbol(nodo->derecho);
            delete nodo;
        }
    }

    // Funci�n para agregar una palabra al diccionario AVL
    void agregarPalabra(const string& italiano, const string& espanol) {
        raiz = agregarPalabraRec(raiz, italiano, espanol);
    }
    
    
   void agregarPalabras(const string& rutaCarpeta, const string& nombreArchivo, const string& espanol, const string& italiano) {
   
    // Construye la ruta completa del archivo
    string rutaCompleta = rutaCarpeta + "\\" + nombreArchivo;
    // Abre el archivo en modo de apertura para agregar al final
    ofstream archivo(rutaCompleta, ios::app);

    // Verifica si el archivo se abri� correctamente
    if (archivo.is_open()) {
        // Escribe las palabras en el archivo
        archivo << espanol << " " << italiano << endl;
        // Cierra el archivo despu�s de escribir
        archivo.close();
        // Muestra un mensaje de �xito
        cout << "Palabras agregadas"<< endl;
    } else {
        // Muestra un mensaje de error si no se puede abrir el archivo
        cerr << "Error al abrir el archivo: " << rutaCompleta << endl;
    }
    
    
}

    // Funci�n auxiliar para agregar una palabra recursivamente
    NodoAVLItal* agregarPalabraRec(NodoAVLItal* nodo, const string& italiano, const string& espanol) {
        if (nodo == nullptr) {
            return new NodoAVLItal(italiano, espanol);
        }

        if (italiano < nodo->palabraItaliana) {
            nodo->izquierdo = agregarPalabraRec(nodo->izquierdo, italiano, espanol);
        } else if (italiano > nodo->palabraItaliana) {
            nodo->derecho = agregarPalabraRec(nodo->derecho, italiano, espanol);
        } else {
            // La palabra ya existe, se puede manejar de acuerdo a los requerimientos
            // Aqu� simplemente se actualiza la palabra espa�ola
            nodo->palabraEspanola = espanol;
            return nodo;
        }

        nodo->altura = 1 + max(altura(nodo->izquierdo), altura(nodo->derecho));

        int balance = obtenerBalance(nodo);

        // Casos de rotaci�n
        if (balance > 1 && italiano < nodo->izquierdo->palabraItaliana) {
            return rotarDerecha(nodo);
        }
        if (balance < -1 && italiano > nodo->derecho->palabraItaliana) {
            return rotarIzquierda(nodo);
        }
        if (balance > 1 && italiano > nodo->izquierdo->palabraItaliana) {
            nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
            return rotarDerecha(nodo);
        }
        if (balance < -1 && italiano < nodo->derecho->palabraItaliana) {
            nodo->derecho = rotarDerecha(nodo->derecho);
            return rotarIzquierda(nodo);
        }

        return nodo;
    }

    // Funci�n para obtener la altura de un nodo
    int altura(NodoAVLItal* nodo) {
        if (nodo == nullptr) return 0;
        return nodo->altura;
    }

    // Funci�n para obtener el balance de un nodo
    int obtenerBalance(NodoAVLItal* nodo) {
        if (nodo == nullptr) return 0;
        return altura(nodo->izquierdo) - altura(nodo->derecho);
    }

    // Rotaci�n simple a la derecha
    NodoAVLItal* rotarDerecha(NodoAVLItal* y) {
        NodoAVLItal* x = y->izquierdo;
        NodoAVLItal* T2 = x->derecho;

        x->derecho = y;
        y->izquierdo = T2;

        y->altura = 1 + max(altura(y->izquierdo), altura(y->derecho));
        x->altura = 1 + max(altura(x->izquierdo), altura(x->derecho));

        return x;
    }

    // Rotaci�n simple a la izquierda
    NodoAVLItal* rotarIzquierda(NodoAVLItal* x) {
        NodoAVLItal* y = x->derecho;
        NodoAVLItal* T2 = y->izquierdo;

        y->izquierdo = x;
        x->derecho = T2;

        x->altura = 1 + max(altura(x->izquierdo), altura(x->derecho));
        y->altura = 1 + max(altura(y->izquierdo), altura(y->derecho));

        return y;
    }

    // Funci�n para traducir una palabra de italiano a espa�ol
    string traducirItalianoEspanol(const string& palabra) {
        NodoAVLItal* actual = raiz;
        while (actual) {
            if (actual->palabraItaliana == palabra) {
                return actual->palabraEspanola;
            } else if (palabra < actual->palabraItaliana) {
                actual = actual->izquierdo;
            } else {
                actual = actual->derecho;
            }
        }
        return "Palabra no encontrada";
    }

    // Funci�n para mostrar las palabras en orden (inorder traversal)
    void mostrarPalabras() {
        mostrarPalabrasRec(raiz);
    }

    // Funci�n auxiliar para mostrar las palabras en orden
    void mostrarPalabrasRec(NodoAVLItal* nodo) {
        if (nodo != nullptr) {
            mostrarPalabrasRec(nodo->izquierdo);
            cout << "Italiano: " << nodo->palabraItaliana << ", Espa�ol: " << nodo->palabraEspanola << endl;
            mostrarPalabrasRec(nodo->derecho);
        }
    }

    // Funci�n para eliminar una palabra del diccionario AVL
    void eliminarPalabra(const string& italiano) {
        raiz = eliminarPalabraRec(raiz, italiano);
    }

    // Funci�n auxiliar para eliminar una palabra recursivamente
    NodoAVLItal* eliminarPalabraRec(NodoAVLItal* nodo, const string& italiano) {
        if (nodo == nullptr) {
            return nodo;
        }

        if (italiano < nodo->palabraItaliana) {
            nodo->izquierdo = eliminarPalabraRec(nodo->izquierdo, italiano);
        } else if (italiano > nodo->palabraItaliana) {
            nodo->derecho = eliminarPalabraRec(nodo->derecho, italiano);
        } else {
            // Caso 1: Nodo con 0 o 1 hijo
            if (nodo->izquierdo == nullptr || nodo->derecho == nullptr) {
                NodoAVLItal* temp = nodo->izquierdo ? nodo->izquierdo : nodo->derecho;

                // Caso 1a: Nodo sin hijos
                if (temp == nullptr) {
                    temp = nodo;
                    nodo = nullptr;
                } else { // Caso 1b: Nodo con un hijo
                    *nodo = *temp; // Copia los datos del hijo no nulo al nodo actual
                }

                delete temp;
            } else { // Caso 2: Nodo con 2 hijos
                NodoAVLItal* temp = nodo->derecho;
                while (temp->izquierdo != nullptr) {
                    temp = temp->izquierdo;
                }

                nodo->palabraItaliana = temp->palabraItaliana;
                nodo->palabraEspanola = temp->palabraEspanola;

                nodo->derecho = eliminarPalabraRec(nodo->derecho, temp->palabraItaliana);
            }
        }

        if (nodo == nullptr) {
            return nodo;
        }

        nodo->altura = 1 + max(altura(nodo->izquierdo), altura(nodo->derecho));

        int balance = obtenerBalance(nodo);

        // Casos de rotaci�n
        if (balance > 1 && obtenerBalance(nodo->izquierdo) >= 0) {
            return rotarDerecha(nodo);
        }
        if (balance < -1 && obtenerBalance(nodo->derecho) <= 0) {
            return rotarIzquierda(nodo);
        }
        if (balance > 1 && obtenerBalance(nodo->izquierdo) < 0) {
            nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
            return rotarDerecha(nodo);
        }
        if (balance < -1 && obtenerBalance(nodo->derecho) > 0) {
            nodo->derecho = rotarDerecha(nodo->derecho);
            return rotarIzquierda(nodo);
        }

        return nodo;
    }
    void mostrarArbol() const {
    mostrarArbol(raiz);
}

    void mostrarArbol(NodoAVLItal* nodo, int nivel = 0) const {
    if (nodo) {
        mostrarArbol(nodo->derecho, nivel + 1);
        for (int i = 0; i < nivel; i++) {
            cout << "   ";
        }
        cout << nodo->palabraItaliana << endl;
        mostrarArbol(nodo->izquierdo, nivel + 1);
    }
}
};

// Funci�n para leer las palabras del archivo de texto y agregarlas al diccionario AVL
void leerPalabras(DiccionarioAVLItal& diccionario) {
    ifstream archivo("palabrasItaliano.txt");
    if (archivo.is_open()) {
        string palabraItaliano, palabraEspanol;
        while (archivo >> palabraItaliano >> palabraEspanol) {
            diccionario.agregarPalabra(palabraItaliano, palabraEspanol);
        }
        archivo.close();
    } else {
        cout << "Error al abrir el archivo" << endl;
    }
}

// Funci�n para encriptar una palabra seg�n las reglas proporcionadas
string encriptarPalabra(const string& palabra, const unordered_map<string, string>& reglas) {
    string encriptada;
    for (size_t i = 0; i < palabra.length(); ++i) {
        // Verificar si la palabra est� en las reglas de encriptaci�n
        string subpalabra = palabra.substr(i, 1); // Obtener la subpalabra de longitud 1
        if (reglas.find(subpalabra) != reglas.end()) {
            encriptada += reglas.at(subpalabra);
        } else {
            encriptada += subpalabra; // Si la palabra no est� en las reglas, mantenerla sin cambios
        }
    }
    return encriptada;
}


// Funci�n para encriptar un archivo de texto seg�n las reglas proporcionadas
void encriptarArchivo(const string& nombreArchivoEntrada, const string& nombreArchivoSalida, const unordered_map<string, string>& reglas) {
    ifstream archivoEntrada(nombreArchivoEntrada);
    ofstream archivoSalida(nombreArchivoSalida);

    if (archivoEntrada.is_open() && archivoSalida.is_open()) {
        string palabraTraduccion, palabraEspanol;
        while (archivoEntrada >> palabraEspanol >> palabraTraduccion) {
            string palabraEncriptadaEspanol = encriptarPalabra(palabraEspanol, reglas);
            string palabraEncriptadaTraduccion = encriptarPalabra(palabraTraduccion, reglas);
            archivoSalida << palabraEncriptadaEspanol << " " << palabraEncriptadaTraduccion << endl;
        }
        archivoEntrada.close();
        archivoSalida.close();
        cout << "Archivo encriptado correctamente." << endl;
    } else {
        cout << "Error al abrir los archivos." << endl;
    }
}




string verificarUsuario() {
// Declaraci�n de variables locales
string usuario, contrasena;  // Almacenan el usuario y la contrase�a ingresados
int contador = 0;  // Contador de intentos
bool encontrado = false;  // Indica si se encontr� el usuario y la contrase�a correctos

while (contador < 3 && !encontrado) {

    system("cls");
    cout <<"\t\t\t----------------------"<<endl;
    cout <<"\t\t\t| INGRESO DE USUARIO |"<<endl;
    cout <<"\t\t\t----------------------"<<endl;

    cout <<"\n\t���Advertencia: Solo tienes permitido 3 intentos!!!"<<endl;
    cout <<"\t---------------------------------------------------"<<endl;

    cout << "\t\t\t\nIngrese el nombre de usuario:         ";
    cin >> usuario;
    cout << "\t\t\t\nIngrese la contrasena:                ";
    char caracter;
    caracter = getch();

    // Ocultar la contrase�a ingresada por el usuario
    contrasena = "";
    while (caracter != 13){
        if(caracter != 8)
        {
            contrasena.push_back(caracter);
            cout<< "*";
        }else{
            if(contrasena.length()>0)
            {
                cout<<"\b \b";
                contrasena = contrasena.substr(0, contrasena.length() - 1);
            }
        }
        caracter = getch();
    }

    // Abrir el archivo de usuarios y contrase�as
    ifstream file;
    file.open("Usuarios.txt", ios::in);

    // Verificar si el archivo se abri� correctamente
    if (!file) {
        cout << "No se pudo abrir el archivo." << endl;
        file.close();
        return " ";
    }

    // Buscar el usuario en el archivo
    string user, pass;
    while (file >> user >> pass) {
        if (user == usuario && pass == contrasena) {
            encontrado = true;
            usuarioAutenticado = usuario;
            break;
        }
    }
    file.close();

    // Si no se encontr� el usuario, se incrementa el contador
    if (!encontrado) {
        cout << "\n\tUSUARIO Y/O PASSWORD INCORRECTOS" << endl;
        cout << "\n\tPerdio un intento, Intente de nuevo" << endl;
        contador++;
        system("pause");
    }
}

// Si se encontr� el usuario, se retorna true
if (encontrado) {
    return usuario;
} else {
    cout << "\n\tPERDIO LOS 3 INTENTOS" << endl;
    cout << "\n\tNO PODRA INGRESAR MAS INTENTOS" << endl;
    return " ";
}
}

bool crearCarpetaUsuario(const std::string& nombreCarpeta) {
    try {
        // Construir la ruta completa de la carpeta
        string rutaCarpeta = "C:\\Users\\HP\\OneDrive\\Desktop\\Programacion 3\\prototipoAVL\\" + nombreCarpeta;

        if (CreateDirectoryA(rutaCarpeta.c_str(), NULL)) {
            return true;
        } else {
            std::cerr << "Error al crear la carpeta: " << rutaCarpeta << std::endl;
            return false;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
}

void palabraHistorial(string palabra) {
    ofstream archivo("palabrasHistorial.txt", std::ios::app); // Abrir el archivo en modo "append"
    
    if (archivo.is_open()) {
        archivo << palabra << "\n"; // Escribir la palabra en el archivo seguida de un salto de l�nea
        archivo.close(); // Cerrar el archivo
        cout << "La palabra '" << palabra << "' se ha agregado al archivo." <<endl;
    } else {
        cout << "No se pudo abrir el archivo." <<endl;
    }
}
void obtenerPalabrasRepetidas() {
    ifstream archivo("palabrasHistorial.txt"); // Abrir el archivo en modo lectura
    unordered_set<string> palabras; // Contenedor para almacenar las palabras �nicas
    unordered_set<string> palabrasReportadas; // Contenedor para almacenar las palabras ya reportadas
    string palabra;
    
    if (archivo.is_open()) {
        while (getline(archivo, palabra)) { // Leer cada l�nea del archivo
            if (palabras.find(palabra) == palabras.end()) { // Si la palabra no est� en el contenedor
                palabras.insert(palabra); // Agregar la palabra al contenedor
            } else if (palabrasReportadas.find(palabra) == palabrasReportadas.end()) { // Si la palabra no ha sido reportada a�n
                cout << "La palabra '" << palabra << "' es una de las mas buscadas." << endl;
                palabrasReportadas.insert(palabra); // Marcar la palabra como reportada
            }
        }
        archivo.close(); // Cerrar el archivo
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}


void traductorEspanolIngles(){
	int choice;
    do{

    system("cls");
    

    cout <<"\t\t\t----------------------------------"<<endl;
    cout <<"\t\t\t|    Traductor Espa�ol a Ingles     |"<<endl;
    cout <<"\t\t\t----------------------------------"<<endl;
	cout<<"\t\t\t 1. Traducir Palabras"<<endl;
	cout<<"\t\t\t 2. Agregar una Nueva Palabra"<<endl;
	cout<<"\t\t\t 3. Mostrar Palabras agregadas"<<endl;
	cout<<"\t\t\t 4. Eliminar una Palabra"<<endl;
	cout<<"\t\t\t 5. Exit"<<endl;

	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"\t\t\tOpcion a escoger:[1/2/3]"<<endl;
	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"Ingresa tu Opcion: ";
    cin>>choice;
    
    switch(choice){
    	case 1:
    		{
    			set<string> palabras;
    			DiccionarioAVL diccionario;
               leerPalabras(diccionario);
               
               string archivo = "palabras.txt";

    
    char pregu;
    string palabra;
    cout << "Ingrese una palabra en espanol: ";
    cin >> palabra;
    
    palabraHistorial(palabra);
    

    string traduccion;

    if ((traduccion = diccionario.traducirEspanolIngles(palabra)) != "Palabra no encontrada") {
        cout << "Traduccion: " << traduccion << endl;
        system("pause");
    } else {
        cout << "Palabra no encontrada" << endl;
        system("pause");
    }
    
    do{
    string rutaBase = "C:\\Users\\HP\\OneDrive\\Desktop\\Programacion 3\\Proyecto_Prototipo\\sonidos\\";
    string nombreArchivo;
    nombreArchivo=traduccion + ".wav";
    string rutaCompleta = rutaBase + nombreArchivo;
	PlaySound(TEXT(rutaCompleta.c_str()), NULL, SND_FILENAME | SND_ASYNC);
	cout<<"Deseas escuchar de nuevo la pronunciacion en ingles?"<<endl;
	cin>>pregu;
	system("pause");
	}while(pregu == 'y');
			}
		break;
	case 2:
		{
			string rutaCarpeta = "C:\\Users\\HP\\OneDrive\\Desktop\\Programacion 3\\prototipoAVL\\" + usuarioAutenticado;
			DiccionarioAVL diccionario;
            string nombreArchivo = "palabrasIngles"+usuarioAutenticado+".txt";
            string espanol, ingles;
            char opcion;

            do {
                cout << "Ingrese una palabra en espa�ol: ";
                cin >> espanol;

                cout << "Ingrese la traducci�n al ingles: ";
                cin >> ingles;

                diccionario.agregarPalabrasIngles (rutaCarpeta, nombreArchivo, espanol, ingles);
                //diccionario.agregarPalabraRec(diccionario.raiz, espanol, ingles);

                cout << "�Desea agregar otra palabra? (s/n): ";
                cin >> opcion;
               } while (opcion == 's' || opcion == 'S');
  
                cout << "Palabras agregadas correctamente al archivo." << endl;
			}
            break;
	case 3:
	{
		DiccionarioAVL diccionario;
		leerPalabras(diccionario);
		diccionario.mostrarPalabras();
		system("pause");
		system("cls");
		cout << "Arbol AVL:" << endl;
        diccionario.mostrarArbol(diccionario.obtenerRaiz());
        cout << endl;
		system("pause");
	}
	break;
	case 4:
	{
		DiccionarioAVL diccionario;
		leerPalabras(diccionario);
		string palabra;
        cout << "Ingrese una palabra en espa�ol a eliminar: ";
        cin >> palabra;
        diccionario.eliminarPalabra(palabra);
        string rutaCarpeta = "C:\\Users\\HP\\OneDrive\\Desktop\\Programacion 3\\prototipoAVL\\"+usuarioAutenticado+"\\";
        eliminarPalabraUsuario(rutaCarpeta, "palabrasIngles" + usuarioAutenticado + ".txt", palabra);
        //diccionario.eliminarPalabraRec(palabra);
        cout << "Palabra eliminada correctamente." << endl;
        system("pause");
	}
	break;	
	case 5:
		return;
	}
	} while(choice!= 5);
	
}
void traductorEspanolAleman(){
	system("cls");
	int choice;
    do{

    system("cls");

    cout <<"\t\t\t----------------------------------"<<endl;
    cout <<"\t\t\t|    Traductor Espa�ol a Aleman     |"<<endl;
    cout <<"\t\t\t----------------------------------"<<endl;
	cout<<"\t\t\t 1. Traducir Palabras"<<endl;
	cout<<"\t\t\t 2. Agregar una Nueva Palabra"<<endl;
	cout<<"\t\t\t 3. Mostrar Palabras agregadas"<<endl;
	cout<<"\t\t\t 4. Eliminar una Palabra"<<endl;
	cout<<"\t\t\t 5. Exit"<<endl;

	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"\t\t\tOpcion a escoger:[1/2/3]"<<endl;
	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"Ingresa tu Opcion: ";
    cin>>choice;
    
    switch(choice){
    	case 1:
    		{
    			set<string> palabras;
    			DiccionarioAVLalem diccionario;
    leerPalabras(diccionario);
    string archivo = "palabras.txt";
    char pregu;
    string palabra;
    cout << "Ingrese una palabra en espanol: ";
    cin >> palabra;
    palabraHistorial(palabra);

    string traduccion;

    if ((traduccion = diccionario.traducirEspanolAleman(palabra)) != "Palabra no encontrada") {
        cout << "Traduccion: " << traduccion << endl;
        system("pause");
    } else {
        cout << "Palabra no encontrada" << endl;
        system("pause");
    }
    
    do{
    string rutaBase = "C:\\Users\\HP\\OneDrive\\Desktop\\Programacion 3\\Proyecto_Prototipo\\audioAleman\\";
    string nombreArchivo;
    nombreArchivo=palabra + ".wav";
    string rutaCompleta = rutaBase + nombreArchivo;
	PlaySound(TEXT(rutaCompleta.c_str()), NULL, SND_FILENAME | SND_ASYNC);
	cout<<"Deseas escuchar de nuevo la pronunciacion en Aleman?"<<endl;
	cin>>pregu;
	system("pause");
	}while(pregu == 'y');
			}
		break;
	case 2:
		{
			string rutaCarpeta = "C:\\Users\\HP\\OneDrive\\Desktop\\Programacion 3\\prototipoAVL\\" + usuarioAutenticado;
			DiccionarioAVLalem diccionario;
            string nombreArchivo = "palabrasAleman"+usuarioAutenticado+".txt";
            string espanol, aleman;
            char opcion;

            do {
                cout << "Ingrese una palabra en espa�ol: ";
                cin >> espanol;

                cout << "Ingrese la traducci�n al Aleman: ";
                cin >> aleman;

                diccionario.agregarPalabras(rutaCarpeta, nombreArchivo, espanol, aleman);
                //diccionario.agregarPalabraRec(diccionario.raiz, espanol, ingles);

                cout << "�Desea agregar otra palabra? (s/n): ";
                cin >> opcion;
               } while (opcion == 's' || opcion == 'S');
  
                cout << "Palabras agregadas correctamente al archivo." << endl;
		}
            break;
case 3:
	{
		DiccionarioAVLalem diccionario;
		leerPalabras(diccionario);
		diccionario.mostrarPalabras();
		system("pause");
		system("cls");
		cout << "Arbol AVL:" << endl;
        diccionario.mostrarArbol(diccionario.obtenerRaiz());
        cout << endl;
		system("pause");
	}
	break;
	case 4:
	{
		DiccionarioAVLalem diccionario;
		leerPalabras(diccionario);
		string palabra;
        cout << "Ingrese una palabra en espa�ol a eliminar: ";
        cin >> palabra;
        diccionario.eliminarPalabra(palabra);
        string rutaCarpeta = "C:\\Users\\HP\\OneDrive\\Desktop\\Programacion 3\\prototipoAVL\\"+usuarioAutenticado+"\\";
        eliminarPalabraUsuario(rutaCarpeta, "palabrasAleman" + usuarioAutenticado + ".txt", palabra);
        //diccionario.eliminarPalabraRec(palabra);
        cout << "Palabra eliminada correctamente." << endl;
        system("pause");
	}
	break;	
	case 5:
		return;
	}
	} while(choice!= 5);
	
}
void traductorEspanolFrances(){
	system("cls");
	int choice;
    do{

    system("cls");

    cout <<"\t\t\t----------------------------------"<<endl;
    cout <<"\t\t\t|    Traductor Espa�ol a Frances     |"<<endl;
    cout <<"\t\t\t----------------------------------"<<endl;
	cout<<"\t\t\t 1. Traducir Palabras"<<endl;
	cout<<"\t\t\t 2. Agregar una Nueva Palabra"<<endl;
	cout<<"\t\t\t 3. Mostrar Palabras agregadas"<<endl;
	cout<<"\t\t\t 4. Eliminar una Palabra"<<endl;
	cout<<"\t\t\t 5. Exit"<<endl;

	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"\t\t\tOpcion a escoger:[1/2/3]"<<endl;
	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"Ingresa tu Opcion: ";
    cin>>choice;
    
    switch(choice){
    	case 1:
    		{
    			set<string> palabras;
    			DiccionarioAVLFran diccionario;
    leerPalabras(diccionario);
    string archivo = "palabras.txt";	
    char pregu;
    string palabra;
    cout << "Ingrese una palabra en espanol: ";
    cin >> palabra;
    palabraHistorial(palabra);

    string traduccion;

    if ((traduccion = diccionario.traducirFrancesEspanol(palabra)) != "Palabra no encontrada") {
        cout << "Traduccion: " << traduccion << endl;
        system("pause");
    } else {
        cout << "Palabra no encontrada" << endl;
        system("pause");
    }
    
    do{
    string rutaBase = "C:\\Users\\HP\\OneDrive\\Desktop\\Programacion 3\\Proyecto_Prototipo\\audioFrances\\";
    string nombreArchivo;
    nombreArchivo=traduccion + ".wav";
    string rutaCompleta = rutaBase + nombreArchivo;
	PlaySound(TEXT(rutaCompleta.c_str()), NULL, SND_FILENAME | SND_ASYNC);
	cout<<"Deseas escuchar de nuevo la pronunciacion en Frances?"<<endl;
	cin>>pregu;
	system("pause");
	}while(pregu == 'y');
			}
		break;
	case 2:
		{
			string rutaCarpeta = "C:\\Users\\HP\\OneDrive\\Desktop\\Programacion 3\\prototipoAVL\\" + usuarioAutenticado;
			DiccionarioAVLFran diccionario;
            string nombreArchivo = "palabrasFrances"+usuarioAutenticado+".txt";
            string espanol, frances;
            char opcion;

            do {
                cout << "Ingrese una palabra en espa�ol: ";
                cin >> espanol;

                cout << "Ingrese la traducci�n al Frances: ";
                cin >> frances;

                diccionario.agregarPalabras(rutaCarpeta, nombreArchivo, espanol, frances);
                //diccionario.agregarPalabraRec(diccionario.raiz, espanol, ingles);

                cout << "�Desea agregar otra palabra? (s/n): ";
                cin >> opcion;
               } while (opcion == 's' || opcion == 'S');
  
                cout << "Palabras agregadas correctamente al archivo." << endl;
		}
            break;
	case 3:
	{
		DiccionarioAVLFran  diccionario;
		leerPalabras(diccionario);
		diccionario.mostrarPalabras();
		system("pause");
		system("cls");
		cout << "Arbol AVL:" << endl;
        diccionario.mostrarArbol();
        cout << endl;
		system("pause");
	}
	break;
	case 4:
	{
		DiccionarioAVLFran  diccionario;
		leerPalabras(diccionario);
		string palabra;
        cout << "Ingrese una palabra en espa�ol a eliminar: ";
        cin >> palabra;
        diccionario.eliminarPalabra(palabra);
        string rutaCarpeta = "C:\\Users\\HP\\OneDrive\\Desktop\\Programacion 3\\prototipoAVL\\"+usuarioAutenticado+"\\";
        eliminarPalabraUsuario(rutaCarpeta, "palabrasFrances" + usuarioAutenticado + ".txt", palabra);
        //diccionario.eliminarPalabraRec(palabra);
        cout << "Palabra eliminada correctamente." << endl;
        system("pause");
	}
	break;	
	case 5:
		return;
	}
	} while(choice!= 5);
	
}
void traductorEspanolItaliano(){
	system("cls");
	int choice;
    do{

    system("cls");

    cout <<"\t\t\t----------------------------------"<<endl;
    cout <<"\t\t\t|    Traductor Espa�ol a Italiano     |"<<endl;
    cout <<"\t\t\t----------------------------------"<<endl;
	cout<<"\t\t\t 1. Traducir Palabras"<<endl;
	cout<<"\t\t\t 2. Agregar una Nueva Palabra"<<endl;
	cout<<"\t\t\t 3. Mostrar Palabras agregadas"<<endl;
	cout<<"\t\t\t 4. Eliminar una Palabra"<<endl;
	cout<<"\t\t\t 5. Exit"<<endl;

	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"\t\t\tOpcion a escoger:[1/2/3]"<<endl;
	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"Ingresa tu Opcion: ";
    cin>>choice;
    
    switch(choice){
    	case 1:
    		{
    			set<string> palabras;
    			DiccionarioAVLItal diccionario;
               leerPalabras(diccionario);
               
               string archivo = "palabras.txt";

    
    char pregu;
    string palabra;
    cout << "Ingrese una palabra en espanol: ";
    cin >> palabra;

    string traduccion;

    if ((traduccion = diccionario.traducirItalianoEspanol(palabra)) != "Palabra no encontrada") {
        cout << "Traduccion: " << traduccion << endl;
        system("pause");
    } else {
        cout << "Palabra no encontrada" << endl;
        system("pause");
    }
    
    do{
    string rutaBase = "C:\\Users\\HP\\OneDrive\\Desktop\\Programacion 3\\Proyecto_Prototipo\\audioItaliano\\";
    string nombreArchivo;
    nombreArchivo=traduccion + ".wav";
    string rutaCompleta = rutaBase + nombreArchivo;
	PlaySound(TEXT(rutaCompleta.c_str()), NULL, SND_FILENAME | SND_ASYNC);
	cout<<"Deseas escuchar de nuevo la pronunciacion en Italiano?"<<endl;
	cin>>pregu;
	system("pause");
	}while(pregu == 'y');
			}
		break;
	case 2:
		{
			string rutaCarpeta = "C:\\Users\\HP\\OneDrive\\Desktop\\Programacion 3\\prototipoAVL\\" + usuarioAutenticado;
			DiccionarioAVLItal diccionario;
            string nombreArchivo = "palabrasItaliano"+usuarioAutenticado+".txt";
            string espanol, Italiano;
            char opcion;

            do {
                cout << "Ingrese una palabra en espa�ol: ";
                cin >> espanol;

                cout << "Ingrese la traducci�n al Italiano: ";
                cin >> Italiano;

                diccionario.agregarPalabras(rutaCarpeta, nombreArchivo, espanol, Italiano);
                //diccionario.agregarPalabraRec(diccionario.raiz, espanol, ingles);

                cout << "�Desea agregar otra palabra? (s/n): ";
                cin >> opcion;
               } while (opcion == 's' || opcion == 'S');
  
                cout << "Palabras agregadas correctamente al archivo." << endl;
		}
            break;
	case 3:
	{
		DiccionarioAVLItal diccionario;
		leerPalabras(diccionario);
		diccionario.mostrarPalabras();
		system("pause");
		system("cls");
		cout << "Arbol AVL:" << endl;
        diccionario.mostrarArbol();
        cout << endl;
		system("pause");
	}
	break;
	case 4:
	{
		DiccionarioAVLItal diccionario;
		leerPalabras(diccionario);
		string palabra;
        cout << "Ingrese una palabra en espa�ol a eliminar: ";
        cin >> palabra;
        diccionario.eliminarPalabra(palabra);
        string rutaCarpeta = "C:\\Users\\HP\\OneDrive\\Desktop\\Programacion 3\\prototipoAVL\\"+usuarioAutenticado+"\\";
        eliminarPalabraUsuario(rutaCarpeta, "palabrasItaliano" + usuarioAutenticado + ".txt", palabra);
        //diccionario.eliminarPalabraRec(palabra);
        cout << "Palabra eliminada correctamente." << endl;
        system("pause");
	}
	break;	
	case 5:
		return;
	}
	} while(choice!= 5);
	
}


void ingresarUsuarios(){
    system("cls");
    fstream file;//objeto "fstream" para manejar archivos

    // Declaraci�n de variables
    string usuario, contrasena;

    // Imprime mensaje y solicita al usuario que ingrese el nombre de usuario y la contrase�a
    cout<<"\n-------------------------------------------------Agregar Usuarios al Sistema--------------------------------------------"<<endl;
    cout << "\t\t\t\nIngrese el nombre de usuario:         ";
    cin >> usuario;
    cout << "\t\t\t\nIngrese la contrasena:         ";

// Inicia la entrada de caracteres uno por uno, ocultando la contrase�a con asteriscos
char caracter;
caracter = getch();
contrasena = "";

    string nombreCarpeta = usuario;
    crearCarpetaUsuario(nombreCarpeta);
while (caracter != 13){ // El bucle se ejecuta hasta que el usuario presiona la tecla "Enter" (c�digo ASCII 13)
    if(caracter != 8) // Si el caracter ingresado no es "Backspace" (c�digo ASCII 8)
    {
        contrasena.push_back(caracter); // Agrega el caracter ingresado al final de la cadena "contrasena"
        cout<< "*"; // Imprime un asterisco en la consola
    }else{ // Si el caracter ingresado es "Backspace"
        if(contrasena.length()>0) // Si la cadena "contrasena" tiene al menos un caracter
        {
            cout<<"\b \b"; // Borra el �ltimo caracter ingresado de la consola (mueve el cursor una posici�n a la izquierda, imprime un espacio en blanco y mueve el cursor de nuevo a la izquierda)
            contrasena = contrasena.substr(0, contrasena.length() - 1); // Elimina el �ltimo caracter ingresado de la cadena "contrasena"
        }
    }
    caracter = getch(); // Lee el siguiente caracter ingresado por el usuario
}

// Abre el archivo "Usuarios1.txt" en modo de apendizaje y escritura
file.open("Usuarios.txt", ios::app | ios::out);

// Escribe en el archivo los datos del usuario ingresados por el usuario, con un ancho de 15 caracteres para cada campo
file<<std::left<<std::setw(15)<< usuario <<std::left<<std::setw(15)<< contrasena << "\n";

// Cierra el archivo
file.close();

// Imprime mensaje de �xito
cout << "\t\t\t\nUsuario registrado exitosamente.";
}
void desplegarUsurios()
{
    system("cls"); // limpia la pantalla de la consola
	fstream file; // crea un objeto de archivo de la biblioteca fstream
	int total=0; // inicializa una variable para contar el n�mero de usuarios

	// Imprime el encabezado para la tabla de usuarios registrados
	cout<<"\n-------------------------Tabla de Usuarios Registrados-------------------------"<<endl;

	file.open("Usuarios.txt",ios::in); // abre el archivo "Usuarios1.txt" en modo lectura
	if(!file) // si no se pudo abrir el archivo
	{
		cout<<"\n\t\t\tNo hay informaci�n..."; // muestra un mensaje de error
		file.close(); // cierra el archivo
	}
	else // si se pudo abrir el archivo
	{
		string usuario, contrasena;
		file >> usuario >> contrasena; // lee el primer usuario del archivo

		// mientras no se llegue al final del archivo
		while(!file.eof())
		{
			total++; // incrementa el contador de usuarios
			cout<<"\t\t\t Nombre de usuario: "<<usuario<<endl; // muestra el nombre del usuario
			cout<<"\t\t\t Contrasena del usuario: "<<contrasena<<endl; // muestra la contrase�a del usuario
			file >> usuario >> contrasena; // lee el siguiente usuario del archivo
		}

		if(total==0) // si no se encontr� ning�n usuario en el archivo
		{
			cout<<"\n\t\t\tNo hay informacion..."; // muestra un mensaje de error
		}
	}

	file.close(); // cierra el archivo
}
void menuUsuarios(){
    int choice; // Se declara la variable choice para almacenar la opci�n elegida por el usuario
	char x; // Se declara la variable x para almacenar la respuesta del usuario al preguntar si quiere agregar otra persona
	do
    {
	system("cls"); // Se limpia la pantalla
    cout <<"\t\t\t------------------------------"<<endl; // Se imprime un mensaje de bienvenida al men� de usuarios
    cout <<"\t\t\t |MENU DE PROCESO DE USUARIOS|"<<endl;
    cout <<"\t\t\t------------------------------"<<endl;
    cout<<"\t\t\t 1. Ingresar un Usuario"<<endl; // Se imprime la opci�n para modificar usuarios
	cout<<"\t\t\t 2. Desplegar Usuarios"<<endl;
	cout<<"\t\t\t 3. Exit"<<endl; // Se imprime la opci�n para salir

	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"\t\t\tOpcion a escoger:[1/2/3]"<<endl; // Se imprime una l�nea indicando que se debe elegir una opci�n
	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"Ingresa tu Opcion: ";
    cin>>choice; // Se lee la opci�n elegida por el usuario

    switch(choice) // Se utiliza un switch para ejecutar el c�digo correspondiente a la opci�n elegida por el usuario
    {
    case 1:
         do // Se utiliza un do-while para permitir al usuario agregar m�s de una persona
    	{
    		ingresarUsuarios(); // Se llama al m�todo para ingresar nuevos usuarios
    		cout<<"\n\t\t\t Agrega otra persona(Y,N): ";
    		cin>>x; // Se pregunta al usuario si desea agregar otra persona
		}while(x=='y'||x=='Y'); // Se repite el ciclo mientras la respuesta del usuario sea afirmativa
		break;
    case 2:
		desplegarUsurios(); // Se llama al m�todo para modificar usuarios
		break;
    case 3:
	    return;
	default:
		cout<<"\n\t\t\t Opcion invalida...Por favor prueba otra vez.."; // Se imprime un mensaje de error si la opci�n elegida es inv�lida
	}
	getch(); // Se espera a que el usuario presione una tecla para continuar
    }while(choice!= 3); // Se repite el ciclo mientras la opci�n elegida por el usuario sea diferente a 6 (salida del men�)
}


void menuTraductor(){
    string rutaCarpeta = "C:\\Users\\HP\\OneDrive\\Desktop\\Programacion 3\\prototipoAVL\\"+usuarioAutenticado+"\\";
	unordered_map<string, string> reglas = {
        {"a", "U1"},
        {"e", "U2"},
        {"i", "U3"},
        {"o", "U4"},
        {"u", "U5b"},
        {"c", "m2"},
        {"d", "m3"},
        {"f", "m4"},
        {"g", "m5"},
        {"h", "m6"},
        {"j", "m7"},
        {"k", "m8"},
        {"l", "m9"},
        {"m", "m10"},
        {"n", "m11"},
        {"�", "m12"},
        {"p", "m13"},
        {"q", "m14"},
        {"r", "m15"},
        {"s", "m16"},
        {"t", "m17"},
        {"v", "m18"},
        {"w", "m19"},
        {"x", "m20"},
        {"y", "m21"},
        {"z", "m22B"},
        {"C", "g2"},
        {"D", "g3"},
        {"F", "g4"},
        {"G", "g5"},
        {"H", "g6"},
        {"J", "g7"},
        {"K", "g8"},
        {"L", "g9"},
        {"M", "g10"},
        {"N", "g11"},
        {"�", "g12"},
        {"P", "g13"},
        {"Q", "g14"},
        {"R", "g15"},
        {"S", "g16"},
        {"T", "g17"},
        {"V", "g18"},
        {"W", "g19"},
        {"X", "g20"},
        {"Y", "g21"},
        {"Z", "g22"}
    };
    
    system("cls");
    cout <<"\t\t\t----------------------------------"<<endl;
    cout <<"\t\t\t|          TOP BUSQUEDAS          |"<<endl;
    cout <<"\t\t\t----------------------------------"<<endl;
    obtenerPalabrasRepetidas();
    system("pause");
    system("cls");
    
	int choice;
    do{
    	system("cls");
    	cout << "Usuario autenticado: " << usuarioAutenticado << endl;

    cout <<"\t\t\t----------------------------------"<<endl;
    cout <<"\t\t\t|          Traductor            |"<<endl;
    cout <<"\t\t\t----------------------------------"<<endl;
	cout<<"\t\t\t 1. Traductor de Espanol a ingles"<<endl;
	cout<<"\t\t\t 2. Traductor de Espanol a Italiano"<<endl;
	cout<<"\t\t\t 3. Traductor de Espanol a Aleman"<<endl;
	cout<<"\t\t\t 4. Traductor de Espanol a Frances"<<endl;
	cout<<"\t\t\t 5. Exit"<<endl;

	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"\t\t\tOpcion a escoger:[1/2/3/4/5]"<<endl;
	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"Ingresa tu Opcion: ";
    cin>>choice;
    
    switch(choice)
    {
    case 1:
    	{
    	traductorEspanolIngles();
    	encriptarArchivo("palabrasIngles.txt", "encriptadoIngles.txt", reglas);
        encriptarArchivo(rutaCarpeta+"palabrasIngles"+usuarioAutenticado+".txt",rutaCarpeta+"encriptadoIngles"+usuarioAutenticado+".txt", reglas);
		}
		break;
	case 2:
	    traductorEspanolItaliano();
	    encriptarArchivo("palabrasItaliano.txt", "encriptadoItaliano.txt", reglas);
	    encriptarArchivo(rutaCarpeta+"palabrasItaliano"+usuarioAutenticado+".txt",rutaCarpeta+"encriptadoItaliano"+usuarioAutenticado+".txt", reglas);
	    break;
	case 3:
	    traductorEspanolAleman();
	    encriptarArchivo("palabrasAleman.txt", "encriptadoAleman.txt", reglas);
	    encriptarArchivo(rutaCarpeta+"palabrasAleman"+usuarioAutenticado+".txt",rutaCarpeta+"encriptadoAleman"+usuarioAutenticado+".txt", reglas);
	    break;
	case 4:
	    traductorEspanolFrances();
	    encriptarArchivo("palabrasFrances.txt", "encriptadoFrances.txt", reglas);
	    encriptarArchivo(rutaCarpeta+"palabrasFrances"+usuarioAutenticado+".txt",rutaCarpeta+"encriptadoFrances"+usuarioAutenticado+".txt", reglas);
	    break;
	case 5:
	    return;
	}
	} while(choice!= 5);
}


int main() {
	
		unordered_map<string, string> reglas = {
        {"a", "U1"},
        {"e", "U2"},
        {"i", "U3"},
        {"o", "U4"},
        {"u", "U5b"},
        {"c", "m2"},
        {"d", "m3"},
        {"f", "m4"},
        {"g", "m5"},
        {"h", "m6"},
        {"j", "m7"},
        {"k", "m8"},
        {"l", "m9"},
        {"m", "m10"},
        {"n", "m11"},
        {"�", "m12"},
        {"p", "m13"},
        {"q", "m14"},
        {"r", "m15"},
        {"s", "m16"},
        {"t", "m17"},
        {"v", "m18"},
        {"w", "m19"},
        {"x", "m20"},
        {"y", "m21"},
        {"z", "m22B"},
        {"C", "g2"},
        {"D", "g3"},
        {"F", "g4"},
        {"G", "g5"},
        {"H", "g6"},
        {"J", "g7"},
        {"K", "g8"},
        {"L", "g9"},
        {"M", "g10"},
        {"N", "g11"},
        {"�", "g12"},
        {"P", "g13"},
        {"Q", "g14"},
        {"R", "g15"},
        {"S", "g16"},
        {"T", "g17"},
        {"V", "g18"},
        {"W", "g19"},
        {"X", "g20"},
        {"Y", "g21"},
        {"Z", "g22"}
    };
    
    cout << "\t\t\t----------------------------------------------------" <<endl;
    cout << "\t\t\t|     Universidad Mariano Galvez de Guatemala      |" <<endl;
    cout << "\t\t\t|                                                  |" <<endl;
    cout << "\t\t\t|              #     # #     #  #####              |" <<endl;
    cout << "\t\t\t|              #     # ##   ## #     #             |" <<endl;
    cout << "\t\t\t|              #     # # # # # #                   |" <<endl;
    cout << "\t\t\t|              #     # #  #  # #  ####             |" <<endl;
    cout << "\t\t\t|              #     # #     # #     #             |" <<endl;
    cout << "\t\t\t|              #     # #     # #     #             |" <<endl;
    cout << "\t\t\t|               #####  #     #  #####              |" <<endl;
    cout << "\t\t\t|                                                  |" <<endl;
    cout << "\t\t\t|                     Grupo 3                      |" <<endl;
    cout << "\t\t\t|  Giovanni Steve Cifuentes Palencia 9989-22-1822  |" <<endl;
    cout << "\t\t\t|  Jorge David Gatica Garcia 9989-22-128           |" <<endl;
    cout << "\t\t\t|  Geovany Marcelino Jimenez Miranda 9989-19-13602 |" <<endl;
    cout << "\t\t\t|                                                  |" <<endl;
    cout << "\t\t\t|                     Proyecto                     |" <<endl;
    cout << "\t\t\t|               Traductor Encriptador              |" <<endl;
    cout << "\t\t\t----------------------------------------------------" <<endl;
    
	system("pause");
	system("cls");
    string usuario = verificarUsuario();
    system("cls");
    if (!usuario.empty()) {
    cout << "Usuario Ingresado: " << usuarioAutenticado << endl;
    int choice;
    do{	

    cout <<"\t\t\t----------------------------------"<<endl;
    cout <<"\t\t\t|          Menu Principal           |"<<endl;
    cout <<"\t\t\t----------------------------------"<<endl;
	cout<<"\t\t\t 1. Menu de Usuarios"<<endl;
	cout<<"\t\t\t 2. Traductor"<<endl;
	cout<<"\t\t\t 3. Salir"<<endl;

	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"\t\t\tOpcion a escoger:[1/2/3]"<<endl;
	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"Ingresa tu Opcion: ";
    cin>>choice;
    
    switch(choice)
    {
    case 1:
    	menuUsuarios();
    	encriptarArchivo("Usuarios.txt", "encriptadoUsuarios.txt", reglas);
    	system("cls");
		break;
	case 2:
		menuTraductor();
	case 3:
		return 0;
	}
	} while(choice!= 2);
}
}

