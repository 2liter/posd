#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "atom.h"
#include "number.h"
#include <iostream>
using std::string;

class Variable : public Term{
public:
  Variable(string s):_symbol(s){
    _value = _symbol;
  }
  string const _symbol;
  string value() { return _value; }
  string symbol() const{
    return _symbol;
  }
  bool match(Term &term){
    Atom *atom_ps = dynamic_cast<Atom *>(&term);
    if (atom_ps) {
      bool ret = _assignable;
      if (_assignable){

        _value = atom_ps->symbol();
        _assignable = false;
      }
      
      atom_ps = NULL ;
      return ret;
    }

    Number *num_ps = dynamic_cast<Number *>(&term);
    if (num_ps)
    {
      bool ret = _assignable;
      if (_assignable)
      {
        _value = num_ps->symbol();
        _assignable = false;
      }
      num_ps = NULL ;
      return ret;
    }

    Variable *var_ps = dynamic_cast<Variable *>(&term);
    if (var_ps)
    {
      var_ps = NULL;
      return true;
    }

    return true;
  }
  

private:
  string _value;
  bool _assignable = true;


};

#endif