#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include <sstream>
#include "variable.h"
#include "atom.h"

using std::string;

class Number
{
  public:
    Number(double s) : _value(s){
        std::ostringstream strs;
        strs << _value;
        _str = strs.str();

     }
    double _value;
    string _str;
    string value() { return _str; }
    string symbol() { return "Number"; }
    bool match( double s ) {
        return s == _value ;
    }

    bool match(Atom tom)
    {
        return false;
    }

    bool match(Variable &X)
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


};

#endif 