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

TEST(Collatz, read_1) {
    std::istringstream r("1 1\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    1);
    ASSERT_TRUE(j ==    1);}

TEST(Collatz, read_2) {
    std::istringstream r("999999 1\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    999999);
    ASSERT_TRUE(j ==   1);}

TEST(Collatz, read_3) {
    std::istringstream r("1 10\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    1);
    ASSERT_TRUE(j ==   10);}

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

//My Test cases (cje466)
TEST(Collatz, eval_5) {
    const int v = collatz_eval(637137, 389379);
    ASSERT_TRUE(v == 470);}

TEST(Collatz, eval_6) {
    const int v = collatz_eval(389379, 637137);
    ASSERT_TRUE(v == 470);}

TEST(Collatz, eval_7) {
    const int v = collatz_eval(907275, 628500);
    ASSERT_TRUE(v == 525);}

TEST(Collatz, eval_8) {
    const int v = collatz_eval(9, 9);
    ASSERT_TRUE(v == 20);}
// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

//My Test cases (cje466)
TEST(Collatz, print_1) {
    std::ostringstream w;
    collatz_print(w, 907275, 628500, 525);
    ASSERT_TRUE(w.str() == "907275 628500 525\n");}

TEST(Collatz, print_2) {
    std::ostringstream w;
    collatz_print(w, 916629, 683757, 525);
    ASSERT_TRUE(w.str() == "916629 683757 525\n");}

TEST(Collatz, print_3) {
    std::ostringstream w;
    collatz_print(w, 10, 10, 7);
    ASSERT_TRUE(w.str() == "10 10 7\n");}


// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

//My Test cases (cje466)
TEST(Collatz, solve_1) {
    std::istringstream r("257177 914579\n663141 682373\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "257177 914579 525\n663141 682373 398\n");}

TEST(Collatz, solve_2) {
    std::istringstream r("9 9\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "9 9 20\n");}

TEST(Collatz, solve_3) {
    std::istringstream r("1 1\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 1 1\n");}


// -----
// sequenceLength
// -----

TEST(Collatz, My_helper_Function_sequenceLength_1) {
   const int v = sequenceLength(1);
    ASSERT_TRUE(v == 1);}


TEST(Collatz, My_helper_Function_sequenceLength_2) {
   const int v = sequenceLength(9);
    ASSERT_TRUE(v == 20);}

TEST(Collatz, My_helper_Function_sequenceLength_3) {
   const int v = sequenceLength(999999);
    ASSERT_TRUE(v == 259);}








