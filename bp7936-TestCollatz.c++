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

TEST(Collatz, read) {
    std::istringstream r("1 10\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 1);
    ASSERT_TRUE(j == 10);}

TEST(Collatz, read_SMALL) {
    std::istringstream r("3 5\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 3);
    ASSERT_TRUE(j == 5);}

TEST(Collatz, read_LARGE) {
    std::istringstream r("6652 578273\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 6652);
    ASSERT_TRUE(j == 578273);}

TEST(Collatz, read_MAX) {
    std::istringstream r("1 999999\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 1);
    ASSERT_TRUE(j == 999999);}

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

TEST(Collatz, eval_SMALL) {
	const int v = collatz_eval(50, 51);
	ASSERT_TRUE(v == 25);}

TEST(Collatz, eval_MED) {
	const int v = collatz_eval(1, 50000);
	ASSERT_TRUE(v == 324);}

TEST(Collatz, eval_LARGE) {
	const int v = collatz_eval(50000, 100000);
	ASSERT_TRUE(v == 351);}


// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print_2) {
	std::ostringstream w;
	collatz_print(w, 10, 15, 18);
	ASSERT_TRUE(w.str() == "10 15 18\n");}

TEST(Collatz, print_3) {
	std::ostringstream w;
	collatz_print(w, 50, 75, 116);
	ASSERT_TRUE(w.str() == "50 75 116\n");}

TEST(Collatz, print_4) {
	std::ostringstream w;
	collatz_print(w, 1, 2, 2);
	ASSERT_TRUE(w.str() == "1 2 2\n");}

// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

TEST(Collatz, solve_2) {
    std::istringstream r("10 15\n10 15\n1 10\n1 10\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "10 15 18\n10 15 18\n1 10 20\n1 10 20\n");}

TEST(Collatz, solve_3) {
    std::istringstream r("50 75\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "50 75 116\n");}

TEST(Collatz, solve_4) {
    std::istringstream r("1 2\n3 5\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 2 1\n3 5 8\n");}
