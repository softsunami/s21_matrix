#ifndef SRC_S21_MATRIX_H
#define SRC_S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define S21_SUCCESS 0
#define S21_INCORRECT 1
#define S21_ARTH_ERROR 2

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// Help
int is_equal(double num1, double num2);  // Well
int is_correct(matrix_t *m1);            // Well
void print_matrix(matrix_t m1);          // Well
double det_square(matrix_t m1);          // Well
matrix_t matrix_minor(matrix_t m1, int a, int b);

// Main
int s21_create_matrix(int rows, int columns, matrix_t *result);     // Well
void s21_remove_matrix(matrix_t *A);                                // Well
int s21_eq_matrix(matrix_t *A, matrix_t *B);                        // Well
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);     // Well
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);     // Well
int s21_mult_number(matrix_t *A, double number, matrix_t *result);  // Well
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);    // Well
int s21_transpose(matrix_t *A, matrix_t *result);                   // Well
int s21_determinant(matrix_t *A, double *result);                   // Well
int s21_calc_complements(matrix_t *A, matrix_t *result);            // Well
int s21_inverse_matrix(matrix_t *A, matrix_t *result);              // Well

#endif  // SRC_S21_MATRIX_H
