#include "number.h"
#include "atom.h"
#include "variable.h"

using std::string;

Number::Number(double s) : _value(s)
{
    std::ostringstream strs;
    strs << _value;
    _str = strs.str();
}
string Number::symbol() const { return _str; }

bool Number::match(Term &term)
{
    Variable *var_ps = dynamic_cast<Variable *>(&term);
    if (var_ps)
    {
        Number num(_value);
        bool is = var_ps->match(num);
        var_ps = NULL;
        return is;
    }
    return symbol() == term.symbol();
}

string Number::getType(){
  return "Number";
}