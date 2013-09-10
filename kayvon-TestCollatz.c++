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

    % g++ -pedantic -std=c++0x -Wall Collatz.c++ kayvon-TestCollatz.c++ -o TestCollatz -lgtest -lpthread -lgtest_main

    % valgrind TestCollatz > kayvon-TestCollatz.out
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
    std::istringstream r("392115 208239\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    392115);
    ASSERT_TRUE(j ==   208239);}

TEST(Collatz, read_2) {
    std::istringstream r("787340 404188\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    787340);
    ASSERT_TRUE(j ==   404188);}

TEST(Collatz, read_3) {
    std::istringstream r("423706 440824\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    423706);
    ASSERT_TRUE(j ==   440824);}

TEST(Collatz, read_4) {
    std::istringstream r("932617 496830 \n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    932617);
    ASSERT_TRUE(j ==   496830);}

// ----
// eval
// ----

TEST(Collatz, eval_1) {
    const int v = collatz_eval(1, 1);
    ASSERT_TRUE(v == 1);} 

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

TEST(Collatz, print_1) {
    std::ostringstream w;
    collatz_print(w, 1, 1, 1);
    ASSERT_TRUE(w.str() == "1 1 1\n");}

TEST(Collatz, print_2) {
    std::ostringstream w;
    collatz_print(w, 100, 200, 125);
    ASSERT_TRUE(w.str() == "100 200 125\n");}

TEST(Collatz, print_3) {
    std::ostringstream w;
    collatz_print(w, 201, 210, 89);
    ASSERT_TRUE(w.str() == "201 210 89\n");}

TEST(Collatz, print_4) {
    std::ostringstream w;
    collatz_print(w, 900, 1000, 174);
    ASSERT_TRUE(w.str() == "900 1000 174\n");}

// -----
// solve
// -----

TEST(Collatz, solve_1) {
    std::istringstream r("1 1\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 1 1\n100 200 125\n201 210 89\n900 1000 174\n");}
TEST(Collatz, solve_2) {
    std::istringstream r("1 30\n20 1000\n300 600\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 30 112\n20 1000 179\n300 600 144\n");}
TEST(Collatz, solve_3) {
    std::istringstream r("10 1\n1000 4000\n200 1\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "10 1 20\n1000 4000 238\n200 1 125\n");}

