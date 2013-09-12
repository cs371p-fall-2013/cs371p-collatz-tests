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
    std::istringstream r("7 9\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    7);
    ASSERT_TRUE(j ==    9);}

TEST(Collatz, read_2) {
    std::istringstream r("64 128\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==   64);
    ASSERT_TRUE(j ==  128);}

TEST(Collatz, read_3) {
    std::istringstream r("10 5\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==   10);
    ASSERT_TRUE(j ==    5);}

TEST(Collatz, read_4) {
    std::istringstream r("1 2\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    1);
    ASSERT_TRUE(j ==    2);}

// ----
// eval
// ----

TEST(Collatz, eval_1) {
    const int v = collatz_eval(512, 2048);
    ASSERT_TRUE(v == 182);}
TEST(Collatz, eval_2) {
    const int v = collatz_eval(8, 88);
    ASSERT_TRUE(v == 116);}
TEST(Collatz, eval_3) {
    const int v = collatz_eval(500, 1200);
    ASSERT_TRUE(v == 182);}
TEST(Collatz, eval_4) {
    const int v = collatz_eval(800, 1000);
    ASSERT_TRUE(v == 179);}
TEST(Collatz, eval_5) {
    const int v = collatz_eval(99, 99999);
    ASSERT_TRUE(v == 351);}
TEST(Collatz, eval_6) {
    const int v = collatz_eval(20, 200);
    ASSERT_TRUE(v == 125);}
TEST(Collatz, eval_7) {
    const int v = collatz_eval(80, 40);
    ASSERT_TRUE(v == 116);}
TEST(Collatz, eval_8) {
    const int v = collatz_eval(10, 1);
    ASSERT_TRUE(v == 20);}

// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}
TEST(Collatz, print_2) {
    std::ostringstream w;
    collatz_print(w, 8, 88, 116);
    ASSERT_TRUE(w.str() == "8 88 116\n");}
 TEST(Collatz, print_3) {
    std::ostringstream w;
    collatz_print(w, 2, 200, 125);
    ASSERT_TRUE(w.str() == "2 200 125\n");}
TEST(Collatz, print_4) {
    std::ostringstream w;
    collatz_print(w, 800, 1000, 179);
    ASSERT_TRUE(w.str() == "800 1000 179\n");}


// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}
TEST(Collatz, solve_2) {
    std::istringstream r("8 88\n512 2048\n80 40\n64 128\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "8 88 116\n512 2048 182\n80 40 116\n64 128 119\n");}