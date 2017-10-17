#include "atom.h"
#include "number.h"
#include "variable.h"

using std::string;

Variable::Variable(string s):_symbol(s){
    _value = _symbol ;
  }
    string Variable::value() { return _value; }
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
        return ret;
      }
  
      Variable *var_ps = dynamic_cast<Variable *>(&term);
      if (var_ps)
      {
        return true;
      }
  
      return true;
    }