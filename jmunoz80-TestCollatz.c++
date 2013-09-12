#include <iostream> 
#include <sstream>
#include <string>

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

TEST(Collatz, reverse_read) {
    std::istringstream r("10 1\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 10);
    ASSERT_TRUE(j == 1);}

TEST(Collatz, large_read) {
    std::istringstream r("1 10000000\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 1);
    ASSERT_TRUE(j == 10000000);}

TEST(Collatz, spaced_read) {
    std::istringstream r("1    5\n");
    int i;
    int j;
    const bool b = collatz_read(r, i, j);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i == 1);
    ASSERT_TRUE(j == 5);}
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

TEST(Collatz, short_eval) {
    const int v = collatz_eval(15, 16);
    ASSERT_TRUE(v == 18);}

TEST(Collatz, long_eval) {
    const int v = collatz_eval(1, 1000000);
    ASSERT_TRUE(v == 525);}

// -----
// print
// -----

TEST(Collatz, print) {
    std::ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_TRUE(w.str() == "1 10 20\n");}

TEST(Collatz, print_2) {
    std::ostringstream w;
    collatz_print(w, 10, 20, 20);
    ASSERT_TRUE(w.str() == "10 20 20\n");}

TEST(Collatz, print_3) {
    std::ostringstream w;
    collatz_print(w, 45, 50, 104);
    ASSERT_TRUE(w.str() == "45 50 104\n");}

// -----
// solve
// -----

TEST(Collatz, solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}


TEST(Collatz, reverse_solve) {
    std::istringstream r("10 1\n20 10\n210 201\n1000 900\n50 45");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "10 1 20\n20 10 21\n210 201 89\n1000 900 174\n50 45 105\n");}

TEST(Collatz, long_solve) {
    std::istringstream r("1 10\n100 200\n201 210\n900 1000\n 1 1000000");
    std::ostringstream w;
    collatz_solve(r, w);
    ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n1 1000000 525\n");}
