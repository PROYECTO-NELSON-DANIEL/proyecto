#ifndef Node_h
#define Node_h
#include "Element.h"
#include <iostream>
#include <string>
#include <list>

using std::list;
using std::string;
using namespace std;

class Node
{
	private:
		Element e;
		Node *firstchild, *nextsibling;
	public:
		//Constructores

		Node(Element elemento): e(elemento), firstchild(NULL),nextsibling(NULL){}//Con parametro
		Node(Element elemento, Node* hijo, Node* hermano): e(elemento), firstchild(hijo),nextsibling(hermano){}//Con parametro
		//Métodos de modificación
		void setElement(Element elemento){e=elemento;}
		void setNextSibling(Node* hermano){nextsibling=hermano;}
		void setFirstChild(Node* hijo){firstchild=hijo;}
		//Métodos de Inspección
		Node* firstChild()const{return(firstchild);}
		Node* nextSibling()const{return(nextsibling);}
		Element element()const{return(e);}
};

#endif

