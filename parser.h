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
#include "list.h"
#include "node.h"

#include "utParser.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
      else
        return atom;
    }
    else if(token == LIST){
      return list();
    }

    return nullptr;
  }



  Term * structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if(_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      return new Struct(structName, args);
    } else {
      throw string("unexpected token");
    }
  }

  Term * list() {
    _scanner.skipLeadingWhiteSpace();
    if (_scanner.currentChar() == ']') {
      _currentToken = _scanner.nextToken();
      return new List();
    }

    Term *term = createTerm();
    vector<Term *> args;
    if (term)args.push_back(term);
    while ((_currentToken = _scanner.nextToken()) == ',') { args.push_back(createTerm());}
    if(_currentToken != LISTEND)throw std::string ("unexpected token");  
    return new List(args);
    
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      return new List(args);
    } else {
      throw string("unexpected token");
    }
    
  }

  void matchings(){
    Term* ter = createTerm();
    while(ter != nullptr ){
      _terms.push_back(ter);
      int a = _scanner.nextToken();
      if(a == '=')opperation.push_back(EQUALITY);
      else if(a == ',') opperation.push_back(COMMA);
      else if(a == ';') opperation.push_back(SEMICOLON);
      
      //std::cout << a << "\n";
      ter = createTerm();
    }

  }

  Node * expressionTree(){

    if(_terms.size() <=2 ){
      Node * head = new Node(opperation[0]);
      Node * head_l = new Node(TERM,_terms[0],nullptr,nullptr);
      Node * head_r = new Node(TERM,_terms[1],nullptr,nullptr);
      head->left = head_l;
      head->right = head_r;
      return head;
    }
    else{
      Node * root ;
      Node * head = new Node(opperation[1]);
      //std::cout << _terms.size() << "\n";
      for(int i = 0; i < _terms.size() ; i ++){
        if(i+2 >= _terms.size() ){
          Node * head_l = new Node(TERM,_terms[i],nullptr,nullptr);
          Node * head_r = new Node(TERM,_terms[i+1],nullptr,nullptr);
          head->left = head_l;
          head->right = head_r;
          
          return root;
        }

        if(i == 0) root = head;
        //std::cout << root << "\n";
        Node * term_l = new Node(TERM,_terms[i],nullptr,nullptr);
        Node * term_r = new Node(TERM,_terms[i+1],nullptr,nullptr);
        Node * head_l = new Node(opperation[i],nullptr,term_l,term_r);
        head->left = head_l;
        Node *head_r;
        if (i + 3 == opperation.size()) head_r = new Node(opperation[i + 2]);
        else head_r = new Node(opperation[i + 3]);
        head->right = head_r;
        head = head->right;
        i++;
        //std::cout << "456456" << "\n";
      }

      return root;
    }

    
    //Node * head = new Node();
  }

  vector<Term *> & getTerms() {
    return _terms;
  }

private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',') {
        _terms.push_back(createTerm());
      }
    }
  }

  vector<Term *> _terms;
  vector<Operators> opperation;
  Scanner _scanner;
  int _currentToken;
};
#endif
