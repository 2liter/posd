#ifndef LIST_H
#define LIST_H

#include "atom.h"
#include <typeinfo>
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
      std::vector<Term *>::const_iterator it = _elements.begin();
      for (; it != _elements.end()-1; ++it)
        (*it)->match(a);
        */
      /*
      std::vector<Term *>::iterator it = _elements.begin();
      for (; it != _elements.end(); ++it) {
        (*it)->match((*list_ps)._elements[0]);
      }
      return ret;


      for(int i = 0; _elements.size()>i ; i++ ){
        if( _elements[i]->match(list_ps->_elements[i]) )
        else ret = false;
      } // for
*/
    }

    return ret1 ;
    
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
