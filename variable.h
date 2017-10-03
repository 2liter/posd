#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "atom.h"

using std::string;

class Variable{
public:
  Variable(string s):_symbol(s){}
  string const _symbol;
  string _value;
  bool _assignable = true;
  void setvalue(string s) { _value = s ; }
  string value(){ return _value; }
  string symbol() { return _symbol; }
  bool match( Atom atom ){
    bool ret = _assignable;
    if(_assignable){
      _value = atom._symbol ;
      _assignable = false;
    }
    return ret;
  }


};

#endif
