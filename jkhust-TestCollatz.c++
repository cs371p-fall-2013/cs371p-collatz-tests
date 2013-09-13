// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------------

/*
To test the program:
% ls -al /usr/include/gtest/
...
gtest.h
...

% locate libgtest.a
/usr/lib/libgtest.a

% locate libpthread.a
/usr/lib/x86_64-linux-gnu/libpthread.a
/usr/lib32/libpthread.a

% locate libgtest_main.a
/usr/lib/libgtest_main.a

% g++ -pedantic -std=c++0x -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lpthread -lgtest_main

% valgrind TestCollatz > TestCollatz.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "gtest/gtest.h"

#include "Collatz.h"

// -----------
// cache
// -----------

// -----------
// cache_isClear
// -----------

TEST(cache, isClear_1) {
  cache_clear();
  ASSERT_TRUE(cache_isClear());
    
}

TEST(cache, isClear_2) {
  cache_clear();
  cache_clear();
  ASSERT_TRUE(cache_isClear());
    
}

TEST(cache, isClear_3) {
  cache_clear();
  
  // no effect
  cache_add(1, -1);
  ASSERT_TRUE(cache_isClear());
    
}

// -----------
// cache_clear
// -----------

TEST(cache, clear_1) {
  cache_clear();
  cache_add(1, 999);
  cache_add(100, 101);

  cache_clear();
  
  ASSERT_TRUE(cache_isClear());
  
}


TEST(cache, clear_2) {
  cache_clear();
  cache_add(0, 1618);
  cache_add(99999, 101);

  cache_clear();
  
  ASSERT_TRUE(cache_isClear());
  
}


TEST(cache, clear_3) {
  cache_clear();
  cache_add(1234, -1);
  cache_add(5678, 1234);
  
  cache_clear();

  ASSERT_TRUE( cache_isClear());
    
}



// -----------
// cache_eagerFill
// -----------

TEST(cache, eagerFill_1) {
  cache_clear();
  cache_eagerFill();

  ASSERT_TRUE( !cache_isClear() );
    
}


// -----------
// cache_add
// -----------

TEST(cache, add_1) {
  cache_clear();
  
  cache_add(0, 100);
  
  bool bFound = false;
  int v;
  
  bFound = cache_lookup(0, v);
  
  ASSERT_TRUE(bFound && (v == 100));
  
}

TEST(cache, add_2) {
  cache_clear();
  
  cache_add(314, 1618);
  
  bool bFound = false;
  int v;
  
  bFound = cache_lookup(314, v);
  
  ASSERT_TRUE(bFound && (v == 1618));
  
}

TEST(cache, add_3) {
  cache_clear();
  
  cache_add(99999, 12345);
  
  bool bFound = false;
  int v;
  
  bFound = cache_lookup(99999, v);
  
  ASSERT_TRUE(bFound && (v == 12345));
  
}

// -----------
// cache_lookup
// -----------

TEST(cache, lookup_1) {
  cache_clear();
  
  bool bFound = false;
  int v;
  
  bFound = cache_lookup(0, v);
  
  ASSERT_FALSE( bFound );
  
}

TEST(cache, lookup_2) {
  cache_clear();
  
  bool bFound = false;
  int v;
  
  bFound = cache_lookup(999999, v);
  
  ASSERT_FALSE( bFound );
  
}

TEST(cache, lookup_3) {
  cache_clear();
  
  bool bFound = false;
  int v;
  
  bFound = cache_lookup(12345, v);
  
  ASSERT_FALSE( bFound );
  
}

TEST(cache, lookup_4) {
  cache_clear();
  
  cache_add(999, 123);
  
  bool bFound = false;
  int v;
  
  bFound = cache_lookup(999, v);
  
  ASSERT_TRUE(bFound && (v == 123));
  
}

// -----------
// collatz
// -----------

// ----
// read
// ----

TEST(Collatz, read_1) {
  std::istringstream r("1 10\n");
  int i;
  int j;
  const bool b = collatz_read(r, i, j);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(i == 1);
  ASSERT_TRUE(j == 10);
    
}

TEST(Collatz, read_2) {
  std::istringstream r("99 5\n");
  int i;
  int j;
  const bool b = collatz_read(r, i, j);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(i == 99);
  ASSERT_TRUE(j == 5);

}
    
TEST(Collatz, read_3) {
  std::istringstream r("1 144\n");
  int i;
  int j;
  const bool b = collatz_read(r, i, j);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(i == 1);
  ASSERT_TRUE(j == 144);
    
}
    
TEST(Collatz, read_4) {
  std::istringstream r("1\n");
  int i;
  int j;
  const bool b = collatz_read(r, i, j);
  ASSERT_TRUE(b == false);
  
}

// -----------
// cycleLength
// -----------
/* Collatz cycles used for testing found here:
  http://csw373.wordpress.com/2013/06/09/list-of-collatz-cycles/
*/

TEST(Collatz, cycleLength_1) {
  const int v = collatz_cycleLength(1);
  ASSERT_TRUE(v == 1);
    
}

TEST(Collatz, cycleLength_2) {
  const int v = collatz_cycleLength(13);
  ASSERT_TRUE(v == 10);
    
}

TEST(Collatz, cycleLength_3) {
  const int v = collatz_cycleLength(19);
  ASSERT_TRUE(v == 21);
    
}

// ----
// eval
// ----

TEST(Collatz, eval_1) {
  cache_clear();
  const int v = collatz_eval(1, 10);
  ASSERT_TRUE(v == 20);
    
}

TEST(Collatz, eval_2) {
  cache_clear();
  const int v = collatz_eval(100, 200);
  ASSERT_TRUE(v == 125);
  
}

TEST(Collatz, eval_3) {
  cache_clear();
  const int v = collatz_eval(201, 210);
  ASSERT_TRUE(v == 89);
  
}

TEST(Collatz, eval_4) {
  cache_clear();
  const int v = collatz_eval(900, 1000);
  ASSERT_TRUE(v == 174);
  
}

// -----
// print
// -----

TEST(Collatz, print_1) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print_2) {
    std::ostringstream w;
    collatz_print(w, 0, 1, 2);
    ASSERT_TRUE(w.str() == "0 1 2\n");}
    
TEST(Collatz, print_3) {
    std::ostringstream w;
    collatz_print(w, 10, 2, 5);
    ASSERT_TRUE(w.str() == "10 2 5\n");}


// -----
// solve
// -----

TEST(Collatz, solve_1) {
  cache_clear();
  cache_eagerFill();
  std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
  std::ostringstream w;
  collatz_solve(r, w);
  ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");
    
}

TEST(Collatz, solve_2) {
  cache_clear();
  cache_eagerFill();
  std::istringstream r("108 199\n8009 9541\n6671 8681\n150 1816\n");
  std::ostringstream w;
  collatz_solve(r, w);
  ASSERT_TRUE(w.str() == "108 199 125\n8009 9541 260\n6671 8681 257\n150 1816 182\n");
  
}
    
TEST(Collatz, solve_3) {
  cache_clear();
  cache_eagerFill();
  std::istringstream r("870 4350\n7422 8196\n633 2022\n620 4474\n");
  std::ostringstream w;
  collatz_solve(r, w);
  ASSERT_TRUE(w.str() == "870 4350 238\n7422 8196 252\n633 2022 182\n620 4474 238\n");
  
}