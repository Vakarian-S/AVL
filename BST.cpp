/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BST.cpp
 * Author: Sebastian
 * 
 * Created on May 23, 2017, 6:04 PM
 */

#include <queue>

#include "BST.h"
#include "BSTNode.h"

BST::BST() {
    this->root = 0;
}

BST::BST(const BST& orig) {
}

BST::~BST() {
}
/**
 * Metodo que busca en el arbol un nodo con el valor X partiendo por la raiz
 * llamando al modo recursivo de esta busqueda
 * @param x valor del nodo a buscar
 * @return bool que indica true si se encontro el valor en el arbol
 */
bool BST::search(int x) {
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    bool boolean = search(this->root, 0, x, 1);
    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "Tiempo de busqueda: " << time_span.count() << " segundos." << endl;
    return boolean;
}

/**
 * Metodo recursivo que busca un nodo con el valor X en el arbol
 * @param b Nodo actual que se esta revisando
 * @param f Nodo padre del nodo actual que se esta revisando
 * @param x numero a buscar
 * @param level nivel en el que se encuentra el nodo actual
 * @return bool con true si esque se encontro el nodo
 */
bool BST::search(BSTNode* b, BSTNode* f, int x, int level) {
   if(!b) return false;
   if (x == this->root->data) {
        cout << "El valor " << x << " ha sido encontrado!\nNivel: " << level << "\nRaiz, por lo tanto no tiene padre" << endl;
        return true;
    }
   //el nodo actual contiene el valor
   if (x == b->data) {
        cout << "El valor " << x << " ha sido encontrado!\nNivel: " << level << "\nPadre: " 
              << f->data << endl;
       return true;
   }
   if(x < b->data) return search(b->leftChild,b,x,level+1);
   return search(b->rightChild,b,x,level+1);
}


/**
 * Metodo que intenta insertar un nodo con el valor ingresado al actual arbol
 * @param x dato que contendra el nodo a ingresar
 * @return bool con true si se pudo ingresar el nodo y false si es que el nodo ya existe
 */
bool BST::insert(int x) {
    // el nodo p sera el nodo que recorre el arbol y el nodo q sera el padre de este.
    BSTNode* p = root;
    BSTNode* q = 0;
    //El siguiente while buscara la posicion en donde deberia ir el nodo a agregar y comprueba si existe o no, moviendo tanto
    // el nodo p como el nodo q como sea necesario
    while(p){
        q = p;
        if (x==p->data) return false; //El valor a ingresar ya existe en el arbol
        if(x<p->data) p = p->leftChild;
        else p = p->rightChild;
    }
    //insertamos 
    p = new BSTNode(x);
    if(!root){ root=p; //si el arbol esta vacio
    }else{
        if(x<q->data)q->leftChild = p;
        else q->rightChild = p;
    }
    return true;
}

/**
 *  Metodo que intenta insertar un nodo con el valor ingresado al actual arbol, pero de la forma que se hace
 * en un AVL, osea, ordenando el arbol despues de cada insercion
 * @param x dato qeu contendra el nodo a ingresar
 * @return  bool con true si se pudo ingresar el nodo y false si es que el nodo ya existe
 */
bool BST::insertAVL(int x) {
   BSTNode *a, *b, *c, *f, *p, *q, *y;
    bool found, unbalanced;
    int d;
    if (!root) { //Caso arbol vacio
        y = new BSTNode(x);
        this->root = y;
        return true;
    }

    //fase 1: Localizar el punto de inserción para x.
    // 'a' guarda la pista del nodo más reciente con el factor de
    //equilibrio ±1, y 'f' es el padre de 'a'. 'q' sigue 'p' a través del árbol.
    f = 0;
    a = p = root;
    q = 0;
    found = false;

    while (p && !found) { //busca el punto donde se insertara x
        if (p->bf) {
            a = p;
            f = q;
        }
        if (x < p->data) {
            q = p;
            p = p->leftChild;
        } else {
            if (x > p->data) {
                q = p;
                p = p->rightChild;
            } else {
                y = p;
                found = true;
            }
        }
    }//end while

    if (!found) {
        // fase 2: Insertar y reequilibrar.
        // x no esta en el arbol y podria ser insertado como
        // un hijo apropiado de q
        y = new BSTNode(x);
        if (x < q->data) q->leftChild = y; //inserta como hijo izquierdo
        else q->rightChild = y; //inserta como hijo derecho

        //Ajusta los factores de balance de los nodos en el camino desde  a hasta q. Notar que por la definicion
        //  de 'a', todos los nodos en el camino deben de tener factores de balance de 0 y cambiaran a +- 1
        // d = +1 Implica que x esta insertado en el subarbol izquierdo de a
        // d = -1 implica que x esta insertado en el subarbol derecho de a

        if (x > a->data) {
            p = a->rightChild;
            b = p;
            d = -1;
        } else {
            p = a->leftChild;
            b = p;
            d = 1;
        }

        while (p != y)
            if (x > p->data) { //la altura derecha se incrementa en 1.
                p->bf = -1;
                p = p->rightChild;
            } else { // la altura izquierda se aumenta en uno
                p->bf = 1;
                p = p->leftChild;
            }
        // Esta el arbol desbalanceado?
        unbalanced = true;
        if (!(a->bf) || !(a->bf + d)) { // arbol aun balanceado
            a->bf += d;
            unbalanced = false;
        }
        if (unbalanced) { //arbol desbalanceado, determina el tipo de rotacion.
            if (d == 1) { // izquierda desbalanceada
                if (b->bf == 1) { // Rotacion tipo LL
                    a->leftChild = b->rightChild;
                    b->rightChild = a;
                    a->bf = 0;
                    b->bf = 0;
                } else { // Rotacion Tipo LR
                    c = b->rightChild;
                    b->rightChild = c->leftChild;
                    a->leftChild = c->rightChild;
                    c->leftChild = b;
                    c->rightChild = a;
                    switch (c->bf) {
                        case 1:
                        { // LR(b)
                            a->bf = -1;
                            b->bf = 0;
                            break;
                        }
                        case -1:
                        { // LR(c)
                            b->bf = 1;
                            a->bf = 0;
                            break;
                        }
                        case 0:
                        { //LR(a)
                            b->bf = 0;
                            a->bf = 0;
                            break;
                        }
                    }// fin switch
                    c->bf = 0;
                    b = c; //b es la nueva raiz
                }// end rotacion LR
            }// end izquierda desbalanceada

            else { // derecha desbalanceada

                if (b->bf == -1) { // Rotacion tipo RR
                    a->rightChild = b->leftChild;
                    b->leftChild = a;
                    a->bf = 0;
                    b->bf = 0;
                } else { // Rotacion Tipo RL
                    c = b->leftChild;
                    b->leftChild = c->rightChild;
                    a->rightChild = c->leftChild;
                    c->rightChild = b;
                    c->leftChild = a;
                    switch (c->bf) {
                        case 1:
                        { // RL(b)
                            a->bf = 1;
                            b->bf = 0;
                            break;
                        }
                        case -1:
                        { // RL(c)
                            b->bf = -1;
                            a->bf = 0;
                            break;
                        }
                        case 0:
                        { //RL(a)
                            b->bf = 0;
                            a->bf = 0;
                            break;
                        }
                    }// fin switch
                    c->bf = 0;
                    b = c; //b es la nueva raiz
                }// end rotacion RL
            } // end else

            //subarbol con raiz b ha sido rebalanceado y es el nuevo arbol

            if (!f) root = b;
            else if (a == f->leftChild) f->leftChild = b;
            else if (a == f->rightChild) f->rightChild = b;
        } // end if unbalances

        return true;

    }//end if (!found)


}



/**
 * Metodo recursivo para vaciar el arbol que elimina cada uno de los nodos
 * @param node nodo actual a eliminar
 */
void BST::clearTree(BSTNode* node) {
     if (node) {
        clearTree(node->leftChild );
        clearTree(node->rightChild);
        delete(node); 
    }
}

/**
 * Metodo inicial para vaciar el arbol que elimina cada uno de los nodos
 */
void BST::clearTree() {
    clearTree(this->root);
    this->root = nullptr;
}

/**
 * Metodo inicial para contar todas las hojas que se encuentran en el arbol, este se comienza llamando al
 * metodo recursivo desde la raiz
 * @return cantidad de hojas contenidas en el arbol
 */
int BST::countLeaves() {
    return countLeaves(this->root);
}

/**
 * Metodo recursivo que cuenta todas las hojas del arbol
 * @param node nodo actual a revisar
 * @return regresa numero de hojas contenidas en los subarboles del nodo actual
 */
int BST::countLeaves(BSTNode* node) {
    //si el nodo esta vacio no se cuenta como hoja
    if(!node) return 0;
    //Si el nodo no tiene hijos se considera una hoja
    if(!node->leftChild && !node->rightChild){
        return 1;
    }
    //si el nodo no esta vacio, y tiene hijos se usa un metodo recursivo para sus hijas
    return countLeaves(node->leftChild) + countLeaves(node->rightChild);
    
}

/**
 * Metodo que imprime todos los nodos del arbol en pre-orden
 * @param node nodo actual al cual aplicarle la impresion
 */
void BST::displayPreorder(BSTNode* node) {
    if (!node) return;
    cout << node->data << " ";
    displayPreorder(node->leftChild);
    displayPreorder(node->rightChild);
    return;
}

/**
 * Metodo que imprime todos lso nodos del arbol en in-orden
 * @param node nodo actual al cual aplicarle la impresion
 */
void BST::displayInorder(BSTNode* node) {
    if (!node) return;
    displayInorder(node->leftChild);
    cout << node->data << " ";
    displayInorder(node->rightChild);
    return;
}

/**
 * Metodo que imprime todos los nodos del arbol en post-orden
 * @param node nodo actual al cual aplicarle la impresion
 */
void BST::displayPostorder(BSTNode* node) {
    if (!node) return;
    displayPostorder(node->leftChild);
    displayPostorder(node->rightChild);
    cout << node->data << " ";
    return;
}

/**
 * Metodo que imprime todos los nodos del arbol por nivel
 */
void BST::displayLevelorder() {
    //si el arbol esta vacio se termina el programa
    if (!this->root) return;
    //usaremos una cola para guardar los niveles a imprimir.
    queue<BSTNode*> q;
    //Empezamos la revision con la raiz
    q.push(this->root);
    //El siguiente while comenzara a imprimir todos los niveles de arriba hacia abajo basado en la cantidad
    //de nodos que guardaremos en el queue, los nodos que guardaremos los iremos añadiendo cada vez
    // que terminemos una linea, osea imprimimos una linea, y guardamos todas las del nivel siguiente, y asi
    //sucesivamente
    while(true){
        //El contador de nodos sera la cantidad de nodos a imprimir que se basara en cuantos nodos hay en el queue
        int nodeCount = q.size();
        //si el contador de nodos es 0 es porque ya no quedan niveles que imprimir
        if(nodeCount == 0) break;
        
        //Ahora sacaremos del Queue todos los nodos del nivel para imprimirlos, y procedemos a añadir
        //todos los nodos del siguiente nivel
        while(nodeCount > 0){
            BSTNode* node = q.front();
            cout << node->data << " ";
            q.pop();
            //al eliminar un nodo ya impreso, aprovechamos de guardar sus hijos para la impresion del siguiente
            //nivel, si bien añadimos mas objetos a la Queue, el ciclo se mantendra intacto y no las imprimira
            //inmediatamente porque el tamaño antiguo ya fue definido con la cantidad de datos del nivel anterior
            if(node->leftChild) q.push(node->leftChild);
            if(node->rightChild) q.push(node->rightChild);
            nodeCount--;
        }
        cout << endl;
    }
    return;
}

