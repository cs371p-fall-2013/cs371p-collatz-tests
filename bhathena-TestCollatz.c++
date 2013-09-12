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

TEST(Collatz, read_noj) {
  std::istringstream r("1\n");
  int i;
  int j;
  collatz_read(r, i, j);
  ASSERT_TRUE(i == 1);}

TEST(Collatz, read_noj1) {
  std::istringstream r("100\n");
  int i;
  int j;
  collatz_read(r, i, j);
  ASSERT_TRUE(i == 100);}

TEST(Collatz, read1) {
  std::istringstream r("11 20\n");
  int i;
  int j;
  const bool b = collatz_read(r, i, j);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(i ==    11);
  ASSERT_TRUE(j ==   20);}

TEST(Collatz, read2) {
  std::istringstream r("1000 1012\n");
  int i;
  int j;
  const bool b = collatz_read(r, i, j);
  ASSERT_TRUE(b == true);
  ASSERT_TRUE(i ==    1000);
  ASSERT_TRUE(j ==   1012);}



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

TEST(Collatz, eval_5) {
  const int v = collatz_eval(1, 2);
  ASSERT_TRUE(v == 2);}

TEST(Collatz, eval_6) {
  const int v = collatz_eval(1, 3);
  ASSERT_TRUE(v == 8);}

TEST(Collatz, eval_7) {
  const int v = collatz_eval(1, 9);
  ASSERT_TRUE(v == 20);}

TEST(Collatz, eval_iGTj) {
  const int v = collatz_eval(10, 1);
  ASSERT_TRUE(v == 20);}


// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

TEST(Collatz, solve1) {
  std::istringstream r("1 2\n");
  std::ostringstream w;
  collatz_solve(r, w);
  ASSERT_TRUE(w.str() == "1 2 2\n");}
