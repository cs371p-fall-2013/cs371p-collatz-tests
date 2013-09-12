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

TEST(Collatz, read1) {
    std::istringstream r("1 10\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    1);
    ASSERT_TRUE(j ==   10);}

TEST(Collatz, read2) {
    std::istringstream r("71 51\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==   71);
    ASSERT_TRUE(j ==   51);}

TEST(Collatz, read3) {
    std::istringstream r("1 1\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==   1);
    ASSERT_TRUE(j ==   1);}

TEST(Collatz, read4) {
    std::istringstream r("35 35\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==   35);
    ASSERT_TRUE(j ==   35);}

// TEST(Collatz, read) {
//     std::istringstream         r("71 51\n");
//     std::istream_iterator<int> q(r);
//     const std::pair<int, int>  p = collatz_read(q);
//     ASSERT_TRUE(p.first  ==  71);
//     ASSERT_TRUE(p.second == 51);}

// TEST(Collatz, read) {
//     std::istringstream         r("96 31\n");
//     std::istream_iterator<int> q(r);
//     const std::pair<int, int>  p = collatz_read(q);
//     ASSERT_TRUE(p.first  ==  96);
//     ASSERT_TRUE(p.second == 31);}

// TEST(Collatz, read) {
//     std::istringstream         r("905109 782975\n");
//     std::istream_iterator<int> q(r);
//     const std::pair<int, int>  p = collatz_read(q);
//     ASSERT_TRUE(p.first  ==  905109);
//     ASSERT_TRUE(p.second == 782975);}

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
    const int v = collatz_eval(71, 51);
    ASSERT_TRUE(v == 113);}

TEST(Collatz, eval_6) {
    const int v = collatz_eval(1, 1);
    ASSERT_TRUE(v == 1);}

TEST(Collatz, eval_7) {
    const int v = collatz_eval(96, 31);
    ASSERT_TRUE(v == 116);}

// -----
// print
// -----

TEST(Collatz, print1) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print2) {
    std::ostringstream w;
    collatz_print(w, 71, 51, 113);
    ASSERT_TRUE(w.str() == "71 51 113\n");}

TEST(Collatz, print3) {
    std::ostringstream w;
    collatz_print(w,1, 1, 1);
    ASSERT_TRUE(w.str() == "1 1 1\n");}

TEST(Collatz, print4) {
    std::ostringstream w;
    collatz_print(w, 35, 35, 14);
    ASSERT_TRUE(w.str() == "35 35 14\n");}

// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

TEST(Collatz, solve2) {
    std::istringstream r("5092 7918\n7693 3573\n4709 4801\n3476 9766\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "5092 7918 262\n7693 3573 262\n4709 4801 197\n3476 9766 262\n");}

TEST(Collatz, solve3) {
    std::istringstream r("1 1\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 1 1\n100 200 125\n201 210 89\n900 1000 174\n");}

TEST(Collatz, solve4) {
    std::istringstream r("71 51\n74 75\n96 31\n45 17\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "71 51 113\n74 75 23\n96 31 116\n45 17 112\n");}