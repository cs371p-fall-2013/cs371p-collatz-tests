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
    ASSERT_EQ(b, true);
    ASSERT_EQ(i, 1);
    ASSERT_EQ(j, 10);}

// ----
// length
// ----

TEST(Collatz, length_1){
    const int v = collatz_length(22);
    ASSERT_EQ(v, 16);
}

TEST(Collatz, length_2){
    const int v = collatz_length(1);
    ASSERT_EQ(v, 1);
}

TEST(Collatz, length_3){
    const int v = collatz_length(10);
    ASSERT_EQ(v, 7);
}
// ----
// eval
// ----

TEST(Collatz, eval_1) {
    int cache[1000000];
    const int v = collatz_eval(1, 10, cache);
    ASSERT_EQ(v, 20);}

TEST(Collatz, eval_2) {
    int cache[1000000];
    const int v = collatz_eval(100, 200, cache);
    ASSERT_EQ(v, 125);}

TEST(Collatz, eval_3) {
    int cache[1000000];
    const int v = collatz_eval(201, 210, cache);
    ASSERT_EQ(v, 89);}

TEST(Collatz, eval_4) {
    int cache[1000000];
    const int v = collatz_eval(900, 1000, cache);
    ASSERT_EQ(v, 174);}

TEST(Collatz, eval_backwards){
    int cache[1000000];
    const int v = collatz_eval(10, 1, cache);
    ASSERT_EQ(v, 20);}

// -----
// print
// -----

TEST(Collatz, print_1) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_EQ(w.str(), "1 10 20\n");}

TEST(Collatz, print_2) {
    std::ostringstream w;
    collatz_print(w, 1, 1, 1);
    ASSERT_EQ(w.str(), "1 1 1\n");}

TEST(Collatz, print_3) {
    std::ostringstream w;
    collatz_print(w, 5, 2, 8);
    ASSERT_EQ(w.str(), "5 2 8\n");}

// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ(w.str(), "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

TEST(Collatz, solve2) {
    std::istringstream r("89384 30887\n92778 36916\n47794 38336\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ(w.str(), "89384 30887 351\n92778 36916 351\n47794 38336 314\n");}

TEST(Collatz, solve3) {
    std::istringstream r("19583 546\n98815 33368\n15435 90365\n44044 13751\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ(w.str(), "19583 546 279\n98815 33368 351\n15435 90365 351\n44044 13751 324\n");}
