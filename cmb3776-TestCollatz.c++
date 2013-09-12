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

TEST(Collatz, read_1) {
    std::istringstream r("1 10\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    1);
    ASSERT_TRUE(j ==   10);}

TEST(Collatz, read_2) {
    std::istringstream r("");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == false);}
    
TEST(Collatz, read_3) {
    std::istringstream r("-20 60\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == false);}
    
TEST(Collatz, read_4) {
    std::istringstream r("999990 1000001\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == false);}

// ----
// eval
// ----

TEST(Collatz, eval_1) {
    const int v = collatz_eval(1, 10);
    ASSERT_EQ(20, v);}

TEST(Collatz, eval_2) {
    const int v = collatz_eval(100, 200);
    ASSERT_EQ(125, v);}

TEST(Collatz, eval_3) {
    const int v = collatz_eval(201, 210);
    ASSERT_EQ(89, v);}

TEST(Collatz, eval_4) { 
    const int v = collatz_eval(900, 1000);
    ASSERT_EQ(174, v);}

TEST(Collatz, eval_5) {
    const int v = collatz_eval(999990, 999999);
    ASSERT_EQ(259, v);}
    
TEST(Collatz, eval_6) {
    const int v = collatz_eval(82795, 82785);
    ASSERT_EQ(214, v);}
    
TEST(Collatz, eval_7) {
    const int v = collatz_eval(76233, 76223);
    ASSERT_EQ(276, v);}

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

TEST(Collatz, solve_1) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}
    
TEST(Collatz, solve_2) {
	  std::istringstream r("1 11\n13155 13165\n75564 75574\n45867 45877\n53279 53289\n");
	  std::ostringstream w;
	  collatz_solve(r, w);
	  ASSERT_TRUE(w.str() == "1 11 20\n13155 13165 214\n75564 75574 245\n45867 45877 208\n53279 53289 185\n");}
		
TEST(Collatz, solve_3) {
	  std::istringstream r("34955 34965\n74835 74845\n29306 29316\n69987 69997\n59114 59124\n");
	  std::ostringstream w;
	  collatz_solve(r, w);
	  ASSERT_TRUE(w.str() == "34955 34965 174\n74835 74845 201\n29306 29316 166\n69987 69997 144\n59114 59124 242\n");}
	
TEST(Collatz, solve_4) {
	  std::istringstream r("24324 24334\n66292 66302\n92993 93003\n81814 81824\n53598 53608\n");
	  std::ostringstream w;
	  collatz_solve(r, w);
	  ASSERT_TRUE(w.str() == "24324 24334 189\n66292 66302 193\n92993 93003 315\n81814 81824 183\n53598 53608 141\n");}
