#include "number.h"
#include "variable.h"
#include "atom.h"

using std::string;

Atom::Atom(string s) : _symbol(s) {}
bool Atom::operator==(Atom a) { return _symbol == a._symbol; }
bool Atom::match(Number math)
{
    math.value();
    return false;
}

bool Atom::match(Variable &X)
{


    bool ret = X._assignable;
    if (X._assignable)
    {
        X._value = _symbol;
        X._assignable = false;
    }

    else if (X.value() == _symbol)
    {
        return true;
    }

    return ret;
}
