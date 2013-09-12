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

TEST(Collatz, read1) {
    std::istringstream r("1 10\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    1);
    ASSERT_TRUE(j ==   10);}

TEST(Collatz, read2) {
    std::istringstream r("10 1\n");
    int i;
    int j;
    const bool b = collatz_read(r,i,j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 10);
    ASSERT_TRUE(j == 1);}

TEST(Collatz, read3) {
    std::istringstream r("");
    int i;
    int j;
    const bool b = collatz_read(r,i,j);
    ASSERT_TRUE(b == false);}

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
    const int v = collatz_eval(5, 6);
    ASSERT_TRUE(v == 9);}


// -----
// computeCycleLength
// -----
TEST(Collatz, single_cycle1) {
   const int v = collatz_computeCycleLength(5);
   ASSERT_TRUE(v == 6);}
TEST(Collatz, single_cycle2) {
   const int v = collatz_computeCycleLength(10);
   ASSERT_TRUE(v == 7);}
TEST(Collatz, single_cycle3) {
   const int v = collatz_computeCycleLength(20);
   ASSERT_TRUE(v == 8);}


// -----
// print
// -----

TEST(Collatz, print1) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print2) {
    std::ostringstream w;
    collatz_print(w, 10, 1, 20);
    ASSERT_TRUE(w.str() == "10 1 20\n");}

TEST(Collatz, print3) {
    std::ostringstream w;
    collatz_print(w, 100, 10000, 50);
    ASSERT_TRUE(w.str() == "100 10000 50\n");}


// -----
// solve
// -----

TEST(Collatz, solve1) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

TEST(Collatz, solve2) {
    std::istringstream r("10 1\n200 100\n 210 201\n1000 900\n");
    std::ostringstream w;
    collatz_solve(r,w);
    ASSERT_TRUE(w.str() == "10 1 20\n200 100 125\n210 201 89\n1000 900 174\n");}

TEST(Collatz, solve3) {
    std::istringstream r("50 100\n200 500\n500 1500\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "50 100 119\n200 500 144\n500 1500 182\n900 1000 174\n");}


