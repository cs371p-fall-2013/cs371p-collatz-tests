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
//My Tests - Jeffrey Fulkerson
TEST(Collatz, read_j1) {
    std::istringstream r("1 20\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 1);
    ASSERT_TRUE(j == 20);
}
TEST(Collatz, read_j2) {
    std::istringstream r("5 250\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 5);
    ASSERT_TRUE(j == 250);
}
TEST(Collatz, read_j3) {
    std::istringstream r("10 30\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 10);
    ASSERT_TRUE(j == 30);
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

//My Tests - Jeffrey Fulkerson
TEST(Collatz, eval_j1) {
    const int v = collatz_eval(1, 1);
    ASSERT_TRUE(v == 1);}

TEST(Collatz, eval_j2) {
    const int v = collatz_eval(3, 9);
    ASSERT_TRUE(v == 20);}

TEST(Collatz, eval_j3) {
    const int v = collatz_eval(127183, 190619);
    ASSERT_TRUE(v == 383);}

TEST(Collatz, eval_j4) {
    const int v = collatz_eval(133, 471855);
    ASSERT_TRUE(v == 449);}




// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}
//My Tests - Jeffrey Fulkerson
TEST(Collatz, print_j1) {
    std::ostringstream w;
    collatz_print(w, 100, 200, 125);
    ASSERT_TRUE(w.str() == "100 200 125\n");}
TEST(Collatz, print_j2) {
    std::ostringstream w;
    collatz_print(w, 201, 210, 89);
    ASSERT_TRUE(w.str() == "201 210 89\n");}
TEST(Collatz, print_j3) {
    std::ostringstream w;
    collatz_print(w, 900, 1000, 174);
    ASSERT_TRUE(w.str() == "900 1000 174\n");}





// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}
//My Tests - Jeffrey Fulkerson
TEST(Collatz, solve_j1) {
    std::istringstream r("99964 184051\n277290 881306\n571744 881153\n267428 874763\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "99964 184051 383\n277290 881306 525\n571744 881153 525\n267428 874763 525\n");}
TEST(Collatz, solve_j2) {
    std::istringstream r("1 1\n2 2\n3 3\n4 4\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 1 1\n2 2 2\n3 3 8\n4 4 3\n");}
TEST(Collatz, solve_j3) {
    std::istringstream r("5 5\n6 6\n7 7\n8 8");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "5 5 6\n6 6 9\n7 7 17\n8 8 4\n");}

