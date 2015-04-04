#include <iostream>
#include "Dom_tree.h"

int main()
{
    Element a("a"), b("b"), c("c"), d("goku");
    DOM_Tree da(a), db(b), dc(c), dd(d), a1, a2, a3;


    a1.appendChild(da);
    a1.appendChild(db);
    a1.appendChild(dc);
    a1.appendChild(dd);

    a2 = a1;

    a1.appendChild(a2, 3);

    a3 = a1.getElementByID("goku");

   // ad.replaceChild(dc, 2);



    /*ae.appendChild(dd);

    ae.appendChild(d);
    ae.appendChild(da);
    ae.appendChild(db, 2);*/
    return 0;
}
