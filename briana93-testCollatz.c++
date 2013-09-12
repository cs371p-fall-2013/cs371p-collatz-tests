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

TEST(Collatz, read_Jlessthani) {
	std::istringstream r("10 1\n");
	int i, j;
	const bool b = collatz_read(r, i, j);
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(i == 10);
	ASSERT_TRUE(j == 1);
}

TEST(Collatz, read_Duplicate) {
	std::istringstream r("1 1\n");
	int i, j;
	const bool b = collatz_read(r, i, j);
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(i == 1);
	ASSERT_TRUE(j == 1);
}

TEST(Collatz, read_LargeRange) {
	std::istringstream r("9 8000\n");
	int i, j;
	const bool b = collatz_read(r, i, j);
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(i == 9);
	ASSERT_TRUE(j == 8000);
}

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

TEST(Collatz, eval_duplicate) {
    const int v = collatz_eval(1, 1);
    ASSERT_TRUE(v == 1);}

TEST(Collatz, eval_jLessThani) {
    const int v = collatz_eval(10, 1);
    ASSERT_TRUE(v == 20);}

TEST(Collatz, eval_largeRange) {
    const int v = collatz_eval(99, 9999);
    ASSERT_TRUE(v == 262);}

// -----
// print
// -----

TEST(Collatz, print_1) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

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

TEST(Collatz, print_5) {
    std::ostringstream w;
    collatz_print(w, 1, 1, 1);
    ASSERT_TRUE(w.str() == "1 1 1\n");}

// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
	std::cout << w.str();
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

TEST(Collatz, solve_average) {
    std::istringstream r("201 210\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "201 210 89\n");}


TEST(Collatz, solve_noinput) {
    std::istringstream r("");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "");}
    
TEST(Collatz, solve_largeRange) {
    std::istringstream r("900 1000");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "900 1000 174\n");}

// ----
// doCollatz
// ----

TEST(Collatz, doCollatz_1) {
    const int v = doCollatz(1, 0);
    ASSERT_TRUE(v == 1);}

TEST(Collatz, doCollatz_2) {
    const int v = doCollatz(22, 0);
    ASSERT_TRUE(v == 16);}

TEST(Collatz, doCollatz_3) {
    const int v = doCollatz(20, 0);
    ASSERT_TRUE(v == 8);}
