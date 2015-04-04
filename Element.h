#ifndef ELEMENT_H
#define ELEMENT_H
#include <string>
#include <list>

using std::list;
using std::string;

class Element
{
    private:
    //tagName, innerHTML
    string tagname, innerthtml;
    //attrList
    list<string> attrList;

    public:
    Element(): tagname(), innerthtml(), attrList() {};
    Element (const string name): tagname(name), innerthtml(), attrList() {};
    Element (string name, list<string> atributos, string inhtml): tagname(name), innerthtml(inhtml), attrList(atributos) {};
    string tagName(){ return(this->tagname); }
    list<string> attributeList(){ return(attrList); }
    string innerHTML() { return (innerthtml); }
    void setTagName (const string name) {tagname = name;}
    void setAttributeList (const list<string> atributos){ attrList = atributos; }
    void setInnerHTML(const string inhtml) {innerthtml = inhtml;}

};

#endif
