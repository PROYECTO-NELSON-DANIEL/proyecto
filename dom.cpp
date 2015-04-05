#include <iostream>
#include "Dom_tree.h"

int main()
{
    Element a("a"), b("b"), c("c"), d("d");
    DOM_Tree da(a), db(b), dc(c), dd(d), ad, ae;
    list<DOM_Tree> l;
    d = c;
    l.push_back(da);
    l.push_back(db);
    l.push_back(dc);
    l.push_back(dd);

    ad=DOM_Tree(a, l);

    return 0;
}
