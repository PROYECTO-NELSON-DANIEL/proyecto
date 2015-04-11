#include <iostream>
#include "Dom_tree.h"

int main()
{

    Element a("html"), b("head"), c("title", "Ejemplo de pagina web"), d("body"), e("h1", "Hola mundo!"), f("!documenttype html");
    Element g("p", "Bye!!"), menol("x", "menol");
    DOM_Tree html(a), head(b), title(c), body(d), h1(e), arbol, document(f), p1(g);
    DOM_Tree explota;
    list<string> l;
    string cadena, c1, c2;


    getline(cin, cadena);

    //cadena = "<html><body>hola mundo</body></html>";
    /*while(cin)
    {
    cin >> c1;
    cadena=cadena+c1;
    }*/
   /* l.push_back("id=\"contenido\"");
    Element h("p", l, "Hola mundo!!!");
    DOM_Tree p2(h);

	head.appendChild(title);
	body.appendChild(h1);
    p1.appendChild(menol);
	body.appendChild(p1);
	body.appendChild(p2);
	html.appendChild(head);
	html.appendChild(body);
	document.appendChild(html);*/

    explota.appendChild(cadena);

	//cout << html << endl;
	cout << explota;


    return 0;
}
