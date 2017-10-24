#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "atom.h"
#include "list.h"
using std::string;

class Variable : public Term {
public:
  Variable(string s):Term(s), _inst(0){}
  string value() const {
    if (_inst)
      return _inst->value();
    else
      return Term::value();
  }
  bool match( Term & term ){
    
    if (typeid(term) == typeid(List)){
      
      List *list_ps = dynamic_cast<List *>(&term);
      //std::cout << list_ps << "\n" <<list_ps->address() << "\n"<< this <<"\n";
      
      for (int i = 0; (list_ps->getEle()).size() > i; i++ )
        if((*(list_ps->getEleArg(i))).symbol() == _symbol )return false;
    
    }
    
    if (this == &term)
      return true;
    if(!_inst){
      _inst = &term ;
      return true;
    }
    return _inst->match(term);
  }
private:
  Term * _inst;
};

#endif
