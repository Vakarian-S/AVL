/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MainMenu.cpp
 * Author: Sebastian
 * 
 * Created on June 1, 2017, 7:47 PM
 */

#include "MainMenu.h"
#include "BST.h"

MainMenu::MainMenu() {
}

MainMenu::MainMenu(const MainMenu& orig) {
}

MainMenu::~MainMenu() {
}

/**
 * Metodo que comprueba la linea ingresada es un numero valido
 * @param line linea a revisar  
 * @return bool con true si es un numero valido
 */
bool MainMenu::isNumber(string line) {
    int length = line.size();
    if (length == 0) {
        return false;
    } else if (length == 1 && !isdigit(line[0])) {
        return false;
    } else {
        int i;
        if (line[0] == '+' || line[0] == '-') i = 1;
        else i = 0;
        while (i < length) {
            if (!isdigit(line[i])) {
                return false;
            }
            i++;
        }
    }
    return true;
}

/**
 * Metodo que comprueba si el ingreso por pantalla es un ingreso valido
 * @param line linea a revisar
 * @return bool con true si es una seleccion valida
 */
bool MainMenu::isValid(string line) {
  int character;
  int num;
    try {
        if (!isNumber(line)) {
            throw character;
        }
    } catch (int e) {
        if (e == character) {
            cout << "No se permite signos ni letras\n" << endl;
        }
        return false;
    }
    return true;
}

/**
 * Metodo que ingresa continuamente numeros a ambos arboles binarios
 */
void MainMenu::insert() {
    cout << ".: Ingresar Datos :.\n" << endl;
    string line;
    //Ciclo para ingresar datos
    while (true) {
        //ciclo para validar datos
       do {
            cout << "Ingrese el numero del nodo a ingresar,[-1] Salir:" << endl;
            cin >> line;
            if (!isNumber(line)) cout << "El valor ingresado no es un numero, intente nuevamente\n" << endl;
        } while (!isNumber(line));
        int num = stoi(line);
        if (num == -1) return;
        if (!this->bst.insert(num) || !this->avl.insertAVL(num)) {
            cout << "El valor ingresado ya se encuentra contenido en los arboles \nSaliendo del ingreso..." << endl;
            return;
        } else {
            cout << num << " ingresado exitosamente" << endl;
        }
    }//fin ciclo while
    return;
}
/**
 * Metodo inicial para imprimir por pantalla todos los nodos del arbol en el orden seleccionado
 * @param i numero que definira el tipo de orden que se usara para imprimir
 */
void MainMenu::display() {
    cout << ".: Imprimir datos :.\n" << endl;
    string line;
    do {
        cout << "Ingrese tipo de orden de impresion:\n[1] Pre-orden\n[2] In-orden\n[3] Post-orden\n[4] Por nivel\n[Otro numero] Salir" << endl;
        cin >> line;
        if (!isNumber(line)) cout << "El valor ingresado no es un numero, intente nuevamente\n" << endl;
    } while (!isNumber(line));
    int i = stoi(line);
    switch (i) {
        case 1:
        {
            cout << "Impresion por Pre-orden:" << "\n ABB:" << endl;
            this->bst.displayPreorder(bst.root);
            cout << "\nAVL:" << endl;
            this->avl.displayPreorder(bst.root);
            cout << endl;
            break;
        }
        case 2:
        {
            cout << "Impresion por In-orden:"<< "\n ABB:" << endl;
            this->bst.displayInorder(bst.root);
            cout << "\nAVL:" << endl;
            this->avl.displayInorder(bst.root);
            cout << endl;
            break;
        }
        case 3:
        {
            cout << "Impresion por Post-orden:" << "\n ABB:"<< endl;
            this->bst.displayPostorder(bst.root);
            cout << "\nAVL:" << endl;
            this->avl.displayPostorder(bst.root);
            cout << endl;
            break;
        }
        case 4:
        {
            cout << "Impresion por nivel:" << "\n ABB:"<< endl;
            this->bst.displayLevelorder();
            cout << "\nAVL:" << endl;
            this->avl.displayLevelorder();
            break;
        }
        default:
        {
         break;    
        }
    }//fin switch
    
}

/**
 * Metodo que muestra por pantalla la cantidad de hojas en ambos arboles
 */
void MainMenu::countLeaves() {
    cout << "La cantidad de hojas en el arbol binario de busqueda es: " << this->bst.countLeaves() << endl;
    cout << "La cantidad de hojas en el arbol binario de busqueda tipo AVL es: " << this->avl.countLeaves() << endl;
    return;
}

/**
 * Metodo que vacia los 2 arboles binarios
 */
void MainMenu::clearTrees() {
    this->bst.clearTree();
    this->avl.clearTree();
    cout << "Arboles limpiados exitosamente" << endl;
    return;
}

void MainMenu::search() {
    string line;
    do {
        cout << "Ingrese numero a buscar en los arboles\[-1] Salir" << endl;
        cin >> line;
        if (!isNumber(line)) cout << "El valor ingresado no es un numero, intente nuevamente\n" << endl;
    } while (!isNumber(line));
    int i = stoi(line);
    if(i ==-1) return;
    if(!this->bst.search(i) || !this->avl.search(i)) cout << "El valor no se encuentra en los arboles";
}


void MainMenu::start() {
    this->bst = BST();
    this->avl =BST();
    bool end = false;
    string line;
    //Comienzo del ciclo del menu principal del programa que se repetira hasta que el valor end sea true, o sea que se 
    //salio del programa por orden del usuario
    while (end != true) {
        do{
        cout << ".: Arboles binarios :." << "\n\n"
                << "Eliga una opcion:\n" << "[1] Ingresar datos.\n[2] Vaciar arboles.\n[3] Buscar dato.\n[4] Contar hojas\n"
                << "[5] Imprimir datos.\n[6] Salir." << endl;
        
        cin >> line;
        if(!isNumber(line)) cout << "El valor ingresado no es un numero, intente nuevamente\n" << endl;
        }while(!isNumber(line));
        int option = stoi(line);
        switch (option) {
            case 1:
            {
                insert();
                break;
            }
            case 2:
            {
                clearTrees();
                break;
            }
            case 3:
            {
                search();
                break;
            }
            case 4:
            {
                countLeaves();
                break;
            }
            case 5:
            {
                display();
                break;
            }
            case 6:
            {
                end = true;
                break;
            }
            default:
            {
                cout << "Valor ingresado no es valido" << endl;
                break;
            }
        }//fin switch
    }// fin while end true
}
