#include <iostream>
#include "Dom_tree.h"

int main()
{
    Element a("a"), b("b"), c("c"), d("d");
    DOM_Tree da(a), db(b), dc(b), dd(b), ad, ae;

    ad.appendChild(da);
    ad.appendChild(db);
    ad.appendChild(dc);
    ae.appendChild(dd);
    
    ae.appendChild(d);
    ae.appendChild(da);
    ae.appendChild(db, 2);
    ad.appendChild("<hola>xxxxxx<b>yyyyy</b></hola>");
    return 0;
}
