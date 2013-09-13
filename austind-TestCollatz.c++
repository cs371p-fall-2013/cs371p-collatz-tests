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

TEST(Collatz, read_same) {
	std::istringstream r("3 3\n");
	int i, j;
	const bool b = collatz_read(r, i, j);
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(i == 3);
	ASSERT_TRUE(j == 3);
}

TEST(Collatz, read_descending) {
	std::istringstream r("100 99\n");
	int i, j;
	const bool b = collatz_read(r, i, j);
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(i == 100);
	ASSERT_TRUE(j == 99);
}

TEST(Collatz, read_large) {
	std::istringstream r("65535 65536\n");
	int i, j;
	const bool b = collatz_read(r, i, j);
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(i == 65535);
	ASSERT_TRUE(j == 65536);
}

TEST(Collatz, read_oneone) {
	std::istringstream r("1 1\n");
	int i, j;
	const bool b = collatz_read(r, i, j);
	ASSERT_TRUE(b == true);
	ASSERT_TRUE(i == 1);
	ASSERT_TRUE(j == 1);
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

TEST(Collatz, eval_5) {
	const int v = collatz_eval(1, 2);
	ASSERT_TRUE(v == 2);}

TEST(Collatz, eval_6) {
	const int v = collatz_eval(1, 1);
	ASSERT_TRUE(v == 1);}

TEST(Collatz, eval_7) {
	const int v = collatz_eval(555, 560);
	ASSERT_TRUE(v == 88);}

TEST(Collatz, eval_8) {
	const int v = collatz_eval(1024, 1024);
	ASSERT_TRUE(v == 11);}

//tests stolen from ghawk88
//TEST(Collatz, eval_9) {
//	const int v = collatz_eval(250000, 500000);
//	ASSERT_TRUE(v == 449);}

TEST(Collatz, eval_10) {
	const int v = collatz_eval(999999, 999999);
	ASSERT_TRUE(v == 259);}

TEST(Collatz, eval_11) {
	const int v = collatz_eval(785, 541);
	ASSERT_TRUE(v == 171);}




// -----
// print
// -----

TEST(Collatz, print1) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print_desc_high) {
	std::ostringstream w;
	collatz_print(w, 8, 7, 888);
	ASSERT_TRUE(w.str() == "8 7 888\n");}

TEST(Collatz, print_asc_low) {
	std::ostringstream w;
	collatz_print(w, 12, 65535, 1);
	ASSERT_TRUE(w.str() == "12 65535 1\n");}

TEST(Collatz, print_desc_low) {
	std::ostringstream w;
	collatz_print(w, 999, 888, 777);
	ASSERT_TRUE(w.str() == "999 888 777\n");}

// -----
// solve
// -----

TEST(Collatz, solve_default) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

TEST(Collatz, solve_triple) {
	std::istringstream r("1 10\n1 10\n1 10\n");
	std::ostringstream w;
	collatz_solve(r, w);
	ASSERT_TRUE(w.str() == "1 10 20\n1 10 20\n1 10 20\n");}

TEST(Collatz, solve_empty) {
	std::istringstream r("");
	std::ostringstream w;
	collatz_solve(r, w);
	ASSERT_TRUE(w.str() == "");}

TEST(Collatz, solve_single) {
	std::istringstream r("27 27\n");
	std::ostringstream w;
	collatz_solve(r, w);
	ASSERT_TRUE(w.str() == "27 27 112\n");}

