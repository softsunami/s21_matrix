#include <check.h>
#include <stdlib.h>

#include "s21_matrix.h"

START_TEST(s21_create_matrix_test) {
  matrix_t m1;
  int result;

  result = s21_create_matrix(1, 3, &m1);
  ck_assert_int_eq(result, S21_SUCCESS);
  s21_remove_matrix(&m1);

  result = s21_create_matrix(3, 1, &m1);
  ck_assert_int_eq(result, S21_SUCCESS);
  s21_remove_matrix(&m1);

  result = s21_create_matrix(0, 2, &m1);
  ck_assert_int_eq(result, S21_INCORRECT);
  s21_remove_matrix(&m1);

  result = s21_create_matrix(-1, -5, &m1);
  ck_assert_int_eq(result, S21_INCORRECT);
  s21_remove_matrix(&m1);
}
END_TEST

START_TEST(s21_eq_matrix_test) {
  matrix_t m1, m2;
  int result;

  s21_create_matrix(3, 3, &m1);
  s21_create_matrix(3, 3, &m2);
  result = s21_eq_matrix(&m1, &m2);
  ck_assert_int_eq(result, 1);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      m1.matrix[i][j] = i + j;
      m2.matrix[i][j] = i + j;
    }
  }

  result = s21_eq_matrix(&m1, &m2);
  ck_assert_int_eq(result, 1);

  m1.matrix[0][0] = 10;

  result = s21_eq_matrix(&m1, &m2);
  ck_assert_int_eq(result, 0);

  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);

  s21_create_matrix(3, 4, &m1);
  s21_create_matrix(4, 3, &m2);
  result = s21_eq_matrix(&m1, &m2);
  ck_assert_int_eq(result, 0);

  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(s21_sum_matrix_test) {
  matrix_t m1, m2, m3;
  int result;

  s21_create_matrix(2, 2, &m1);
  s21_create_matrix(2, 2, &m2);

  result = s21_sum_matrix(&m1, &m2, &m3);
  ck_assert_int_eq(result, S21_SUCCESS);
  s21_remove_matrix(&m3);

  m1.matrix[0][0] = 5;

  result = s21_sum_matrix(&m1, &m2, &m3);
  ck_assert_int_eq(result, S21_SUCCESS);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&m3);

  s21_create_matrix(2, 3, &m1);
  s21_create_matrix(3, 2, &m2);

  result = s21_sum_matrix(&m1, &m2, &m3);
  ck_assert_int_eq(result, S21_ARTH_ERROR);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);

  s21_create_matrix(-2, 3, &m1);
  s21_create_matrix(3, 2, &m2);

  result = s21_sum_matrix(&m1, &m2, &m3);
  ck_assert_int_eq(result, S21_INCORRECT);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(s21_sub_matrix_test) {
  matrix_t m1, m2, m3;
  int result;

  s21_create_matrix(2, 2, &m1);
  s21_create_matrix(2, 2, &m2);
  result = s21_sub_matrix(&m1, &m2, &m3);
  ck_assert_int_eq(result, S21_SUCCESS);
  s21_remove_matrix(&m3);

  m1.matrix[0][0] = 5;
  result = s21_sub_matrix(&m1, &m2, &m3);
  ck_assert_int_eq(result, S21_SUCCESS);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&m3);

  s21_create_matrix(2, 3, &m1);
  s21_create_matrix(3, 2, &m2);
  result = s21_sub_matrix(&m1, &m2, &m3);
  ck_assert_int_eq(result, S21_ARTH_ERROR);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);

  s21_create_matrix(-2, 3, &m1);
  s21_create_matrix(3, 2, &m2);
  result = s21_sub_matrix(&m1, &m2, &m3);
  ck_assert_int_eq(result, S21_INCORRECT);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(s21_mult_number_test) {
  int result;
  matrix_t m1, m2;

  s21_create_matrix(3, 3, &m1);
  result = s21_mult_number(&m1, 5, &m2);
  ck_assert_int_eq(result, S21_SUCCESS);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);

  s21_create_matrix(3, 0, &m1);
  result = s21_mult_number(&m1, 0, &m2);
  ck_assert_int_eq(result, S21_INCORRECT);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(s21_mult_matrix_test) {
  int result;
  matrix_t m1, m2, m3;

  // Default test 1
  s21_create_matrix(3, 3, &m1);
  s21_create_matrix(3, 3, &m2);
  result = s21_mult_matrix(&m1, &m2, &m3);
  ck_assert_int_eq(result, S21_SUCCESS);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&m3);

  // Default test 2
  s21_create_matrix(3, 4, &m1);
  s21_create_matrix(4, 3, &m2);
  result = s21_mult_matrix(&m1, &m2, &m3);
  ck_assert_int_eq(result, S21_SUCCESS);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&m3);

  // Default test 3
  s21_create_matrix(1, 5, &m1);
  s21_create_matrix(5, 3, &m2);
  result = s21_mult_matrix(&m1, &m2, &m3);
  ck_assert_int_eq(result, S21_SUCCESS);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&m3);

  // Incorrect test 1
  s21_create_matrix(-3, 4, &m1);
  s21_create_matrix(4, 3, &m2);
  result = s21_mult_matrix(&m1, &m2, &m3);
  ck_assert_int_eq(result, S21_INCORRECT);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&m3);

  // Incorrect test 2
  s21_create_matrix(3, 4, &m1);
  s21_create_matrix(5, -3, &m2);
  result = s21_mult_matrix(&m1, &m2, &m3);
  ck_assert_int_eq(result, S21_INCORRECT);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&m3);

  // Arth error test 1
  s21_create_matrix(1, 5, &m1);
  s21_create_matrix(2, 4, &m2);
  result = s21_mult_matrix(&m1, &m2, &m3);
  ck_assert_int_eq(result, S21_ARTH_ERROR);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&m3);

  // Functional test 1
  s21_create_matrix(1, 3, &m1);
  s21_create_matrix(3, 2, &m2);
  m1.matrix[0][0] = 1;
  m1.matrix[0][1] = 2;
  m1.matrix[0][2] = 3;

  m2.matrix[0][0] = 1;
  m2.matrix[0][1] = 2;
  m2.matrix[1][0] = 3;
  m2.matrix[1][1] = 4;
  m2.matrix[2][0] = 5;
  m2.matrix[2][1] = 6;

  double res1[1][2] = {{22, 28}};
  result = s21_mult_matrix(&m1, &m2, &m3);
  ck_assert_int_eq(result, S21_SUCCESS);
  for (int i = 0; i < 1; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq_tol(m3.matrix[i][j], res1[i][j], 1e-7);
    }
  }
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&m3);

  // Functional test 2
  s21_create_matrix(2, 2, &m1);
  s21_create_matrix(2, 3, &m2);
  m1.matrix[0][0] = 1;
  m1.matrix[0][1] = 2;
  m1.matrix[1][0] = 3;
  m1.matrix[1][1] = 1;

  m2.matrix[0][0] = 5;
  m2.matrix[0][1] = 2;
  m2.matrix[0][2] = 5;
  m2.matrix[1][0] = 2;
  m2.matrix[1][1] = 5;
  m2.matrix[1][2] = 2;

  double res2[2][3] = {{9, 12, 9}, {17, 11, 17}};

  result = s21_mult_matrix(&m1, &m2, &m3);
  ck_assert_int_eq(result, S21_SUCCESS);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(m3.matrix[i][j], res2[i][j], 1e-7);
    }
  }
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&m3);
}
END_TEST

START_TEST(s21_transpose_test) {
  int result;
  matrix_t m1, m2;

  // Default test
  s21_create_matrix(3, 3, &m1);
  result = s21_transpose(&m1, &m2);
  ck_assert_int_eq(result, S21_SUCCESS);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);

  // Incorrect test
  s21_create_matrix(3, -3, &m1);
  result = s21_transpose(&m1, &m2);
  ck_assert_int_eq(result, S21_INCORRECT);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);

  // Non-square matrix test 1
  s21_create_matrix(2, 4, &m1);
  m1.matrix[0][0] = 1;
  m1.matrix[0][1] = 2;
  m1.matrix[0][2] = 3;
  m1.matrix[0][3] = 4;
  m1.matrix[1][0] = 5;
  m1.matrix[1][1] = 6;
  m1.matrix[1][2] = 7;
  m1.matrix[1][3] = 8;
  double res1[4][2] = {
      {1, 5},
      {2, 6},
      {3, 7},
      {4, 8},
  };
  result = s21_transpose(&m1, &m2);
  ck_assert_int_eq(result, S21_SUCCESS);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq_tol(m2.matrix[i][j], res1[i][j], 1e-7);
    }
  }
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);

  //     Non-square matrix test 2
  s21_create_matrix(4, 2, &m1);
  m1.matrix[0][0] = 1;
  m1.matrix[0][1] = 2;
  m1.matrix[1][0] = 3;
  m1.matrix[1][1] = 4;
  m1.matrix[2][0] = 5;
  m1.matrix[2][1] = 6;
  m1.matrix[3][0] = 7;
  m1.matrix[3][1] = 8;
  double res2[2][4] = {{1, 3, 5, 7}, {2, 4, 6, 8}};
  result = s21_transpose(&m1, &m2);
  ck_assert_int_eq(result, S21_SUCCESS);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_double_eq_tol(m2.matrix[i][j], res2[i][j], 1e-7);
    }
  }
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(s21_determinant_test) {
  int result;
  double output;
  matrix_t m1;

  s21_create_matrix(3, 3, &m1);
  m1.matrix[0][0] = 1;
  m1.matrix[0][1] = 3;
  m1.matrix[0][2] = 2;
  m1.matrix[1][0] = 4;
  m1.matrix[1][1] = 6;
  m1.matrix[1][2] = 7;
  m1.matrix[2][0] = 3;
  m1.matrix[2][1] = 4;
  m1.matrix[2][2] = 0;

  result = s21_determinant(&m1, &output);
  ck_assert_int_eq(result, S21_SUCCESS);
  ck_assert_double_eq_tol(output, 31, 1e-4);
  s21_remove_matrix(&m1);

  s21_create_matrix(-1, 3, &m1);
  result = s21_determinant(&m1, &output);
  ck_assert_int_eq(result, S21_INCORRECT);
  s21_remove_matrix(&m1);

  s21_create_matrix(4, 3, &m1);
  result = s21_determinant(&m1, &output);
  ck_assert_int_eq(result, S21_ARTH_ERROR);
  s21_remove_matrix(&m1);

  s21_create_matrix(3, 4, &m1);
  result = s21_determinant(&m1, &output);
  ck_assert_int_eq(result, S21_ARTH_ERROR);
  s21_remove_matrix(&m1);

  // One more
  s21_create_matrix(2, 2, &m1);
  m1.matrix[0][0] = 3;
  m1.matrix[0][1] = 2;
  m1.matrix[1][0] = 7;
  m1.matrix[1][1] = -1;
  result = s21_determinant(&m1, &output);
  ck_assert_int_eq(result, S21_SUCCESS);
  ck_assert_double_eq_tol(output, -17, 1e-7);
  s21_remove_matrix(&m1);

  // One more
  s21_create_matrix(1, 1, &m1);
  m1.matrix[0][0] = 5;
  result = s21_determinant(&m1, &output);
  ck_assert_int_eq(result, S21_SUCCESS);
  ck_assert_double_eq_tol(output, 5, 1e-7);
  s21_remove_matrix(&m1);
}
END_TEST

START_TEST(s21_calc_complements_test) {
  matrix_t m1, m2;
  int result = 1;

  // Test for incorrect sizes

  // Test 1
  s21_create_matrix(0, 3, &m1);
  result = s21_calc_complements(&m1, &m2);
  ck_assert_int_eq(result, S21_INCORRECT);

  // Test 2
  s21_create_matrix(3, -1, &m1);
  result = s21_calc_complements(&m1, &m2);
  ck_assert_int_eq(result, S21_INCORRECT);

  // Test for non-square matrix

  // Test 3
  s21_create_matrix(2, 3, &m1);
  result = s21_calc_complements(&m1, &m2);
  ck_assert_int_eq(result, S21_ARTH_ERROR);
  s21_remove_matrix(&m1);

  // Test 4
  s21_create_matrix(3, 2, &m1);
  result = s21_calc_complements(&m1, &m2);
  ck_assert_int_eq(result, S21_ARTH_ERROR);
  s21_remove_matrix(&m1);

  // Functional test

  // Test 5 (3x3)
  s21_create_matrix(3, 3, &m1);
  m1.matrix[0][0] = 1;
  m1.matrix[0][1] = 2;
  m1.matrix[0][2] = 3;
  m1.matrix[1][0] = 0;
  m1.matrix[1][1] = 4;
  m1.matrix[1][2] = 2;
  m1.matrix[2][0] = 5;
  m1.matrix[2][1] = 2;
  m1.matrix[2][2] = 1;

  double res1[3][3] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};

  result = s21_calc_complements(&m1, &m2);
  ck_assert_int_eq(result, S21_SUCCESS);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(m2.matrix[i][j], res1[i][j], 1e-7);
    }
  }
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);

  //   Test 6 (2x2)
  s21_create_matrix(2, 2, &m1);
  m1.matrix[0][0] = 1;
  m1.matrix[0][1] = -5;
  m1.matrix[1][0] = 3;
  m1.matrix[1][1] = -4;

  double res2[2][2] = {{-4, -3}, {5, 1}};

  result = s21_calc_complements(&m1, &m2);
  ck_assert_int_eq(result, S21_SUCCESS);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq_tol(m2.matrix[i][j], res2[i][j], 1e-7);
    }
  }
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(s21_inverse_matrix_test) {
  matrix_t m1, m2;
  int result;

  // Test for incorrect sizes

  // Test 1
  s21_create_matrix(0, 3, &m1);
  result = s21_inverse_matrix(&m1, &m2);
  ck_assert_int_eq(result, S21_INCORRECT);

  // Test 2
  s21_create_matrix(3, -1, &m1);
  result = s21_inverse_matrix(&m1, &m2);
  ck_assert_int_eq(result, S21_INCORRECT);

  // Test for non-square matrix

  // Test 3
  s21_create_matrix(2, 3, &m1);
  result = s21_inverse_matrix(&m1, &m2);
  ck_assert_int_eq(result, S21_ARTH_ERROR);
  s21_remove_matrix(&m1);

  // Test 4
  s21_create_matrix(3, 2, &m1);
  result = s21_inverse_matrix(&m1, &m2);
  ck_assert_int_eq(result, S21_ARTH_ERROR);
  s21_remove_matrix(&m1);

  // Functional test

  // Test 5 (3x3)
  s21_create_matrix(3, 3, &m1);
  m1.matrix[0][0] = 2;
  m1.matrix[0][1] = 5;
  m1.matrix[0][2] = 7;
  m1.matrix[1][0] = 6;
  m1.matrix[1][1] = 3;
  m1.matrix[1][2] = 4;
  m1.matrix[2][0] = 5;
  m1.matrix[2][1] = -2;
  m1.matrix[2][2] = -3;

  double res1[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};

  result = s21_inverse_matrix(&m1, &m2);
  ck_assert_int_eq(result, S21_SUCCESS);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(m2.matrix[i][j], res1[i][j], 1e-7);
    }
  }
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);

  //   Test 6 (2x2)
  s21_create_matrix(2, 2, &m1);
  m1.matrix[0][0] = 1;
  m1.matrix[0][1] = 2;
  m1.matrix[1][0] = 3;
  m1.matrix[1][1] = 4;

  double res2[2][2] = {{-2, 1}, {3.0 / 2.0, -1.0 / 2.0}};

  result = s21_inverse_matrix(&m1, &m2);
  ck_assert_int_eq(result, S21_SUCCESS);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq_tol(m2.matrix[i][j], res2[i][j], 1e-7);
    }
  }

  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(is_equal_test) {
  ck_assert_int_eq(is_equal(0, 0), 1);
  ck_assert_int_eq(is_equal(0, 0.1), 0);

  ck_assert_int_eq(is_equal(2.0, 2.0), 1);
  ck_assert_int_eq(is_equal(2.0, 2.01), 0);

  ck_assert_int_eq(is_equal(3.06, 3.06), 1);
  ck_assert_int_eq(is_equal(3.06, 3.061), 0);

  ck_assert_int_eq(is_equal(18.007, 18.007), 1);
  ck_assert_int_eq(is_equal(18.007, 18.0071), 0);

  ck_assert_int_eq(is_equal(-5.0005, -5.0005), 1);
  ck_assert_int_eq(is_equal(-5.0005, -5.00051), 0);

  ck_assert_int_eq(is_equal(115.00007, 115.00007), 1);
  ck_assert_int_eq(is_equal(115.00007, 115.000071), 0);

  ck_assert_int_eq(is_equal(25.000004, 25.000004), 1);
  ck_assert_int_eq(is_equal(25.000004, 25.0000041), 0);

  ck_assert_int_eq(is_equal(14.0000001, 14.0000001), 1);
  ck_assert_int_eq(is_equal(14.0000001, 14.00000011), 1);

  ck_assert_int_eq(is_equal(54.00000008, 54.00000008), 1);
  ck_assert_int_eq(is_equal(54.00000008, 54.000000081), 1);
}
END_TEST

START_TEST(is_correct_test) {
  matrix_t m1;
  int result;

  s21_create_matrix(3, 3, &m1);
  result = is_correct(&m1);
  ck_assert_int_eq(result, S21_SUCCESS);
  s21_remove_matrix(&m1);

  s21_create_matrix(0, 3, &m1);
  result = is_correct(&m1);
  ck_assert_int_eq(result, S21_INCORRECT);

  s21_create_matrix(3, -4, &m1);
  result = is_correct(&m1);
  ck_assert_int_eq(result, S21_INCORRECT);
}
END_TEST

Suite *s21_matrix_tests_create() {
  Suite *s21_matrix = suite_create("s21_matrix");
  TCase *s21_matrix_tests = tcase_create("S21_MATRIX");

  tcase_add_test(s21_matrix_tests, s21_create_matrix_test);
  tcase_add_test(s21_matrix_tests, s21_eq_matrix_test);
  tcase_add_test(s21_matrix_tests, s21_sum_matrix_test);
  tcase_add_test(s21_matrix_tests, s21_sub_matrix_test);
  tcase_add_test(s21_matrix_tests, s21_mult_number_test);
  tcase_add_test(s21_matrix_tests, s21_mult_matrix_test);
  tcase_add_test(s21_matrix_tests, s21_transpose_test);
  tcase_add_test(s21_matrix_tests, s21_determinant_test);
  tcase_add_test(s21_matrix_tests, s21_calc_complements_test);
  tcase_add_test(s21_matrix_tests, s21_inverse_matrix_test);
  tcase_add_test(s21_matrix_tests, is_equal_test);
  tcase_add_test(s21_matrix_tests, is_correct_test);

  suite_add_tcase(s21_matrix, s21_matrix_tests);
  return s21_matrix;
}

int main() {
  Suite *s21_matrix = s21_matrix_tests_create();
  SRunner *s21_matrix_runner = srunner_create(s21_matrix);
  float number_failed;
  srunner_run_all(s21_matrix_runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(s21_matrix_runner);
  srunner_free(s21_matrix_runner);

  return number_failed == 0 ? 0 : 1;
}
