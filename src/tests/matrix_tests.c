#include "tests.h"

START_TEST(create_01) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(1, 1, &A);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(create_02) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(create_03) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(3, 2, &A);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(create_04) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(2, 4, &A);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(create_05) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(10, 15, &A);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(create_06) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(0, 0, &A);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(create_07) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(1, 0, &A);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(create_08) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(0, 1, &A);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(create_09) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(-1, 1, &A);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(remove_01) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(2, 2, &A);
  s21_remove_matrix(&A);
  if (A.matrix != NULL) {
    res = 1;
  }
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(remove_02) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(1, 1, &A);
  s21_remove_matrix(&A);
  if (A.matrix != NULL) {
    res = 1;
  }
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(remove_03) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(3, 2, &A);
  s21_remove_matrix(&A);
  if (A.matrix != NULL) {
    res = 1;
  }
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(remove_04) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(3, 4, &A);
  s21_remove_matrix(&A);
  if (A.matrix != NULL) {
    res = 1;
  }
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(remove_05) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(3, 2, &A);
  s21_remove_matrix(&A);
  if (A.matrix != NULL) {
    res = 1;
  }
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(equal_01) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(3, 2, &A);
  s21_numb_matrix(1.0, &A);

  s21_create_matrix(3, 2, &B);
  s21_numb_matrix(1.0, &B);

  res = s21_eq_matrix(&A, &B);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(equal_02) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(3, 2, &A);
  s21_numb_matrix(1.0, &A);

  s21_create_matrix(3, 2, &B);
  s21_numb_matrix(2.0, &B);

  res = s21_eq_matrix(&B, &A);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(equal_03) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(3, 2, &A);
  s21_numb_matrix(10.0, &A);

  s21_create_matrix(3, 2, &B);
  s21_numb_matrix(-10.0, &B);

  res = s21_eq_matrix(&A, &B);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(equal_04) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(3, 2, &A);
  s21_numb_matrix(1.0, &A);
  s21_create_matrix(3, 3, &B);
  s21_numb_matrix(1.0, &B);
  res = s21_eq_matrix(&A, &B);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(equal_05) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(10, 10, &A);
  s21_numb_matrix(1.0, &A);

  s21_create_matrix(10, 10, &B);
  s21_numb_matrix(1.0, &B);

  res = s21_eq_matrix(&A, &B);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

Suite *matrix_tests() {
  Suite *s = suite_create("matrix_tests");
  TCase *o = tcase_create("matrix_tests");
  suite_add_tcase(s, o);

  tcase_add_test(o, create_01);
  tcase_add_test(o, create_02);
  tcase_add_test(o, create_03);
  tcase_add_test(o, create_04);
  tcase_add_test(o, create_05);
  tcase_add_test(o, create_06);
  tcase_add_test(o, create_07);
  tcase_add_test(o, create_08);
  tcase_add_test(o, create_09);

  tcase_add_test(o, remove_01);
  tcase_add_test(o, remove_02);
  tcase_add_test(o, remove_03);
  tcase_add_test(o, remove_04);
  tcase_add_test(o, remove_05);

  tcase_add_test(o, equal_01);
  tcase_add_test(o, equal_02);
  tcase_add_test(o, equal_03);
  tcase_add_test(o, equal_04);
  tcase_add_test(o, equal_05);

  return s;
}