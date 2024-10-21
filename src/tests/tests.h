#ifndef MATRIX_TEST_H
#define MATRIX_TEST_H

#include <check.h>

#define MAX_DOUBLE 1.79769e+308
#define MIN_DOUBLE 2.22507e-308

#include "../s21_matrix.h"

Suite *matrix_tests();
Suite *arithmetic_tests();
Suite *complements_tests();

#endif