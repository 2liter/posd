#ifndef NODE_H
#define NODE_H

enum Operators {SEMICOLON, COMMA, EQUALITY, TERM};
#include "atom.h"

class Node {
public:
  Node(Operators op):payload(op), term(0), left(0), right(0) {}
  Node(Operators op, Term *t, Node *l, Node *r):payload(op), term(t), left(l), right(r) {}

  bool evaluate(){
    if(this->payload == EQUALITY){
      return this->left->term->match(*(this->right->term));
    }
    else{
      //return (this->left->evaluate() && this->right->evaluate() );
    }

    return true;
      /*
    for(int i = 0; _terms.size() < i; i++){
        _terms[i]->match(*(_terms[i+1]));
        i++;
      }
      */
  }

  Operators payload;
  Term *term;
  Node *left;
  Node *right;

};


    


#endif