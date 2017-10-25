#ifndef LIST_H
#define LIST_H

#include "atom.h"
#include <typeinfo>
#include <vector>
#include <string>
#include <iostream>
using std::vector;

class List : public Term {
public:

  List (): _elements() {}
  List (vector<Term *> const & elements):_elements(elements){}

  std::string symbol() const{
    string ret;
    if(_elements.empty()) return "[]";
    else{
      ret = + "[";
      std::vector<Term *>::const_iterator it = _elements.begin();
      for (; it != _elements.end()-1; ++it)
        ret += (*it)->symbol()+", ";
      ret  += (*it)->symbol()+"]";
      return ret;
    }
  }
  std::string value() const{
    string ret;
    if(_elements.empty()) return "[]";
    else{
      ret = + "[";
      std::vector<Term *>::const_iterator it = _elements.begin();
      for (; it != _elements.end()-1; ++it)
        ret += (*it)->value()+", ";
      ret  += (*it)->value()+"]";
      return ret;
    }
  }

  bool match(Term & a){
    bool ret1 = true;
    if (typeid(a) == typeid(List)){

      List *list_ps = dynamic_cast<List *>(&a);
      //std::cout << list_ps << "\n" <<list_ps->address() << "\n"<< this <<"\n";
      
      for (int i = 0; _elements.size() > i; i++ )
        (*_elements[i]).match(*(list_ps->_elements[i]) );
      //(*_elements[1]).match(*(list_ps->_elements[1]) );
    }
    else return false ;
    return ret1 ;
  }

  List * address() { return this;}
  void set(vector<Term *> _ele){
    _elements.assign(_ele.begin() , _ele.end());
  }
  vector<Term *> getEle() { return _elements;}
  Term * getEleArg(int i) { return _elements[i];}
  Term * head() const{ 
    //std::cout << _elements;
    if(_elements.empty()) {
      std::cout << "Accessing head in an empty list";
      throw "Accessing head in an empty list";  
    }
    
    return _elements.front(); 
  
  }
  List * tail() {
    static vector<Term *> _newElements;
    static List l1;
    if(_elements.empty()) {
      std::cout << "Accessing head in an empty list";
      throw "Accessing head in an empty list";  
    }

    _newElements.assign(_elements.begin() + 1, _elements.end());
    l1.set(_newElements);

    //std::cout << l1.value() << "\n" <<l1.address() << "\n"<< this <<"\n";

    return &l1;
    //return this;
  }

private:
  vector<Term *> _elements;
};

#endif
