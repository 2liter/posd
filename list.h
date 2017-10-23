#ifndef LIST_H
#define LIST_H

#include "atom.h"
#include <typeinfo>
#include <vector>
#include <iostream>
using std::vector;

class List : public Term {
public:

  List (): _elements() {}
  List (vector<Term *> const & elements):_elements(elements){}

  string symbol() const{
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
      /*
      std::vector<Term *>::const_iterator it = list_ps->_elements.begin();
      for (; it != _elements.end()-1; ++it)
        (*it)->match(a);
      
      std::vector<Term *>::const_iterator it = _elements.begin();
      for (; it != _elements.end()-1; ++it)
        (*it)->match(a);
        */
    }
    return ret1 ;
  }

  List * address() { return this;}
  void set(vector<Term *> _ele){
    _elements.assign(_ele.begin() , _ele.end());
  }


  Term * head() const{ return _elements.front(); }
  List * tail() {
    static vector<Term *> _newElements;
    _newElements.assign(_elements.begin() + 1, _elements.end());
    static List l1;
    l1.set(_newElements);
    //std::cout << l1.value() << "\n" <<l1.address() << "\n"<< this <<"\n";

    return (l1.address());
    //return this;
  }

private:
  vector<Term *> _elements;
};

#endif
