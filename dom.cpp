#include <iostream>
#include "Dom_tree.h"

int main()
{

    Element a("html"), b("head"), c("title", "Ejemplo de pagina web"), d("body"), e("h1", "Hola mundo!"), f("!documenttype html");
    Element g("p", "Bye!!");
    DOM_Tree html(a), head(b), title(c), body(d), h1(e), arbol, document(f), p1(g);
    list<string> l;

    l.push_back("id=\"contenido\"");
    Element h("p", l, "Hola mundo!!!");
    DOM_Tree p2(h);

	head.appendChild(title);
	body.appendChild(h1);
	body.appendChild(p1);
	body.appendChild(p2);
	html.appendChild(head);
	html.appendChild(body);
	document.appendChild(html);

	cout << document << endl;


    return 0;
}
