#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "atom.h"
#include "number.h"
using std::string;

class Variable{
public:
  Variable(string s):_symbol(s){}
  string const _symbol;
  string value(){ return _value; }
  bool match( Atom atom ){
    bool ret = _assignable;
    if(_assignable){
      _value = atom.symbol() ;
      _assignable = false;
    }
    return ret;
  }

  bool match( Number num ){
    bool ret = _assignable;
    if(_assignable){
      _value = num.symbol() ;
      _assignable = false;
    }
    return ret;
  }

  bool match( Variable X ){
    return true;
  }

private:
  string _value;
  bool _assignable = true;
};

#endif