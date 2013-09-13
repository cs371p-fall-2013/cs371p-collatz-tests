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
    ASSERT_TRUE(i == 1);
    ASSERT_TRUE(j == 10);}

TEST(Collatz, read2) {
    std::istringstream r("1 1\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 1);
    ASSERT_TRUE(j == 1);}

TEST(Collatz, read3) {
    std::istringstream r("2 1\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 2);
    ASSERT_TRUE(j == 1);}

TEST(Collatz, read4) {
    std::istringstream r("1 1000000\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 1);
    ASSERT_TRUE(j == 1000000);}

// ----
// length
// ----

TEST(Collatz, length1) {
    const int i = cycle_length(10);
    ASSERT_TRUE(i == 7);}

TEST(Collatz, length2) {
   const int i = cycle_length(999999);
   ASSERT_TRUE(i == 259);}

TEST(Collatz, length3) {
   const int i = cycle_length(592653);
   ASSERT_TRUE(i == 147);}

TEST(Collatz, length4) {
   const int i = cycle_length(777777);
   ASSERT_TRUE(i == 155);}


// ----
// eval
// ----

TEST(Collatz, eval1) {
    const int v = collatz_eval(1, 10);
    ASSERT_TRUE(v == 20);}

TEST(Collatz, eval2) {
    const int v = collatz_eval(100, 200);
    ASSERT_TRUE(v == 125);}

TEST(Collatz, eval3) {
    const int v = collatz_eval(201, 210);   
    ASSERT_TRUE(v == 89);}

TEST(Collatz, eval4) {
    const int v = collatz_eval(900, 1000);
    ASSERT_TRUE(v == 174);}

TEST(Collatz, eval5) {
    const int v = collatz_eval(999999, 1); 
    ASSERT_TRUE(v == 525);}

TEST(Collatz, eval6) {
    const int v = collatz_eval(1, 1);
    ASSERT_TRUE(v == 1);}

TEST(Collatz, eval7) {
    const int v = collatz_eval(900, 1000);
    ASSERT_TRUE(v == 174);}

TEST(Collatz, eval8) {
    const int v = collatz_eval(1, 999999); 
    ASSERT_TRUE(v == 525);}

// -----
// print
// -----

TEST(Collatz, print1) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print2) {
    std::ostringstream w;
    collatz_print(w, 1, 100, 300);
    ASSERT_TRUE(w.str() == "1 100 300\n");}

TEST(Collatz, print3) {
    std::ostringstream w;
    collatz_print(w, 1, 2, 3);
    ASSERT_TRUE(w.str() == "1 2 3\n");}

TEST(Collatz, print4) {
    std::ostringstream w;
    collatz_print(w, 3, 2, 1);
    ASSERT_TRUE(w.str() == "3 2 1\n");}

TEST(Collatz, print5) {
    std::ostringstream w;
    collatz_print(w, 1234, 2345, 3456);
    ASSERT_TRUE(w.str() == "1234 2345 3456\n");}


// -----
// solve
// -----

TEST(Collatz, solve1) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

TEST(Collatz, solve2) {
    std::istringstream r("200 300\n300 200\n500 5000\n5000 500\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "200 300 128\n300 200 128\n500 5000 238\n5000 500 238\n");}

TEST(Collatz, solve3) {
    std::istringstream r("999999 999999\n1 1\n1 10000\n1 100000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "999999 999999 259\n1 1 1\n1 10000 262\n1 100000 351\n");}
