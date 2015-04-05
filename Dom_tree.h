
			//HOLA NELSONNN XDDDDDD
			//HOLA DANIEL :v


#ifndef DomTree_h
#define DomTree_h
#include "Node.h"
#include <iostream>
#include <string>
#include <list>
#include <stack>

using std::list;
using std::stack;
using std::string;
using namespace std;

class DOM_Tree
{
    private:
        // ATRIBUTOS
        Node* raiz;

        //METODOS
        static Node* copiar(const Node *r);
        void vaciar(Node* r);
        void buscarID(DOM_Tree &h, string id, Node* p);
        DOM_Tree convertir(const string s);

    public:
        //Constructores
        DOM_Tree(): raiz(NULL){}; // Constructor sin parametros
        DOM_Tree(const Element e) { raiz=new Node(e); }
        //DOM_Tree(Element e, list<DOM_Tree> hijos) {raiz->setElement(e); this->hijos = hijos;}
        DOM_Tree(const DOM_Tree &d) { raiz=copiar(d.raiz); } // Constructor copia

        //Metodos de Inspeccion
        DOM_Tree childNode(int pos); // este retorna un arbol, no un nodo.
        DOM_Tree getElementByID(string id);


        //Metodos de modificacion
        void appendChild(const DOM_Tree h);
        void appendChild(const DOM_Tree h, const int pos); //Sobrecarga con posicion
        void appendChild(string h); //Sobrecarga con cadena HTML
        void appendChild(string h, int pos); //Sobrecarga con cadena HTML y posicion
        void removeChild(const int pos);
        void replaceChild(const DOM_Tree h, const int pos);
        void replaceChild(const string h, const int pos);
        void vaciar();


        //Destructor
        ~DOM_Tree() { vaciar(); }

        //Sobrecarga de operadores
        void operator=(const DOM_Tree &h);

};

/***METODOS DE MODIFICACION***/
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

void DOM_Tree::vaciar(Node* r)
{
    if(r != NULL)
    {
        vaciar(r->firstChild());
        vaciar(r->nextSibling());
        r = NULL;
    }
}

void DOM_Tree::vaciar()
{
    vaciar(raiz);
}

void DOM_Tree::removeChild(int pos)
{
    Node *aux1, *aux2;
    int i;

    if(raiz!= NULL)
    {
        if(pos!= 0)
        {
            if(pos == 1)
            {
               aux1 = raiz->firstChild();
                raiz->setFirstChild(aux1->nextSibling());
                aux1->setNextSibling(NULL);
                vaciar(aux1);
            }
            else
            {
                aux1 = raiz->firstChild();
                for(i=2; i<=pos; i++)
                {
                aux2 = aux1;
                aux1 = aux1->nextSibling();
                }
                if(aux1 != NULL)
                {
                    aux2->setNextSibling( aux1->nextSibling() );
                    aux1->setNextSibling(NULL);
                    vaciar(aux1);
                }
                else
                    cerr << "ERROR! se trato de eliminar una posicion invalida!" << endl;
            }
        }
        else
            cerr << "ERROR! se trato de eliminar una posicion invalida!" << endl;
    }
    else
        cerr << "ERROR! no se pudo eliminar. (Arbol vacio)" << endl;




}

void DOM_Tree::replaceChild(const DOM_Tree h, const int pos)
{
    Node *aux1, *aux2;
    int i;

    if(raiz!= NULL)
    {
        if(pos!= 0)
        {
            if(pos == 1)
            {
               aux1 = raiz->firstChild();
               h.raiz->setNextSibling(aux1->nextSibling()) ;
                raiz->setFirstChild(h.raiz);
                aux1->setNextSibling(NULL);
                vaciar(aux1);
            }
            else
            {
                aux1 = raiz->firstChild();
                for(i=2; i<=pos; i++)
                {
                aux2 = aux1;
                aux1 = aux1->nextSibling();
                }
                if(aux1 != NULL)
                {



                    aux2->setNextSibling(h.raiz);
                    h.raiz->setNextSibling(aux1->nextSibling());
                    aux1->setNextSibling(NULL);
                    vaciar(aux1);
                }
                else
                    cerr << "ERROR! posicion invalida!" << endl;
            }
        }
        else
            cerr << "ERROR!  posicion invalida!" << endl;
    }
    else
        cerr << "ERROR! Arbol vacio! " << endl;

}

void DOM_Tree::replaceChild(const string h, const int pos)
{
    DOM_Tree arb;

    arb = convertir(h);
    replaceChild(arb, pos);

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


/***METODOS DE INSPECCION***/


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

DOM_Tree DOM_Tree::getElementByID(string id)
{
    DOM_Tree arbol;

    buscarID(arbol, id, raiz);
    return (arbol);

}

void DOM_Tree::buscarID(DOM_Tree &h, string id, Node* p)
{
    if(p!=NULL)
    {
        if( (p->element()).tagName() == id)
        h.raiz = copiar(p);

        buscarID(h, id, p->firstChild() );
        buscarID(h, id, p->nextSibling());

    }

}

DOM_Tree DOM_Tree::childNode(const int pos)
{
    DOM_Tree arbol;

    Node *aux1;
    int i;

    if(raiz!= NULL)
    {
        if(pos!= 0)
        {
            if(pos == 1)
            {
               aux1 = raiz->firstChild();
               aux1->setNextSibling(NULL);
               arbol.raiz = copiar(aux1);
               vaciar(aux1);

            }
            else
            {
                aux1 = raiz->firstChild();
                for(i=2; i<=pos; i++)
                {

                aux1 = aux1->nextSibling();
                }
                if(aux1 != NULL)
                {
                    aux1->setNextSibling(NULL);
                    arbol.raiz = copiar(aux1);
                    vaciar(aux1);
                }
                else
                    cerr << "ERROR! posicion invalida!" << endl;
            }
        }
        else
            cerr << "ERROR!  posicion invalida!" << endl;
    }
    else
        cerr << "ERROR! Arbol vacio! " << endl;

    return (arbol);

}



/***Sobrecarga de operadores**/
void DOM_Tree::operator=(const DOM_Tree  &h)
{
    if(this!=&h)
    raiz = copiar(h.raiz);
}

#endif
