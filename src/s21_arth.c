#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int flag = 1;
  if (A->rows != B->rows || A->columns != B->columns) {
    flag = 0;
  }

  if (is_correct(A) != S21_SUCCESS || is_correct(B) != S21_SUCCESS) {
    flag = 0;
  }

  if (flag == 1) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (is_equal(A->matrix[i][j], B->matrix[i][j]) == 0) {
          flag = 0;
          break;
        }
      }
    }
  }
  return flag;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = S21_SUCCESS;

  if (is_correct(A) != S21_SUCCESS || is_correct(B) != S21_SUCCESS) {
    flag = S21_INCORRECT;
  }

  if (flag == S21_SUCCESS) {
    if (A->rows != B->rows && A->columns != B->columns) {
      flag = S21_ARTH_ERROR;
    }
  }

  if (flag == S21_SUCCESS) {
    if (s21_create_matrix(A->rows, A->columns, result) != S21_SUCCESS) {
      flag = S21_INCORRECT;
    }
  }

  if (flag == S21_SUCCESS) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }

  return flag;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = S21_SUCCESS;

  if (is_correct(A) != S21_SUCCESS || is_correct(B) != S21_SUCCESS) {
    flag = S21_INCORRECT;
  }

  if (flag == S21_SUCCESS) {
    if (A->rows != B->rows && A->columns != B->columns) {
      flag = S21_ARTH_ERROR;
    }
  }

  if (flag == S21_SUCCESS) {
    if (s21_create_matrix(A->rows, A->columns, result) != S21_SUCCESS) {
      flag = S21_INCORRECT;
    }
  }

  if (flag == S21_SUCCESS) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }

  return flag;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int flag = S21_SUCCESS;

  if (is_correct(A) != S21_SUCCESS) {
    flag = S21_INCORRECT;
  }

  if (flag == S21_SUCCESS) {
    if (s21_create_matrix(A->rows, A->columns, result) != S21_SUCCESS) {
      flag = S21_INCORRECT;
    }
  }

  if (flag == S21_SUCCESS) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = number * A->matrix[i][j];
      }
    }
  }

  return flag;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = S21_SUCCESS;

  if (is_correct(A) != S21_SUCCESS || is_correct(B) != S21_SUCCESS) {
    flag = S21_INCORRECT;
  }

  if (flag == S21_SUCCESS) {
    if (A->columns != B->rows) {
      flag = S21_ARTH_ERROR;
    }
  }

  if (flag == S21_SUCCESS) {
    if (s21_create_matrix(A->rows, B->columns, result) != S21_SUCCESS) {
      flag = S21_INCORRECT;
    }
  }

  double temp = 0;

  if (flag == S21_SUCCESS) {
    for (int a = 0; a < A->rows; a++) {
      for (int b = 0; b < B->columns; b++) {
        for (int c = 0; c < B->rows; c++) {
          temp += A->matrix[a][c] * B->matrix[c][b];
        }
        result->matrix[a][b] = temp;
        temp = 0;
      }
    }
  }

  return flag;
}