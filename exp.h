#ifndef EXP_H
#define EXP_H

#include "atom.h"
//#include "global.h"

class Exp {
public:
  virtual bool evaluate() = 0;
    Exp * _left;
  Exp * _right;
};


class MatchExp : public Exp {
public:
  MatchExp(Term* left, Term* right): _left(left), _right(right){

  }

  bool evaluate(){
    return _left->match(*_right);
  }

  Term* _left;
  Term* _right;
};

class ConjExp : public Exp {
public:
  ConjExp(Exp *left, Exp *right) : _left(left), _right(right) {

  }

  bool evaluate() {
    
    return (_left->evaluate() && _right->evaluate());
  }

  Exp * _left;
  Exp * _right;
};

class DisjExp : public Exp {
public:
  DisjExp(Exp *left, Exp *right) : _left(left), _right(right) {

  }

  bool evaluate() {
    return (_left->evaluate() || _right->evaluate());
  }

  Exp * _left;
  Exp * _right;
};
#endif
