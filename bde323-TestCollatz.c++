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
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "gtest/gtest.h"

#include "Collatz.h"

// -----------
// TestCollatz
// -----------

// ----
// read
// ----

TEST(Collatz, read) {
    std::istringstream r("1 10\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    1);
    ASSERT_TRUE(j ==   10);}

TEST(Collatz, read_tab) {
  std::istringstream r("1 \t 10\n");
  int i;
  int j;
  const bool b = collatz_read(r, i, j);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(i == 1);
  ASSERT_TRUE(j == 10);
}
TEST(Collatz, read_spaces) {
  std::istringstream r("1     10     \n");
  int i;
  int j;
  const bool b = collatz_read(r, i, j);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(i == 1);
  ASSERT_TRUE(j == 10);
}

// ----
// eval
// ----

TEST(Collatz, eval_1) {
    const int v = collatz_eval(1, 10);
    ASSERT_TRUE(v == 20);}

TEST(Collatz, eval_2) {
    const int v = collatz_eval(100, 200);
    ASSERT_TRUE(v == 125);}

TEST(Collatz, eval_3) {
    const int v = collatz_eval(201, 210);
    ASSERT_TRUE(v == 89);}

TEST(Collatz, eval_4) {
    const int v = collatz_eval(900, 1000);
    ASSERT_TRUE(v == 174);}

// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, reverseprint) {
    std::ostringstream w;
    collatz_print(w, 20, 10, 1);
    ASSERT_TRUE(w.str() == "20 10 1\n");}

TEST(Collatz, bigprint) {
    std::ostringstream w;
    collatz_print(w, 200000, 100000, 112345);
    ASSERT_TRUE(w.str() == "200000 100000 112345\n");}
// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

TEST(Collatz, solve2) {
    std::istringstream r("3 10\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "3 10 20\n");}

TEST(Collatz, solve3) {
    std::istringstream r("8239 2971\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "8239 2971 262\n");}
    
TEST(Collatz, solve4) {
    std::istringstream r("7639 11696\n3427 1280\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "7639 11696 268\n3427 1280 217\n");}

// -----
// value
// -----

TEST(Collatz, value) {
  int val = collatz_value(8);
  ASSERT_TRUE(val == 4);}

TEST(Collatz, largervalue) {
  int val = collatz_value(50);
  ASSERT_TRUE(val == 25);}

TEST(Collatz, largestvalue) {
  int val = collatz_value(10000);
  ASSERT_TRUE(val == 30);}

