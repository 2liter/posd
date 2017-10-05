#include "atom.h"
#include "number.h"
#include "variable.h"

using std::string;

Variable::Variable(string s) : _symbol(s) {}
void Variable::setvalue(string s) { _value = s; }
string Variable::value() { return _value; }
string Variable::symbol() { return _symbol; }
bool Variable::match(Atom atom)
{
    bool ret = _assignable;
    if (_assignable)
    {
        _value = atom._symbol;
        _assignable = false;
    }
    else if (_value == atom._symbol)
    {
        return true;
    }

    return ret;
}

bool Variable::match(Number number)
{
    bool ret = _assignable;
    if (_assignable)
    {
        _value = number.value();
        _assignable = false;
    }
    else if (_value == number.value() )
    {
        return true;
    }
    return ret;
}