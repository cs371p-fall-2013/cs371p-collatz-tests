// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------------

/*
To test the program:
    % ls -al /usr/include/gtest/...gtest.h...

    % locate libgtest.a /usr/lib/libgtest.a

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
    std::istringstream r("1 72\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    1);
    ASSERT_TRUE(j ==   72);}

TEST(Collatz, read2) {
    std::istringstream r("100 10\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    100);
    ASSERT_TRUE(j ==   10);}

TEST(Collatz, read3) {
    std::istringstream r("999999 111111\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    999999);
    ASSERT_TRUE(j ==   111111);}

// ----
// eval
// ----

TEST(Collatz, eval_1) {
    const int v = collatz_eval(1, 1000000);
    ASSERT_TRUE(v == 525);}

TEST(Collatz, eval_2) {
    const int v = collatz_eval(7, 561);
    ASSERT_TRUE(v == 144);}

TEST(Collatz, eval_3) {
    const int v = collatz_eval(5432, 92137);
    ASSERT_TRUE(v == 351);}

TEST(Collatz, eval_4) {
    const int v = collatz_eval(77321, 74321);
    ASSERT_TRUE(v == 351);}

// -----
// print
// -----

TEST(Collatz, print0) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 1000000, 525);
    ASSERT_TRUE(w.str() == "1 1000000 525\n");}

TEST(Collatz, print1) {
    std::ostringstream w;
    collatz_print(w, 7, 561, 144);
    ASSERT_TRUE(w.str() == "7 561 144\n");}

TEST(Collatz, print2) {
    std::ostringstream w;
    collatz_print(w, 5432, 92137, 351);
    ASSERT_TRUE(w.str() == "5432 92137 351\n");}

// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("10 1\n1 1000000\n7 561\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "10 1 20\n1 1000000 525\n7 561 144\n");}

TEST(Collatz, solve1) {
    std::istringstream r("5432 92137\n74321 77321\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "5432 92137 351\n74321 77321 351\n");}

TEST(Collatz, solve2) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}
