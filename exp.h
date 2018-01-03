#ifndef EXP_H
#define EXP_H

#include "atom.h"

#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"

#include <map>
using std::map;

map<string,Variable*> _table;
string ret = "";

class Exp {
public:
  virtual bool evaluate() = 0;
  virtual string getEvaluateString() {return "";}
  virtual string getRet() {return "";}
};


class MatchExp : public Exp {
public:
  MatchExp(Term* left, Term* right): _left(left), _right(right){
    ret = "";
    _table.clear();
  }

  bool evaluate(){

    // ret = ret + _left->symbol() + " = " + _right->value() ;
    bool result ; 
    Variable  *var = _left->getVariable();
    Variable  *var_r = _right->getVariable();
    if((var == var_r) && var != nullptr ) return true;
    if(var &&( _table.find(var->symbol())== _table.end() ) ) {
      _table.insert(pair<string,Variable*>(var->symbol(),var));
      ret = ret + _left->symbol() + " = " + _right->value() ;
    }  
    result = _left->match(*_right);
    return result;
  }
  string getEvaluateString(){
    return _left->symbol() + " = " + _right->value() ;
  }

  string getRet(){
    return ret;
  }
  
private:
  Term* _left;
  Term* _right;
};

class ConjExp : public Exp {
public:
  ConjExp(Exp *left, Exp *right) : _left(left), _right(right) {
    ret = "";
    _table.clear();
  }

  bool evaluate() {
    bool left,right;
    string instr = ret;
    left = _left->evaluate();
    if(instr != ret)ret = ret + ", ";
    right = _right->evaluate();
    if(ret[ret.length()-1 ] == ' ') ret = ret.substr(0,ret.length()-2);
    return (left && right);
  }

  string getEvaluateString(){
    return (_left->getEvaluateString() + ", "+  _right->getEvaluateString());
  }

  string getRet(){
    return ret;
  }

private:
  Exp * _left;
  Exp * _right;
};

class DisjExp : public Exp {
public:
  DisjExp(Exp *left, Exp *right) : _left(left), _right(right) {
    ret = "";
    _table.clear();
  }

  bool evaluate() {
    bool left,right;
    string instr = ret;
    left = _left->evaluate();
    //if(!left) ret = instr;
    if(instr != ret)ret = ret + "; ";
    instr = ret;
    right = _right->evaluate();
    //if(!right) ret = instr;
    if(ret[ret.length()-1 ] == ' ') ret = ret.substr(0,ret.length()-2);
    return (left || right);
  }

  string getEvaluateString(){
    return (_left->getEvaluateString() + "; "+  _right->getEvaluateString());
  }

  string getRet(){
    return ret;
  }

private:
  Exp * _left;
  Exp * _right;
};
#endif
