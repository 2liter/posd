#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "term.h"

class Atom;
class Number;

using std::string;

class Variable{
public:
  Variable(string s);
  string const _symbol;
  string _value;
  bool _assignable = true;
  void setvalue(string s);
  string value();
  string symbol();
  bool match( Atom atom );
  bool match(Number number);
};

#endif
