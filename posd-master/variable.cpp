
#include <string>
#include "variable.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include <iostream>
using std::string;


  Variable::Variable(string s):_symbol(s){
    _value = _symbol;
  }
  string Variable::value() const{ return _value; }
  string Variable::symbol() const{
    return _symbol;
  }
  bool Variable::match(Term &term){
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
      _value = var_ps->value();
      var_ps = NULL;
      return true;
    }

    Struct *Struct_ps = dynamic_cast<Struct *>(&term);
    if (Struct_ps)
    {
      _value = Struct_ps->value();
      Struct_ps = NULL;
      return true;
    }

    return true;
  }
  