// Natahlie Beavers
// nmb642
//--------------------------------
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

// Check for i > j
TEST(Collatz, read_2) {
    std::istringstream r("10 1\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);}

// Check for i=0
TEST(Collatz, read_3) {
    std::istringstream r("3 1\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);}

// Check for i < 0
TEST(Collatz, read_4) {
    std::istringstream r("5 1\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b== true);}

// Check for j = 0
TEST(Collatz, read_5) {
    std::istringstream r("1 5\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b== true);}

// Check for j < 0 
TEST(Collatz, read_6) {
    std::istringstream r("1 5000\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b== true);}

// Check for i > 999999
TEST(Collatz, read_7) {
    std::istringstream r("10000 10\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b== true);}

// Check for j > 9999999
TEST(Collatz, read_8) {
    std::istringstream r("1 10000\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b== true);}


// ----
// eval
// ----

TEST(Collatz, eval_1) {
    const int v = collatz_eval(2363, 40028);
    ASSERT_TRUE(v == 324);}

TEST(Collatz, eval_2) {
    const int v = collatz_eval(200, 100);
    ASSERT_TRUE(v == 125);}

TEST(Collatz, eval_3) {
    const int v = collatz_eval(2, 3);
    ASSERT_TRUE(v == 8);}

TEST(Collatz, eval_4) {
    const int v = collatz_eval(1, 10);
    ASSERT_TRUE(v == 20);}

TEST(Collatz, eval_5) {
    const int v = collatz_eval(100, 200);
    ASSERT_TRUE(v == 125);}

TEST(Collatz, eval_6) {
    const int v = collatz_eval(201, 210);
    ASSERT_TRUE(v == 89);}

TEST(Collatz, eval_7) {
    const int v = collatz_eval(900, 1000);
    ASSERT_TRUE(v == 174);}

// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}


TEST(Collatz, print_2) {
    std::ostringstream w;
    collatz_print(w, 201, 210, 89);
    ASSERT_TRUE(w.str() == "201 210 89\n");}

TEST(Collatz, print_3) {
    std::ostringstream w;
    collatz_print(w, 2, 2, 1);
    ASSERT_TRUE(w.str() == "2 2 1\n");}



TEST(Collatz, print_4) {
    std::ostringstream w;
    collatz_print(w, 100, 200, 125);
    ASSERT_TRUE(w.str() == "100 200 125\n");}

// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}


TEST(Collatz, solve_2) {
    std::istringstream r("5 5\n10 15\n7 5\n9 12\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "5 5 6\n10 15 18\n7 5 17\n9 12 20\n");}


TEST(Collatz, solve_3) {
    std::istringstream r("1 5000\n5200 6000\n19 12\n3 2\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 5000 238\n5200 6000 236\n19 12 21\n3 2 8\n");}


TEST(Collatz, solve_4) {
    std::istringstream r("1 1\n 12 14\n2400 7900\n89 62\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 1 1\n12 14 18\n2400 7900 262\n89 62 116\n");}

