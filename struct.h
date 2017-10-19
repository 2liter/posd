#ifndef STRUCT_H
#define STRUCT_H

#include "variable.h"
#include "atom.h"
#include <vector>
#include <string>
#include <iostream>

using std::string;

class Struct:public Term
{
public:
  Struct(Atom const & name, std::vector<Term *> args):_name(name), _args(args) { }



  Term * args(int index) {
    return _args[index];
  }

  Atom const & name() {
    return _name;
  }
  string symbol() const{
    string ret =_name.symbol() + "(";
    for(int i = 0; i < _args.size() - 1 ; i++){
      ret += _args[i]-> symbol() + ", ";
    }
    ret += _args[_args.size()-1]-> symbol() + ")";
    return  ret;
  }
  
  string value() const{
    string ret =_name.symbol() + "(";
    for(int i = 0; i < _args.size() - 1 ; i++){
      Variable * ps = dynamic_cast<Variable *>(_args[i]);
      //Struct * ps1 = dynamic_cast<Struct *>(_args[i]);
      if(ps) ret += ps->value() + ", ";
      //else if(ps1) ret += ps->value() + ", ";
      else ret += _args[i]-> symbol() + ", ";
      ps = NULL ;
      //ps1 = NULL;
    }
    Variable * ps = dynamic_cast<Variable *>(_args[_args.size()-1]);
    //Struct * ps1 = dynamic_cast<Struct *>(_args[_args.size()-1]);
    if(ps) {
      ret +=  ps->value()+ ")";
    }
    //else if (ps1)ret += _args[_args.size()-1]->value() + ")";
    else  ret += _args[_args.size()-1]-> symbol() + ")";
    ps = NULL ;

    return  ret;
  }
  bool match(Term &term){
    Struct * ps_struct = dynamic_cast<Struct *>(&term);
    if (ps_struct){

      if (!_name.match(ps_struct->_name))
        return false;
      //std::cout << ".." <<_name.match(ps_struct->_name) << "\n";
      if(_args.size()!= ps_struct->_args.size())
        return false;
      //std::cout << _args.size() << ".." <<ps_struct->_args.size() << "\n";
      for(int i=0;i<_args.size();i++){
        //std::cout << _args[i]->symbol() << ".." <<ps_struct->_args[i]->symbol() << "\n";
        if(_args[i]->symbol() != ps_struct->_args[i]->symbol())
            return false;

      }
      return true;
    }
/*
    Variable * ps = dynamic_cast<Variable *>(&term);
    if (ps){
      if (!_name.match(ps->_name))
        return false;
      if(_args.size()!= ps->_args.size())
        return false;
      for(int i=0;i<_args.size();i++){
        if(_args[i]->symbol() != ps->_args[i]->symbol())
            return false;
      }
      return true;
    }
*/


    return false;
  }
private:
  Atom _name;
  std::vector<Term *> _args;
};

#endif
