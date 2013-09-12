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

TEST(Collatz, ReadNormal) {
    std::istringstream r("1 10\n");
    int i, j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b);
    ASSERT_EQ(1, i);
    ASSERT_EQ(10, j);
}

TEST(Collatz, ReadReverseInput){
	std::istringstream r("10 1\n");
    int i, j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b);
    ASSERT_EQ(10, i);
    ASSERT_EQ(1, j);
}

TEST(Collatz, ReadBadInput){
	std::istringstream r("\n");
	int i, j;
	const bool b = collatz_read(r, i, j);
	ASSERT_FALSE(b);
}

TEST(Collatz, ReadMultiline){
	std::istringstream r("1 2\n3 4\n");
	int i, j;
	const bool first = collatz_read(r, i, j);
	ASSERT_TRUE(first);
	ASSERT_EQ(1, i);
	ASSERT_EQ(2, j);

	int k, m;
	const bool second = collatz_read(r, k, m);
	ASSERT_TRUE(second);
	ASSERT_EQ(3, k);
	ASSERT_EQ(4, m);
}

// ----
// eval
// ----

TEST(Collatz, eval_1) {
    const int v = collatz_eval(1, 10);
    ASSERT_EQ(20, v);}

TEST(Collatz, eval_2) {
    const int v = collatz_eval(100, 200);
    ASSERT_EQ(125, v);}

TEST(Collatz, eval_3) {
    const int v = collatz_eval(201, 210);
    ASSERT_EQ(89, v);}

TEST(Collatz, eval_4) {
    const int v = collatz_eval(900, 1000);
    ASSERT_EQ(174, v);}

TEST(Collatz, EvalIdenticalInput) {
	const int v = collatz_eval(2, 2);
	ASSERT_EQ(2, v);
}

TEST(Collatz, EvalReverseInput) {
	const int v = collatz_eval(10, 1);
	ASSERT_EQ(20, v);
}



// ----------
// do_collatz
// ----------

TEST(Collatz, do_collatz_1){
	const int v = do_collatz(1);
	ASSERT_EQ(1, v);
}

TEST(Collatz, do_collatz_2){
	const int v = do_collatz(2);
	ASSERT_EQ(2, v);
}

TEST(Collatz, do_collatz_3){
	const int v = do_collatz(10);
	ASSERT_EQ(7, v);
}

TEST(Collatz, do_collatz_4){
	const int v = do_collatz(1024);
	ASSERT_EQ(11, v);
}


// -----
// print
// -----

TEST(Collatz, print_1) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_EQ("1 10 20\n", w.str());
}

TEST(Collatz, print_2) {
	std::ostringstream w;
	collatz_print(w, 1, 1, 1);
	ASSERT_EQ("1 1 1\n", w.str());
}

TEST(Collatz, print_3) {
	std::ostringstream w;
	collatz_print(w, 4, 5, 6);
	ASSERT_EQ("4 5 6\n", w.str());
}

// -----
// solve
// -----

TEST(Collatz, SolveMultiline) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", w.str());}

TEST(Collatz, SolveReverseMultiline){
	std::istringstream r("10 1\n200 100\n");
	std::ostringstream w;
	collatz_solve(r, w);
	ASSERT_EQ("10 1 20\n200 100 125\n", w.str());
}

TEST(Collatz, SolveReverseInput){
	std::istringstream r("10 1\n");
	std::ostringstream w;
	collatz_solve(r, w);
	ASSERT_EQ("10 1 20\n", w.str());
}

TEST(Collatz, SolveIdenticalInput){
	std::istringstream r("1 1\n");
	std::ostringstream w;
	collatz_solve(r, w);
	ASSERT_EQ("1 1 1\n", w.str());
}
