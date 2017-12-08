#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "struct.h"
#include "variable.h"
#include "atom.h"
#include "list.h"
#include "iterator.h"
#include "parser.h"
#include "scanner.h"

TEST(Iterator, first) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    Iterator<Term> *itStruct = s.createIterator();
    itStruct->first();
    ASSERT_EQ("1", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("Y", itStruct->currentItem()->symbol());
    itStruct->next();
    ASSERT_TRUE(itStruct->isDone());
}

TEST(Iterator, nested_iterator) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("s"), { &one, &t, &Y });
  Iterator<Term> *it = s.createIterator();
  it->first();
  it->next();
  Struct *s2 = dynamic_cast<Struct *>(it->currentItem());

  Iterator<Term> *it2 = s2->createIterator();
  it2->first();
  ASSERT_EQ("X", it2->currentItem()->symbol());
  ASSERT_FALSE(it2->isDone());
  it2->next();
  ASSERT_EQ("2", it2->currentItem()->symbol());
  ASSERT_FALSE(it2->isDone());
  it2->next();
  ASSERT_TRUE(it2->isDone());
}



TEST(Iterator, firstList) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l({ &one, &t, &Y });
    Iterator<Term>* itList = l.createIterator();
    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("Y", itList->currentItem()->symbol());
    itList->next();
    ASSERT_TRUE(itList->isDone());
}

TEST(Iterator, NullIterator){
  Number one(1);
  NullIterator nullIterator(&one);
  nullIterator.first();
  ASSERT_TRUE(nullIterator.isDone());
  Iterator<Term> * it = one.createIterator();
  it->first();
  ASSERT_TRUE(it->isDone());
}




TEST(Iterator, DFS_Struct_1) {
  Scanner scanner("com(two(1,2),2,3,4)");
  Parser parser(scanner);
  Struct *str = dynamic_cast<Struct *>(parser.createTerm());
  
  Iterator<Term*> * it = str->createDFSIterator();
  it->first();
  ASSERT_EQ("two(1, 2)", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("3", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("4", it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());

}

TEST(Iterator, DFS_Struct_2) {
  Scanner scanner("com([5,4],2,3,4)");
  Parser parser(scanner);
  Struct *str = dynamic_cast<Struct *>(parser.createTerm());
  
  Iterator<Term*> * it = str->createDFSIterator();
  it->first();
  ASSERT_EQ("[5, 4]", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("5", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("4", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("3", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("4", it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());
}


TEST(Iterator, BFS_Struct_1) {
  Scanner scanner("combo1(bigMac(cheese, [pickleSlice1, pickleSlice2]), coke, [fries1, fries2])");
  Parser parser(scanner);
  Struct *str = dynamic_cast<Struct *>(parser.createTerm());
  
  Iterator<Term*> * it = str->createBFSIterator();
  it->first();
  ASSERT_EQ("bigMac(cheese, [pickleSlice1, pickleSlice2])", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("coke", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("[fries1, fries2]", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("cheese", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("[pickleSlice1, pickleSlice2]", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("fries1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("fries2", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("pickleSlice1", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("pickleSlice2", it->currentItem()->symbol());
  it->next();
  ASSERT_TRUE(it->isDone());

}






#endif