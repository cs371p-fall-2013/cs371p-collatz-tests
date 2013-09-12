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

TEST(Collatz, read2) {
    std::istringstream r("100 100\n");
    int i;
    int j;
    const bool b = collatz_read(r,i,j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 100);
    ASSERT_TRUE(j == 100);}

TEST(Collatz, read3) {
    std::istringstream r("50 2\n");
    int i;
    int j;
    const bool b = collatz_read(r,i,j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 50);
    ASSERT_TRUE(j == 2);}

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
    const int v = collatz_eval(50, 2);
    ASSERT_TRUE(v == 112);}

// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print2) {
    std::ostringstream w;
    collatz_print(w,1200,1200,1200);
    ASSERT_TRUE(w.str() == "1200 1200 1200\n");}

TEST(Collatz, print3) {
    std::ostringstream w;
    collatz_print(w,5,4,3);
    ASSERT_TRUE(w.str() == "5 4 3\n");}

// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

TEST(Collatz, solve2) {
    std::istringstream r("200 350\n1000 2500\n9654 10256\n25 36\n");
    std::ostringstream w;
    collatz_solve(r,w);
    ASSERT_TRUE(w.str() == "200 350 144\n1000 2500 209\n9654 10256 242\n25 36 112\n");}

TEST(Collatz, solve3) {
    std::istringstream r("70 50\n8 3\n150 10\n1000 250\n");
    std::ostringstream w;
    collatz_solve(r,w);
    ASSERT_TRUE(w.str() == "70 50 113\n8 3 17\n150 10 122\n1000 250 179\n");}
