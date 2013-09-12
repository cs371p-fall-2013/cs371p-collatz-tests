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
	
TEST(Collatz, read_2) {
	std::istringstream r("999999 999999\n");
	int i;
	int j;
	const bool b = collatz_read(r, i, j);
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(i == 999999);
	ASSERT_TRUE(j == 999999);}
	
TEST(Collatz, read_3) {
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
	
// --------------
// getCycleLength
// --------------

TEST(Collatz, getCycleLength_1) {
	const int r = getCycleLength(31546);
	ASSERT_TRUE(r == 179);}
	
TEST(Collatz, getCycleLength_2) {
	const int r = getCycleLength(1);
	ASSERT_TRUE(r == 1);}

TEST(Collatz, getCycleLength_3) {
	const int r = getCycleLength(50000);
	ASSERT_TRUE(r == 128);}

// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print_2) {
	std::ostringstream w;
	collatz_print(w, 999999, 999999, 259);
	ASSERT_TRUE(w.str() == "999999 999999 259\n");}

TEST(Collatz, print_3) {
	std::ostringstream w;
	collatz_print(w, -1, -1, -1);	//arbitrary impossible values
	ASSERT_TRUE(w.str() == "-1 -1 -1\n");}

// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}
	
TEST(Collatz, solve_2) {
	std::istringstream r("15934 27744\n16263 41530\n19701 25509\n");
	std::ostringstream w;
	collatz_solve(r, w);
	ASSERT_TRUE(w.str() == "15934 27744 308\n16263 41530 324\n19701 25509 282\n");}

TEST(Collatz, solve_3) {
	std::istringstream r("49753 37257\n17257 8120\n49712 18352\n");
	std::ostringstream w;
	collatz_solve(r, w);
	ASSERT_TRUE(w.str() == "49753 37257 314\n17257 8120 276\n49712 18352 324\n");}
