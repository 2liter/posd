#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "atom.h"
#include <iostream>
using std::string;

class Variable : public Term{
public:
  Variable(string s);
  string const _symbol;
  string value() const;
  string symbol() const;
  bool match(Term &term);
  

private:
  Variable *Y = 0;
  string _value;
  bool _assignable = true;


};

#endif