#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "term.h"

using std::string;

class Number;
class Variable;

class Atom
{
public:
  Atom(string s);
  bool operator==(Atom a);
  string _symbol;

  bool match(Variable &X);
  bool match(Number math);
  string value();
}
;

#endif
