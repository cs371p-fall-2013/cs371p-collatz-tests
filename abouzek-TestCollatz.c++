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

TEST(Collatz, read_empty) {
  std::istringstream r("\n");
  int i;
  int j;
  const bool b = collatz_read(r, i, j);
  ASSERT_FALSE(b);}

TEST(Collatz, read_three) {
  std::istringstream r("1 10 5000\n");
  int i;
  int j;
  const bool b = collatz_read(r, i, j);
  ASSERT_TRUE(b);
  ASSERT_EQ(1, i);
  ASSERT_EQ(10, j);}

TEST(Collatz, read_blanks) {
  std::istringstream r("\n\n\n1 10");
  int i;
  int j;
  const bool b = collatz_read(r, i, j);
  ASSERT_TRUE(b);
  ASSERT_EQ(1, i);
  ASSERT_EQ(10, j);}

TEST(Collatz, read_same) {
  std::istringstream r("1 1\n");
  int i;
  int j;
  const bool b = collatz_read(r, i, j);
  ASSERT_TRUE(b);
  ASSERT_EQ(1, i);
  ASSERT_EQ(1, j);}

// ----
// cycle_length
// ----

TEST(Collatz, cycle_1) {
  const int v = cycle_length(1);
  ASSERT_TRUE(v == 1);}

TEST(Collatz, cycle_3) {
  const int v = cycle_length(3);
  ASSERT_TRUE(v == 8);}

TEST(Collatz, cycle_5) {
  const int v = cycle_length(5);
  ASSERT_TRUE(v == 6);}

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

TEST(Collatz, eval_backward) {
  const int v = collatz_eval(10, 1);
  ASSERT_TRUE(v == 20);}

// -----
// print
// -----

TEST(Collatz, print) {
  std::ostringstream w;
  collatz_print(w, 1, 10, 20);
  ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print_1) {
  std::ostringstream w;
  collatz_print(w, 1, 50, 100);
  ASSERT_TRUE(w.str() == "1 50 100\n");}

TEST(Collatz, print_2) {
  std::ostringstream w;
  collatz_print(w, 1, 1, 1);
  ASSERT_TRUE(w.str() == "1 1 1\n");}

// -----
// solve
// -----

TEST(Collatz, solve) {
  std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
  std::ostringstream w;
  collatz_solve(r, w);
  ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

TEST(Collatz, solve_2) {
  std::istringstream r("4 2285\n");
  std::ostringstream w;
  collatz_solve(r, w);
  ASSERT_TRUE(w.str() == "4 2285 183\n");}

TEST(Collatz, solve_backward) {
  std::istringstream r("10 1\n");
  std::ostringstream w;
  collatz_solve(r, w);
  ASSERT_TRUE(w.str() == "10 1 20\n");}
