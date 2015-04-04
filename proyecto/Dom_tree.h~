#ifndef DomTree_h
#define DomTree_h
#include "Node.h"
#include <iostream>
#include <string>
#include <list>

using std::list;
using std::string;
using namespace std;

class DOM_Tree
{
    private:
    Node* raiz;

    public:
    //Constructores
    DOM_Tree(): raiz(NULL){}
    //DOM_Tree(Element e, list<DOM_Tree> hijos) {raiz->setElement(e); this->hijos = hijos;}
    //Metodos de Inspeccion
    Node* childNode(){ return(raiz->firstChild()); }
    void appendChild(DOM_Tree h);/*Agrega un nuevo hijo en la posicion p del arbol, si no se especifica posicion se agrega como ultimo hijo*/
    void appendChild(DOM_Tree h, int pos); //Sobrecarga con posicion
    void appendChild(string h); //Sobrecarga con cadena HTML
    void appendChild(string h, int pos); //Sobrecarga con cadena HTML y posicion
    void removeChild();/*Elimina el hijo de la posición p del árbol.*/
    void replaceChild(); /*Cambia el subarbol de la posición p por otro subárbol dado.*/

    DOM_Tree getElementByID();/*Devuelve el subarbol cuya raíz es el element que tenga el ID dado. Si no existe dicho
elemento, devuelve el árbol vacío.*/

    //Destructor
    /*~DOM_Tree();*/

};

void DOM_Tree::appendChild(DOM_Tree h)
{
    Node *aux;
    aux=raiz;
    if(raiz==NULL)
        raiz=h.raiz;
    else
    {
        if(aux->firstChild()==NULL)
            aux->setFirstChild(h.raiz);
        else
        {
            aux=aux->firstChild();
            while(aux->nextSibling()!=NULL)
            {
                aux=aux->nextSibling();
            }
            aux->setNextSibling(h.raiz);
        }
    }
}
#endif
