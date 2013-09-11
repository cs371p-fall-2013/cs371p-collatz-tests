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

TEST(CollatzReadTest, BasicInput) {
	std::istringstream in_stream("1 2\n");
	int first;
	int second;

	const bool read_successful = collatz_read(in_stream, first, second);

	ASSERT_TRUE(read_successful);
	ASSERT_EQ(1, first);
	ASSERT_EQ(2, second);
}

TEST(CollatzReadTest, ReverseInput) {
	std::istringstream in_stream("2 1\n");
	int first;
	int second;

	const bool read_successful = collatz_read(in_stream, first, second);

	ASSERT_TRUE(read_successful);
	ASSERT_EQ(2, first);
	ASSERT_EQ(1, second);
}

TEST(CollatzReadTest, IdenticalInput) {
	std::istringstream in_stream("1 1\n");
	int first;
	int second;

	const bool read_successful = collatz_read(in_stream, first, second);

	ASSERT_TRUE(read_successful);
	ASSERT_EQ(1, first);
	ASSERT_EQ(first, second);
}

// ----
// eval
// ----

TEST(CollatzEvalTest, BasicInput) {
	const int max_cycle_length = collatz_eval(2, 3);
	ASSERT_EQ(8, max_cycle_length);
}

TEST(CollatzEvalTest, ReverseInput) {
	const int max_cycle_length = collatz_eval(3, 2);
	ASSERT_EQ(8, max_cycle_length);
}

TEST(CollatzEvalTest, IdenticalInput) {
	const int max_cycle_length = collatz_eval(2, 2);
	ASSERT_EQ(2, max_cycle_length);
}

TEST(CollatzEvalTest, LargerGapInput) {
	const int max_cycle_length = collatz_eval(100, 200);
	ASSERT_EQ(125, max_cycle_length);
}

TEST(CollatzEvalTest, LowBoundaryBasicInput) {
	const int max_cycle_length = collatz_eval(1, 10);
	ASSERT_EQ(20, max_cycle_length);
}

TEST(CollatzEvalTest, LowBoundaryReverseInput) {
	const int max_cycle_length = collatz_eval(10, 1);
	ASSERT_EQ(20, max_cycle_length);
}

TEST(CollatzEvalTest, LowBoundaryIdenticalInput) {
	const int max_cycle_length = collatz_eval(1, 1);
	ASSERT_EQ(1, max_cycle_length);
}

TEST(CollatzEvalTest, HighBoundaryBasicInput) {
	const int max_cycle_length = collatz_eval(999990, 999999);
	ASSERT_EQ(259, max_cycle_length);
}

TEST(CollatzEvalTest, HighBoundaryReverseInput) {
	const int max_cycle_length = collatz_eval(999999, 999990);
	ASSERT_EQ(259, max_cycle_length);
}

TEST(CollatzEvalTest, HighBoundaryIdenticalInput) {
	const int max_cycle_length = collatz_eval(999999, 999999);
	ASSERT_EQ(259, max_cycle_length);
}

// ------------
// cycle length
// ------------

TEST(CollatzCycleLengthTest, Basic) {
	const int cycle_length = collatz_find_cycle_length(10);
	ASSERT_EQ(7, cycle_length);
}

TEST(CollatzCycleLengthTest, LowBoundary) {
	const int cycle_length = collatz_find_cycle_length(1);
	ASSERT_EQ(1, cycle_length);
}

TEST(CollatzCycleLengthTest, HighBoundary) {
	const int cycle_length = collatz_find_cycle_length(999999);
	ASSERT_EQ(259, cycle_length);
}

// -----
// print
// -----

TEST(CollatzPrintTest, BasicInput) {
	std::ostringstream out_stream;

	collatz_print(out_stream, 1, 2, 3);
	ASSERT_STREQ("1 2 3\n", out_stream.str().c_str());
}

TEST(CollatzPrintTest, DifferentOrderInput) {
	std::ostringstream out_stream;

	collatz_print(out_stream, 3, 1, 2);
	ASSERT_STREQ("3 1 2\n", out_stream.str().c_str());
}

// -----
// solve
// -----

TEST(CollatzSolveTest, SingleLineInput) {
	std::istringstream in_stream("1 10\n");
	std::ostringstream out_stream;

	collatz_solve(in_stream, out_stream);
	ASSERT_STREQ("1 10 20\n", out_stream.str().c_str());
}

TEST(CollatzSolveTest, MultipleLineInput) {
	std::istringstream in_stream("1 10\n100 200\n");
	std::ostringstream out_stream;

	collatz_solve(in_stream, out_stream);
	ASSERT_STREQ("1 10 20\n100 200 125\n", out_stream.str().c_str());
}

TEST(CollatzSolveTest, EmptyInput) {
	std::istringstream in_stream("");
	std::ostringstream out_stream;

	collatz_solve(in_stream, out_stream);
	ASSERT_STREQ("", out_stream.str().c_str());
}

