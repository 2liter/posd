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

class Exp {
public:
  virtual bool evaluate() = 0;
  virtual string getEvaluateString() = 0;
  virtual bool getRet() = 0;
};


class MatchExp : public Exp {
public:
  MatchExp(Term* left, Term* right): _left(left), _right(right){
    _table.clear();
  }

  bool evaluate(){

    bool result ; 
    result = _left->match(*_right);
    ret = result; 
    return result;
  }
  string getEvaluateString(){

    Variable  *var = _left->getVariable();
    Variable  *var_r = _right->getVariable();
    if((var == var_r) && var != nullptr ) return "";
    if(var &&( _table.find(var->symbol())== _table.end() ) ) {
      _table.insert(pair<string,Variable*>(var->symbol(),var));
      return _left->symbol() + " = " + _right->value() ;
    }  
    else return "";
    return _left->symbol() + " = " + _right->value() ;
  }

  bool getRet(){
    return ret;
  }
  
private:
  bool ret; 
  Term* _left;
  Term* _right;
};

class ConjExp : public Exp {
public:
  ConjExp(Exp *left, Exp *right) : _left(left), _right(right) {
    _table.clear();
  }

  bool evaluate() {
    ret = _left->evaluate();
    ret = _right->evaluate() && ret;
    return ret;
  }

  string getEvaluateString(){
    string left = "",right = "",last = "";
    left = _left->getEvaluateString();
    if(left != "")left = left + ", ";
    right = _right->getEvaluateString();
    if(right == "" && left != "" ) left = left.substr(0,left.length()-2);
    if( (left +  right) == "" ) return "true";
    return (left +  right);
  }

  bool getRet(){
    return ret;
  }

private:
  bool ret; 
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

    ret =  _left->evaluate() ;
    ret = _right->evaluate() || ret ;
    return ret;
  }

  string getEvaluateString(){
    string left = "",right = "",last = "";
    left = _left->getEvaluateString();
    if(_left->getRet() == false) left = "";
    else if(left == "")left = "true";
    
    if(left != "")left = left + "; ";
    _table.clear();
    right = _right->getEvaluateString();
    if(_right->getRet() == false) right = "";
    if(right == "" && left != "" ) left = left.substr(0,left.length()-2);
    return (left +  right);
  }

  bool getRet(){
    return ret;
  }

private:
  bool ret; 
  Exp * _left;
  Exp * _right;
};
#endif
