#include "variable.h"
#include "atom.h"
#include "number.h"
using std::string;

Number::Number(int s) : _value(s)
{
    std::ostringstream strs;
    strs << _value;
    _str = strs.str();
}
string Number::value() { return _str; }
string Number::symbol() { return _str; }
bool Number::match(int s)
{
    return s == _value;
}

bool Number::match(Atom tom)
{
    return false;
}

bool Number::match(Variable &X)
{
    X._value = _str;
    bool ret = X._assignable;
    if (X._assignable)
    {
        X._value = _str;
        X._assignable = false;
    }
    return ret;
}
