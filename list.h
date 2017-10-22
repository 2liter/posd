#ifndef LIST_H
#define LIST_H

#include "atom.h"

#include <vector>
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
    if(_elements.empty()) return "[]";
  }
  bool match(Term & term){
    return true;
  }


  Term * head() const{
    return NULL;
  }
  List * tail() const{
    return NULL;
  }

private:
  vector<Term *> _elements;

};

#endif
