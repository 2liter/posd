#include "atom.h"
#include "variable.h"
#include "number.h"
using std::string;


Atom::Atom (string s):_symbol(s) {}

string Atom::symbol() const{
  return _symbol;
}

bool Atom::match(Term & term){
    
    Variable *var_ps = dynamic_cast<Variable *>(&term);
    if (var_ps)
    {
        Atom atom (_symbol);
        var_ps->match(atom);
        return true;
    }

    Atom *atom_ps = dynamic_cast<Atom *>(&term);
    if (atom_ps)
    {
        if (_symbol == atom_ps->symbol())
            return true;
        else return false;
    }

    Number *num_ps = dynamic_cast<Number *>(&term);
    if (num_ps)
    {
        if (_symbol == num_ps->symbol())
            return true;
        else
            return false;
    }
    
}

string Atom::getType()
{
  return "Atom";
}
