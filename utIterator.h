#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "struct.h"
#include "variable.h"
#include "atom.h"
#include "list.h"
#include "iterator.h"
#include "parser.h"
#include "scanner.h"

class IteratorTest : public ::testing::Test {
protected:
  void SetUp() {
    symtable.clear();
  }
};


TEST(IteratorTest, first) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    // StructIterator it(&s);
    Iterator *itStruct = s.createIterator();
    // Iterator& itStruct = it;
    // ASSERT_EQ(it.first()->symbol());
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

// TEST(IteratorTest, nested_iterator) {
//   Number one(1);
//   Variable X("X");
//   Variable Y("Y");
//   Number two(2);
//   Struct t(Atom("t"), { &X, &two });
//   Struct s(Atom("s"), { &one, &t, &Y });
  // StructIterator it(&s);
  // it.first();
  // it.next();
  // Struct *s2 = dynamic_cast<Struct *>(it.currentItem());

  // StructIterator it2(s2);
  // it2.first();
  // ASSERT_EQ("X", it2.currentItem()->symbol());
  // ASSERT_FALSE(it2.isDone());
  // it2.next();
  // ASSERT_EQ("2", it2.currentItem()->symbol());
  // ASSERT_FALSE(it2.isDone());
  // it2.next();
  // ASSERT_TRUE(it2.isDone());
// }

TEST(IteratorTest, firstList) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l({ &one, &t, &Y });
    ListIterator it(&l);
    Iterator* itList = &it;
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

TEST(IteratorTest, NullIterator){
  Number one(1);
  NullIterator nullIterator(&one);
  nullIterator.first();
  ASSERT_TRUE(nullIterator.isDone());
  Iterator * it = one.createIterator();
  it->first();
  ASSERT_TRUE(it->isDone());
}

TEST(IteratorTest, DFS_OneMatching) {
  Scanner scanner("X=1.");
  Parser parser(scanner);
  parser.matchings();
  Node * et = parser.expressionTree();
  Iterator * it = et->createDFSIterator();
  it->first();
  ASSERT_EQ("=", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("X", it->currentItem()->symbol());
  it->next();
  ASSERT_EQ("1", it->currentItem()->symbol());
  
  ASSERT_TRUE(it->isDone());
}


#endif