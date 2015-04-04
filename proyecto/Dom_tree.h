			//HOLA NELSONNN XDDDDDD
			//HOLA DANIEL :v  

#ifndef DomTree_h
#define DomTree_h
#include "Node.h"
#include <iostream>
#include <string>
#include <list>
#include <stack>
#include <queue>

using std::list;
using std::stack;
using std::queue;
using std::string;

using namespace std;

class DOM_Tree
{
    private:
        // ATRIBUTOS
        Node* raiz;
        
        //METODOS
        static Node* copiar(const Node *r);
        DOM_Tree convertir(const string s);
    public:
        //Constructores
        DOM_Tree(): raiz(NULL){}; // Constructor sin parametros
        DOM_Tree(const Element e) { raiz=new Node(e); }
        //DOM_Tree(Element e, list<DOM_Tree> hijos) {raiz->setElement(e); this->hijos = hijos;}
        DOM_Tree(const DOM_Tree &d) { raiz=copiar(d.raiz); } // Constructor copia
        
        //Metodos de Inspeccion
        DOM_Tree childNode(int pos); // este retorna un arbol, no un nodo. 
        
        //Metodos de modificacion
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

// METODOS DE MODIFICACION
Node* DOM_Tree::copiar(const Node *r)
{
    Node *aux(NULL);
    if(r!=NULL)
    {
        aux=new Node(r->element());
        aux->setFirstChild(copiar(r->firstChild()));
        aux->setNextSibling(copiar(r->nextSibling()));
    }
    return aux;
}

void DOM_Tree::appendChild(DOM_Tree h)
{
    Node *aux;
    
    if(raiz==NULL)
        raiz=copiar(h.raiz);
    else
    {
        if(raiz->firstChild()==NULL)
            raiz->setFirstChild(copiar(h.raiz));
        else
        {
            aux=raiz->firstChild();
            while(aux->nextSibling()!=NULL)
            {
                aux=aux->nextSibling();
            }
            aux->setNextSibling(copiar(h.raiz));
        }
    }
}

void DOM_Tree::appendChild(DOM_Tree h, int pos)
{
    Node *aux, *aux2;
    int p=1;
    if(pos>0)
    {
        if(pos==1)
        {
            if(raiz->firstChild()==NULL)
                raiz->setFirstChild(copiar(h.raiz));
            else
            {
                aux=raiz->firstChild();
                raiz->setFirstChild(copiar(h.raiz));
                aux2=raiz->firstChild();
                aux2->setNextSibling(aux);
            }
        }
        else
        {
            aux=raiz->firstChild();
            while(p<pos && aux!=NULL)
            {
                aux2=aux;
                aux=aux->nextSibling();
                p++;
            }
            if(p==pos)
            {
                aux2->setNextSibling(copiar(h.raiz));
                aux2=aux2->nextSibling();
                aux2->setNextSibling(aux);
            }
        }
    }
}

DOM_Tree DOM_Tree::convertir(string h)
{
    int j(0), k;
    Element e;
    DOM_Tree arb, aux;
    string name1, inn;
    stack<Element> a;
    stack<string> p, q;
    
    while(!h.empty())
    {
        if(h[0]=='<')
        {
            j=h.find('>');
            if(h[1]!='/')
            {
                name1=h.substr(1, j-1);
                p.push(name1);
            }
            else
            {
                e=Element(p.top(), q.top());
                a.push(e);
                p.pop();
                q.pop();
            }
            h.erase(0, j+1);
        }
        else
        {
            k=h.find('<');
            inn=h.substr(0, k);
            h.erase(0, k);
            q.push(inn);
        }
    }
    while(!a.empty())
    {
        aux=DOM_Tree(a.top());
        arb.appendChild(aux);
        a.pop();
    }
    return (arb);
}

void DOM_Tree::appendChild(string h)
{
    DOM_Tree a;
    a=convertir(h);
    appendChild(a);
}

void DOM_Tree::appendChild(string h, int pos)
{
    DOM_Tree a;
    a=convertir(h);
    appendChild(a, pos);
}
#endif
