#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>
using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"


class Parser{
public:
  Parser() {}
  Parser(Scanner scanner)try  : _scanner(scanner){ }catch (std::string &e) { }
  Term* createTerm(){
    int token = _scanner.nextToken();

    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM){
        Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
        if(_scanner.currentChar() == '(' ) {
          _scanner.nextToken() ;
          vector<Term*> terms;
          
          if(_scanner.currentChar() == ')') return new Struct(*atom);
          terms = getArgs();
          if(_currentToken == ')') return new Struct(*atom, terms);
        }
        else
          return atom;
    }else if(token == LIST){
      _scanner.skipLeadingWhiteSpace();
      if (_scanner.currentChar() == ']') {
        token = _scanner.nextToken();
        return new List();
      }

      Term *term = createTerm();
      vector<Term *> args;
      if (term)args.push_back(term);
      while ((token = _scanner.nextToken()) == ',') { args.push_back(createTerm());}
      if(token != LISTEND)throw std::string ("unexpected token");  
      return new List(args);
    }else if(token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        _scanner.nextToken() ;
        vector<Term*> terms;
        
        if(_scanner.currentChar() == ')') return new Struct(*atom);
        terms = getArgs();
        if(_currentToken == ')') return new Struct(*atom, terms);
      }
    } // else if

      return nullptr;
  }

  vector<Term*> getArgs()
  {
    Term* term = createTerm();
    vector<Term*> args;
    if(term)
      args.push_back(term);
    while((_currentToken = _scanner.nextToken()) == ',') {
      args.push_back(createTerm());
    }
    return args;
  }


private:
  Scanner _scanner;
  int _currentToken;
};
#endif  