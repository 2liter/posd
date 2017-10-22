#include "list.h" 

std::string List::symbol() const{
    if(_elements.empty()) return "[]";
}

std::string List::value() const{
    if(_elements.empty()) return "[]";
}

bool List::match(Term & term){
    return true;
}
