
			//HOLA NELSONNN XDDDDDD
			//HOLA DANIEL :v


#ifndef DomTree_h
#define DomTree_h
#include "Node.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <stack>
#include <vector>

using std::list;
using std::vector;
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
        static void imprimirArbol(const Node *raiz, int esp);
        static void imprimirAtributos(list<string> atributos);
        DOM_Tree convertir(const string s);
        static void identar(int cont);
        static void imprimirHastaTag(string &h, string &tag, string tagRaiz, int esp);
        static string encontrarTagName(string h);

    public:

        //Constructores
        DOM_Tree(): raiz(NULL){}; // Constructor sin parametros
        DOM_Tree(const Element e) { raiz=new Node(e); }
        DOM_Tree(Element e, list<DOM_Tree> hijos);
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
        friend ostream& operator << (ostream &o, const DOM_Tree &h);

};

    /***CONSTRUCTORES***/
DOM_Tree::DOM_Tree(Element e, list<DOM_Tree> hijos)
{
        raiz=new Node(e);

        while(!hijos.empty())
        {
            appendChild(hijos.front());
            hijos.pop_front();
        }


}


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
           /* aux = raiz->firstChild();
            if(aux->firstChild() == NULL)
            {
                aux->setFirstChild(copiar(h.raiz));
            }*/
          //  else
          //  {
                aux=raiz->firstChild();
                while(aux->nextSibling()!=NULL)
                {
                    aux=aux->nextSibling();
                }
                aux->setNextSibling(copiar(h.raiz));
            //}
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
    int j, k, i;
    Element e;
    DOM_Tree aux;
    string n1, n2, inn, tag, atr;
    list<string> atrb;
    vector<DOM_Tree> a;


    while(!h.empty())
    {
        atrb=list<string>();
        k=h.find('<');
        j=h.find('>');
        if(k!=-1 && j!=-1)
        {
            n1=h.substr(k+1, j-k-1);
            if(n1.find(' ')!=-1)
            {
                i=n1.find(' ');
                tag=n1.substr(0, i);
                n1.erase(0, i+1);
                while(!n1.empty())
                {
                    if(n1.find(' ')!=-1)
                    {
                        i=n1.find(' ');
                        atr=n1.substr(0, i);
                        atrb.push_back(atr);
                        n1.erase(0, i+1);
                    }
                    else
                    {
                        atrb.push_back(n1);
                        n1.clear();
                    }
                }
                n1=tag;
            }
            n2="</"+n1+'>';
            h.erase(0, j+1);
            k=h.find(n2);
            inn=h.substr(0, k);
            h.erase(k, n2.size());
        }
        else
        {
            inn=h;
            h.clear();
        }

        e=Element(n1, atrb, inn);
        aux=DOM_Tree(e);
        a.insert(a.begin(), aux);
    }
    a.erase(a.begin());

    while(!a.empty())
    {
        aux=a[0];
        a.erase(a.begin()+0);
        if(!a.empty())
        {
            i=0;
            while(a[i].raiz->element().innerHTML().find(aux.raiz->element().innerHTML())==-1)
                i++;
            a[i].appendChild(aux, 1);
        }
    }
    return (aux);
}

DOM_Tree DOM_Tree::getElementByID(string id)
{
    DOM_Tree arbol;

    buscarID(arbol, id, raiz);
    return (arbol);

}

void DOM_Tree::buscarID(DOM_Tree &h, string id, Node* p)
{
    int k;
    list<string> atributos;
    if(p!=NULL)
    {
        atributos = (p->element()).attributeList();
        while(!atributos.empty())
        {
            if( atributos.front().find(id) != -1)
            h.raiz = copiar(p);
        }
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

ostream& operator <<(ostream &o, const DOM_Tree &h)  /*********/
{
    int esp;
    Node* aux;

    if(h.raiz != NULL)
    {
        if(h.raiz->element().tagName() == "html");
        o << "<" << "!document type" << ">" << endl;
        DOM_Tree::imprimirArbol(h.raiz, 0);
    }
    return o;
}

void DOM_Tree::imprimirArbol(const Node* raiz, int esp)/********/
{
    Node* hermano, *hijo;
    string tag, inner;

    if( raiz != NULL )
    {

        hermano = NULL;
        hijo = NULL;
        inner = raiz->element().innerHTML();
        hermano=raiz->firstChild();
        hijo= raiz->firstChild();



            if( raiz->firstChild() != NULL)
            {
                    identar(esp);
                    cout << "<" << raiz->element().tagName();
                    imprimirAtributos(raiz->element().attributeList());
                    cout << ">" << endl;


                    while(!inner.empty())
                    {
                        imprimirHastaTag(inner, tag, raiz->element().tagName(), esp); /***/


                        if(hijo!=NULL)
                        {
                        cout << endl;
                            imprimirArbol(hijo, esp+1);
                            hijo=hijo->firstChild();
                        }
                        imprimirHastaTag(inner, tag, raiz->element().tagName(), esp); /***/

                        if( hermano->nextSibling() != NULL)
                        {
                        cout << endl;
                            imprimirArbol(hermano->nextSibling(), esp+1);
                            hermano = hermano->nextSibling();
                        }

                    }
                     cout << endl;
                    identar(esp);
                    cout << "</" << raiz->element().tagName() << ">" << endl;
            }
            else
            {
                    identar(esp);
                    cout << "<" << raiz->element().tagName();
                    imprimirAtributos(raiz->element().attributeList());
                    cout << ">";
                    cout << raiz->element().innerHTML() << "</" << raiz->element().tagName() << ">"<< endl;
            }

    }
}

void DOM_Tree::imprimirAtributos(list<string> atributos)
{
    while(!atributos.empty())
    {
        cout << " " << atributos.front();
        atributos.pop_front();
    }
}

void DOM_Tree::identar(int cont)
{
    int i;

    for(i=0; i<cont; i++)
    {
        cout << "       ";
    }
}

void DOM_Tree::imprimirHastaTag(string &h, string &tag, string tagRaiz, int esp)
{
    string tagaux;
    int i, j;

    i= h.find('<');
    j= h.find('>');
    if(i!=-1 && j!=-1)
    {
         if(!h.substr(0, i).empty())
        {
        identar(esp+1);
        cout << h.substr(0, i);
        }


           tag =  encontrarTagName(h.substr(i+1, j-i-1));
            h.erase(0, j+1);
            if( ('/' +tag)!=tagRaiz)
            {
                tagaux = '/' + tag;
                i= h.find(tagaux);
                h.erase(0, i+1+tagaux.length());
            }

    }
    else
    {
        if(!h.empty())
        {
            identar(esp+1);
            cout << h;
            h.erase();
        }
    }


}

string DOM_Tree::encontrarTagName(string h)
{
    if(h.find(' ')!=-1)
        return( h.substr(0, h.find(' ')) );
    else
        return h;


}


#endif





