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

TEST(Collatz, reverse_read){
    std::istringstream r("10 1\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 10);
    ASSERT_TRUE(j == 1);
}

TEST(Collatz, read_large){
    std::istringstream r("999991 999999\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 999991);
    ASSERT_TRUE(j == 999999);
}

// ----
// eval
// ----

//------------
// value tests
//------------
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

TEST(Collatz, eval_lower_bound) {
    const int v = collatz_eval(1,4);
    ASSERT_TRUE(v == 8);
}

/*TEST(Collatz, eval_upper_bound) {
    const int v = collatz_eval(999990,999999);
    ASSERT_TRUE(v == 259);
} */


//------------
// cache tests
//------------

//---------------
// Odd input test
//---------------

TEST(Collatz, identical_input){
    const int v = collatz_eval(1,1);
    ASSERT_TRUE(v == 1);
}

TEST(Collatz, larger_I_than_J){
    const int v = collatz_eval(200, 100);
    ASSERT_TRUE(v == 125);
}


// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");
}

TEST(Collatz, print_reverse) {
    std::ostringstream w;
    collatz_print(w, 10, 1, 20);
    ASSERT_TRUE(w.str() == "10 1 20\n");
}

TEST(Collatz, print_large) {
    std::ostringstream w;
    collatz_print(w, 999990, 999999, 259);
    ASSERT_TRUE(w.str() == "999990 999999 259\n");
}

TEST(Collatz, print_same) {
    std::ostringstream w;
    collatz_print(w, 50, 50, 50);
    ASSERT_TRUE(w.str() == "50 50 50\n");
}
// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");
}

TEST(Collatz, solve_reverse) {
    std::istringstream r("10 1\n200 100\n210 201\n1000 900\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "10 1 20\n200 100 125\n210 201 89\n1000 900 174\n");
}


TEST(Collatz, solve_duplicates) {
    std::istringstream r("1 1\n100 100\n1000 1000\n999 999\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 1 1\n100 100 26\n1000 1000 112\n999 999 50\n");
}


/*TEST(Collatz, solve_large) {
    std::istringstream r("999990 999999\n900000 999999\n800000 888888\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "999990 999999 259\n900000 999999 476\n800000 888888 450\n");
}*/