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

#define cachesize 100000

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
    ASSERT_TRUE(j ==   10);
}

TEST(Collatz, read_2) {
    std::istringstream r("\n\n\n\n          1\n\n     \n\n\n\n\n10\n\n\n    4\n\n\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    1);
    ASSERT_TRUE(j ==   10);
}

TEST(Collatz, read_3) {
    std::istringstream r("200 1\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==   200);
    ASSERT_TRUE(j ==   1);
}

TEST(Collatz, read_4) {
    std::istringstream r("    \n\n  ");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == false);
}

TEST(Collatz, read_5) {
    std::istringstream r("\n\n\n\n\n\n                   77777         \n\n\t\t\t\n\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == false);
}

TEST(Collatz, read_6) {
    std::istringstream r("1 2\n\n\n\n   \t\t\t  3 4     5 \n   \n\t\n 6 7 8 9\n");
    int i;
    int j;
    bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    1);
    ASSERT_TRUE(j ==    2);
    b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    3);
    ASSERT_TRUE(j ==    4);
    b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    5);
    ASSERT_TRUE(j ==    6);
    b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    7);
    ASSERT_TRUE(j ==    8);
    b = collatz_read(r, i, j);
    ASSERT_TRUE(b == false);
}

// ------------
// cycle_length
// ------------

TEST(Collatz, cycle_length_1) {
    int cache[cachesize];
    int x = 0;
    for(x = 0; x < cachesize; x++)
        cache[x] = 0;
    int v = collatz_cycle_length(1, cache);
    ASSERT_TRUE(v == 1);
}

TEST(Collatz, cycle_length_2) {
    int cache[cachesize];
    int x = 0;
    for(x = 0; x < cachesize; x++)
        cache[x] = 0;
    int i;
    for(i = 1; i < 70; i++)
    {
        int v = collatz_cycle_length(i, cache);
        ASSERT_TRUE(v == collatz_cycle_length(i*2, cache)-1);
    }
}

TEST(Collatz, cycle_length_3) {
    int cache[cachesize];
    int x = 0;
    for(x = 0; x < cachesize; x++)
        cache[x] = 0;
    int i;
    for(i = 2; i < 280; i+=2)
    {
        int v = collatz_cycle_length(i, cache);
        ASSERT_TRUE(v == collatz_cycle_length(i/2, cache)+1);
    }
}

TEST(Collatz, cycle_length_4) {
    int cache[cachesize];
    int x = 0;
    for(x = 0; x < cachesize; x++)
        cache[x] = 0;
    int v = collatz_cycle_length(113383, cache);
    ASSERT_TRUE(v == 248);
}


// ----
// eval
// ----

TEST(Collatz, eval_1) {
    int cache[cachesize];
    int x = 0;
    for(x = 0; x < cachesize; x++)
        cache[x] = 0;
    const int v = collatz_eval(1, 10, cache);
    ASSERT_TRUE(v == 20);}

TEST(Collatz, eval_2) {
    int cache[cachesize];
    int x = 0;
    for(x = 0; x < cachesize; x++)
        cache[x] = 0;
    const int v = collatz_eval(100, 200, cache);
    ASSERT_TRUE(v == 125);}

TEST(Collatz, eval_3) {
    int cache[cachesize];
    int x = 0;
    for(x = 0; x < cachesize; x++)
        cache[x] = 0;
    const int v = collatz_eval(201, 210, cache);
    ASSERT_TRUE(v == 89);}

TEST(Collatz, eval_4) {
    int cache[cachesize];
    int x = 0;
    for(x = 0; x < cachesize; x++)
        cache[x] = 0;
    const int v = collatz_eval(900, 1000, cache);
    ASSERT_TRUE(v == 174);}

TEST(Collatz, eval_5) {
    int cache[cachesize];
    int x = 0;
    for(x = 0; x < cachesize; x++)
        cache[x] = 0;
    int i = 1;
    while (i < 80000)
    {
        int v = collatz_eval(i, i, cache);
        i *= 2;
        ASSERT_TRUE(collatz_eval(i, i, cache) == 1 + v);
    }
}

TEST(Collatz, eval_6) {
    int cache[cachesize];
    int x = 0;
    for(x = 0; x < cachesize; x++)
        cache[x] = 0;
    int i = 3;
    while (i < 80000)
    {
        int v = collatz_eval(i, i, cache);
        i *= 2;
        ASSERT_TRUE(collatz_eval(i, i, cache) == 1 + v);
    }
}

TEST(Collatz, eval_7) {
    int cache[cachesize];
    int x = 0;
    for(x = 0; x < cachesize; x++)
        cache[x] = 0;
    int i = 100;
    for(; i < 500; i++)
       ASSERT_TRUE(collatz_eval(i/2, i, cache) >= collatz_eval(1, i, cache));
}

// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print_2) {
    std::ostringstream w;
    collatz_print(w, 100000, 10, 20);
    ASSERT_TRUE(w.str() == "100000 10 20\n");}

// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

TEST(Collatz, solve_2) {
    std::istringstream r("");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "");
}

TEST(Collatz, solve_3) {
    std::istringstream r("10 1\n200 100\n210 201\n1000 900\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "10 1 20\n200 100 125\n210 201 89\n1000 900 174\n");}
