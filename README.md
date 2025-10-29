# Traductor-Encriptador
El proyecto constara de 3 Fases, las cuales permitirán el desempeñando, cada una de las habilidades adquiridas.
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <windows.h>
 
using namespace std;

//INGLES
/*// Nodo que representa una palabra en el diccionario
struct Nodo {
    string palabraEspanol;
    string palabraIngles;
    Nodo* siguiente;

    Nodo(const string& espanol, const string& ingles)
        : palabraEspanol(espanol), palabraIngles(ingles), siguiente(NULL) {}
};

// Clase que representa el diccionario
class Diccionario {
private:
    Nodo* cabeza;

public:
    Diccionario() : cabeza(NULL) {}

    ~Diccionario() {
        while (cabeza) {
            Nodo* nodoAEliminar = cabeza;
            cabeza = cabeza->siguiente;
            delete nodoAEliminar;
        }
    }

    // Agrega una palabra al diccionario
    void agregarPalabra(const string& espanol, const string& ingles) {
        Nodo* nuevoNodo = new Nodo(espanol, ingles);
        nuevoNodo->siguiente = cabeza;
        cabeza = nuevoNodo;
    }
    void agregarPalabras(const string& espanol, const string& ingles) {
    ofstream archivo("palabrasIngles.txt", ios::app); // Abre el archivo en modo de apertura para agregar al final
    if (archivo.is_open()) {
        archivo << espanol << " " << ingles << endl; // Escribe las palabras en el archivo
        archivo.close(); // Cierra el archivo después de escribir
    } else {
        cout << "Error al abrir el archivo" << endl;
    }
}
void mostrarPalabras() const {
    cout << "Palabras agregadas:" << endl;
    Nodo* actual = cabeza;
    while (actual) {
        cout << "Espanol: " << actual->palabraEspanol << ",      Ingles: " << actual->palabraIngles << endl;
        actual = actual->siguiente;
    }
}
void eliminarPalabra(const string& espanol) {
    Nodo* anterior = NULL;
    Nodo* actual = cabeza;

    // Buscar el nodo a eliminar
    while (actual) {
        if (actual->palabraEspanol == espanol) {
            if (anterior) {
                anterior->siguiente = actual->siguiente; // Actualizar el enlace del nodo anterior
            } else {
                cabeza = actual->siguiente; // El nodo a eliminar es el primero, actualizar la cabeza
            }

            // Eliminar el nodo
            delete actual;

            // Eliminar la palabra del archivo
            eliminarPalabraArchivo(espanol);

            return;
        }

        anterior = actual;
        actual = actual->siguiente;
    }

    cout << "Palabra no encontrada" << endl;
}

void eliminarPalabraArchivo(const string& espanol) {
    ifstream archivoEntrada("palabrasIngles.txt");
    ofstream archivoSalida("temp.txt");

    if (archivoEntrada.is_open() && archivoSalida.is_open()) {
        string linea;
        while (getline(archivoEntrada, linea)) {
            istringstream iss(linea);
            string palabra;
            iss >> palabra;

            if (palabra != espanol) {
                archivoSalida << linea << endl;
            }
        }

        archivoEntrada.close();
        archivoSalida.close();

        // Reemplazar el archivo original con el archivo temporal
        remove("palabrasIngles.txt");
        rename("temp.txt", "palabrasIngles.txt");
    } else {
        cout << "Error al abrir los archivos" << endl;
    }
}


    // Traduce una palabra de español a inglés
    string traducirEspanolIngles(const string& palabra) {
        Nodo* actual = cabeza;
        while (actual) {
            if (actual->palabraEspanol == palabra) {
                return actual->palabraIngles;
            }
            actual = actual->siguiente;
        }
        return "Palabra no encontrada";
    }
};

// Lee las palabras del archivo de texto y las agrega al diccionario
void leerPalabras(Diccionario& diccionario) {
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
}*/

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

    // Función auxiliar para destruir el árbol
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

    // Función auxiliar para agregar una palabra recursivamente
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
            // Aquí simplemente se actualiza la palabra inglesa
            nodo->palabraIngles = ingles;
            return nodo;
        }

        nodo->altura = 1 + max(altura(nodo->izquierdo), altura(nodo->derecho));

        int balance = obtenerBalance(nodo);

        // Casos de rotación
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

    // Función para obtener la altura de un nodo
    int altura(NodoAVL* nodo) {
        if (nodo == NULL) return 0;
        return nodo->altura;
    }

    // Función para obtener el balance de un nodo
    int obtenerBalance(NodoAVL* nodo) {
        if (nodo == NULL) return 0;
        return altura(nodo->izquierdo) - altura(nodo->derecho);
    }

    // Rotación simple a la derecha
    NodoAVL* rotarDerecha(NodoAVL* y) {
        NodoAVL* x = y->izquierdo;
        NodoAVL* T2 = x->derecho;

        x->derecho = y;
        y->izquierdo = T2;

        y->altura = 1 + max(altura(y->izquierdo), altura(y->derecho));
        x->altura = 1 + max(altura(x->izquierdo), altura(x->derecho));

        return x;
    }

    // Rotación simple a la izquierda
    NodoAVL* rotarIzquierda(NodoAVL* x) {
        NodoAVL* y = x->derecho;
        NodoAVL* T2 = y->izquierdo;

        y->izquierdo = x;
        x->derecho = T2;

        x->altura = 1 + max(altura(x->izquierdo), altura(x->derecho));
        y->altura = 1 + max(altura(y->izquierdo), altura(y->derecho));

        return y;
    }

    // Función para traducir una palabra de español a inglés
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

    // Función para mostrar las palabras en orden (inorder traversal)
    void mostrarPalabras() {
        mostrarPalabrasRec(raiz);
    }

    // Función auxiliar para mostrar las palabras en orden
    void mostrarPalabrasRec(NodoAVL* nodo) {
        if (nodo != NULL) {
            mostrarPalabrasRec(nodo->izquierdo);
            cout << "Español: " << nodo->palabraEspanol << ", Inglés: " << nodo->palabraIngles << endl;
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

    // Casos de rotación
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

// Función para leer las palabras del archivo de texto y agregarlas al diccionario AVL
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

// Función para encriptar una palabra según las reglas proporcionadas
string encriptarPalabra(const string& palabra, const unordered_map<string, string>& reglas) {
    string encriptada;
    for (size_t i = 0; i < palabra.length(); ++i) {
        // Verificar si la palabra está en las reglas de encriptación
        string subpalabra = palabra.substr(i, 1); // Obtener la subpalabra de longitud 1
        if (reglas.find(subpalabra) != reglas.end()) {
            encriptada += reglas.at(subpalabra);
        } else {
            encriptada += subpalabra; // Si la palabra no está en las reglas, mantenerla sin cambios
        }
    }
    return encriptada;
}

// Función para encriptar un archivo de texto según las reglas proporcionadas
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

void traductorEspanolIngles(){
	system("cls");
	int choice;
    do{

    system("cls");

    cout <<"\t\t\t----------------------------------"<<endl;
    cout <<"\t\t\t|    Traductor Español a ingles     |"<<endl;
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
    			DiccionarioAVL diccionario;
    leerPalabras(diccionario);
    char pregu;
    string palabra;
    cout << "Ingrese una palabra en espanol: ";
    cin >> palabra;

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
			DiccionarioAVL diccionario;
            ofstream archivo("palabrasIngles.txt", ios::app);
            string espanol, ingles;
            char opcion;

            do {
                cout << "Ingrese una palabra en español: ";
                cin >> espanol;

                cout << "Ingrese la traducción al ingles: ";
                cin >> ingles;

                diccionario.agregarPalabra(espanol, ingles);
                //diccionario.agregarPalabraRec(diccionario.raiz, espanol, ingles);

                cout << "¿Desea agregar otra palabra? (s/n): ";
                cin >> opcion;
               } while (opcion == 's' || opcion == 'S');

                archivo.close();

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
        cout << "Ingrese una palabra en español a eliminar: ";
        cin >> palabra;
        diccionario.eliminarPalabra(palabra);
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

int main() {
	
	unordered_map<string, string> reglas = {
        {"a", "U1"},
        {"e", "U2"},
        {"i", "U3"},
        {"o", "U4"},
        {"u", "U5"},
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
        {"ñ", "m12"},
        {"p", "m13"},
        {"q", "m14"},
        {"r", "m15"},
        {"s", "m16"},
        {"t", "m17"},
        {"v", "m18"},
        {"w", "m19"},
        {"x", "m20"},
        {"y", "m21"},
        {"z", "m22"},
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
        {"Ñ", "g12"},
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
    
    
	int choice;
    do{

    system("cls");

    cout <<"\t\t\t----------------------------------"<<endl;
    cout <<"\t\t\t|          Traductor            |"<<endl;
    cout <<"\t\t\t----------------------------------"<<endl;
	cout<<"\t\t\t 1. Traductor de Espanol a ingles"<<endl;
	cout<<"\t\t\t 2. Exit"<<endl;

	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"\t\t\tOpcion a escoger:[1/2/3/4/5]"<<endl;
	cout<<"\t\t\t-------------------------------"<<endl;
	cout<<"Ingresa tu Opcion: ";
    cin>>choice;
    
    switch(choice)
    {
    case 1:
    	traductorEspanolIngles();
    	encriptarArchivo("palabrasIngles.txt", "encriptadoIngles.txt", reglas);
		break;
	case 2:
	    exit(0);
	}
	} while(choice!= 5);
    return 0;
}
