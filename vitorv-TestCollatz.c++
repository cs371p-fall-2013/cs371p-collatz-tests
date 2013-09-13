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

TEST(Collatz, readjGreater) {
    std::istringstream r("1 10\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    1);
    ASSERT_TRUE(j ==   10);}

TEST(Collatz, readiGreater) {
    std::istringstream r("10 1\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==   10);
    ASSERT_TRUE(j ==    1);}

TEST(Collatz, readBiggestRange) {
    std::istringstream r("1 1000000\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    1);
    ASSERT_TRUE(j == 1000000);}

// ------
// isEven
// ------

TEST(Collatz, isEvenMinInput) {
    const bool v = collatz_isEven(1);
    ASSERT_TRUE(v == false);}

TEST(Collatz, isEvenMaxInput) {
    const bool v = collatz_isEven(1000000);
    ASSERT_TRUE(v == true);}

TEST(Collatz, isEvenIntermediate1) {
    const bool v = collatz_isEven(666666);
    ASSERT_TRUE(v == true);}

TEST(Collatz, isEvenIntermediate2) {
    const bool v = collatz_isEven(666667);
    ASSERT_TRUE(v == false);}

// ---------- 
// isInBounds
// ----------

TEST(Collatz, isInBoundsInMin) {
    const bool v = collatz_isInBounds(1);
    ASSERT_TRUE(v == true);}

TEST(Collatz, isInBoundsInMax) {
    const bool v = collatz_isInBounds(1000000);
    ASSERT_TRUE(v == true);}

TEST(Collatz, isInBoundsOutMin) {
    const bool v = collatz_isInBounds(0);
    ASSERT_TRUE(v == false);}

TEST(Collatz, isInBoundsOutMax) {
    const bool v = collatz_isInBounds(1000001);
    ASSERT_TRUE(v == false);}

// -------
// isValid
// -------

TEST(Collatz, isValidmin) {
    const bool v = collatz_isValid(2);
    ASSERT_TRUE(v == true);}

TEST(Collatz, isValidmax) {
    const bool v = collatz_isValid(1000000);
    ASSERT_TRUE(v == true);}

TEST(Collatz, isValidfail) {
    const bool v = collatz_isValid(0);
    ASSERT_TRUE(v == false);}

// ---------
// cacheRead
// ---------

TEST(Collatz, cacheReadMin) {
    const int v = collatz_cacheRead(2);
    ASSERT_TRUE(v == 0);}

TEST(Collatz, cacheReadMax) {
    const int v = collatz_cacheRead(1000000);
    ASSERT_TRUE(v == 0);}

TEST(Collatz, cacheReadMid) {
    const int v = collatz_cacheRead(500000);
    ASSERT_TRUE(v == 0);}

// ---------
// cacheHit
// ---------

TEST(Collatz, cacheHitMinInvalid) {
    int i;
    const int v = collatz_cacheHit(1, i);
    ASSERT_TRUE(v == false);}

TEST(Collatz, cacheHitMiddle) {
    int i;
    const int v = collatz_cacheHit(250000, i);
    ASSERT_TRUE(v == false);}

TEST(Collatz, cacheHitMaxInvalid) {
    int i;
    const int v = collatz_cacheHit(500000, i);
    ASSERT_TRUE(v == false);}

// ---------
// nextInput
// ---------

TEST(Collatz, nextInput2to1) {
    const int v = collatz_nextInput(2);
    ASSERT_TRUE(v == 1);}

TEST(Collatz, nextInput3to10) {
    const int v = collatz_nextInput(3);
    ASSERT_TRUE(v == 10);}

TEST(Collatz, nextInput4to2) {
    const int v = collatz_nextInput(4);
    ASSERT_TRUE(v == 2);}

TEST(Collatz, nextInput1000000to500000) {
    const int v = collatz_nextInput(1000000);
    ASSERT_TRUE(v == 500000);}

// -----------
// cycleLength
// -----------

TEST(Collatz, cycleLength1) {
    const int v = collatz_cycleLength(1);
    ASSERT_TRUE(v == 1);}

TEST(Collatz, cycleLength100) {
    const int v = collatz_cycleLength(100);
    ASSERT_TRUE(v == 26);}

TEST(Collatz, cycleLength201) {
    const int v = collatz_cycleLength(201);
    ASSERT_TRUE(v == 19);}

TEST(Collatz, cycleLength900) {
    const int v = collatz_cycleLength(900);
    ASSERT_TRUE(v == 55);}

// --------------
// maxCycleLength
// --------------

TEST(Collatz, maxCycleLength1to10) {
    const int v = collatz_maxCycleLength(1, 10);
    ASSERT_TRUE(v == 20);}

TEST(Collatz, maxCycleLength100to200) {
    const int v = collatz_maxCycleLength(100, 200);
    ASSERT_TRUE(v == 125);}

TEST(Collatz, maxCycleLength201to210) {
    const int v = collatz_maxCycleLength(201, 210);
    ASSERT_TRUE(v == 89);}

TEST(Collatz, maxCycleLength900to1000) {
    const int v = collatz_maxCycleLength(900, 1000);
    ASSERT_TRUE(v == 174);}

// ----
// eval
// ----

TEST(Collatz, eval1to10) {
    const int v = collatz_eval(1, 10);
    ASSERT_TRUE(v == 20);}

TEST(Collatz, eval100to200) {
    const int v = collatz_eval(100, 200);
    ASSERT_TRUE(v == 125);}

TEST(Collatz, eval201to210) {
    const int v = collatz_eval(201, 210);
    ASSERT_TRUE(v == 89);}

TEST(Collatz, eval900to1000) {
    const int v = collatz_eval(900, 1000);
    ASSERT_TRUE(v == 174);}

// -----
// print
// -----

TEST(Collatz, print1) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print2) {
    std::ostringstream w;
    collatz_print(w, 5, 5, 6);
    ASSERT_TRUE(w.str() == "5 5 6\n");}

TEST(Collatz, print3) {
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
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

TEST(Collatz, solve_reverse) {
    std::istringstream r("10 1\n200 100\n210 201\n1000 900\n");
    std::ostringstream w;
    collatz_solve(r,w);
    ASSERT_TRUE(w.str() == "10 1 20\n200 100 125\n210 201 89\n1000 900 174\n");}

TEST(Collatz, solveExtreme) {
    std::istringstream r("1 1000000");
    std::ostringstream w;
    collatz_solve(r,w);
    ASSERT_TRUE(w.str() == "1 1000000 525\n");}
