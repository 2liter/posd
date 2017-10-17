#include "atom.h"
#include "variable.h"
using std::string;


Atom::Atom (string s):_symbol(s) {}

string Atom::symbol() const{
  return _symbol;
}
/*
bool Atom::match(Term & term){
    
    Variable *var_ps = dynamic_cast<Variable *>(&term);
    if (var_ps)
    {
        Atom atom (_symbol);
        var_ps->match(atom);
        return true;
    }
    
}
*/