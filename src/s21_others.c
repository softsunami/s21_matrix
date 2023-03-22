#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int flag = S21_SUCCESS;

  if (is_correct(A) != S21_SUCCESS) {
    flag = S21_INCORRECT;
  }

  if (flag == S21_SUCCESS) {
    if (s21_create_matrix(A->columns, A->rows, result) != S21_SUCCESS) {
      flag = S21_INCORRECT;
    }
  }

  if (flag == S21_SUCCESS) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }

  return flag;
}

double det_square(matrix_t m1) {
  double result = 0;

  if (m1.rows == m1.columns) {
    result =
        m1.matrix[0][0] * m1.matrix[1][1] - m1.matrix[0][1] * m1.matrix[1][0];
  } else {
    result = NAN;
  }

  return result;
}

matrix_t matrix_minor(matrix_t m1, int a, int b) {
  int flag = S21_SUCCESS;
  matrix_t result = {0};
  a--;
  b--;

  if (a < 0 || b < 0 || a >= m1.rows || b >= m1.columns ||
      m1.rows != m1.columns) {
    flag = S21_INCORRECT;
  }

  if (flag == S21_SUCCESS) {
    s21_create_matrix(m1.rows - 1, m1.columns - 1, &result);
    for (int i = 0, i_res = 0; i < m1.rows; i++) {
      if (i == a) continue;
      for (int j = 0, j_res = 0; j < m1.rows; j++) {
        if (j == b) continue;
        result.matrix[i_res][j_res] = m1.matrix[i][j];
        j_res++;
      }
      i_res++;
    }
  }
  return result;
}

int s21_determinant(matrix_t *A, double *result) {
  int flag = S21_SUCCESS;
  if (is_correct(A) != S21_SUCCESS) {
    flag = S21_INCORRECT;
  }

  if (A->columns != A->rows) {
    flag = S21_ARTH_ERROR;
  }

  if (flag == S21_SUCCESS) {
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows == 2) {
      *result = det_square(*A);
    } else {
      double determinant = 0;
      int minus_flag = 1;
      matrix_t minored_matrix;
      double ratio = 0;
      for (int i = 0; i < A->rows; i++) {
        ratio = A->matrix[0][i];
        minored_matrix = matrix_minor(*A, 1, i + 1);
        *result += s21_determinant(&minored_matrix, result);
        *result = *result * ratio * minus_flag;
        determinant += *result;
        minus_flag = -minus_flag;

        s21_remove_matrix(&minored_matrix);
      }
      *result = determinant;
    }
  }

  return flag;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int flag = S21_SUCCESS;

  if (is_correct(A) != S21_SUCCESS) {
    flag = S21_INCORRECT;
  }
  if (A->rows != A->columns) {
    flag = S21_ARTH_ERROR;
  }
  if (flag == S21_SUCCESS) {
    if (s21_create_matrix(A->rows, A->columns, result) != S21_SUCCESS) {
      flag = S21_INCORRECT;
    }
  }
  if (flag == S21_SUCCESS) {
    matrix_t temp;
    double elem = 0;
    for (int i = 1; i < A->rows + 1; i++) {
      for (int j = 1; j < A->columns + 1; j++) {
        temp = matrix_minor(*A, i, j);
        s21_determinant(&temp, &elem);
        result->matrix[i - 1][j - 1] = elem;
        s21_remove_matrix(&temp);
      }
    }

    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] *= pow(-1, i + j);
      }
    }
  }
  return flag;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int flag = S21_SUCCESS;

  if (is_correct(A) != S21_SUCCESS) {
    flag = S21_INCORRECT;
  }

  if (A->rows != A->columns) {
    flag = S21_ARTH_ERROR;
  }
  double det = 0;
  if (flag == S21_SUCCESS) {
    s21_determinant(A, &det);
    if (det == 0) {
      flag = S21_ARTH_ERROR;
    }
  }

  if (flag == S21_SUCCESS) {
    if (s21_create_matrix(A->rows, A->columns, result) != S21_SUCCESS) {
      flag = S21_SUCCESS;
    }
  }
  matrix_t temp1, temp2;

  if (flag == S21_SUCCESS) {
    flag = s21_calc_complements(A, &temp1);
  }

  if (flag == S21_SUCCESS) {
    flag = s21_transpose(&temp1, &temp2);
    s21_remove_matrix(&temp1);
  }

  if (flag == S21_SUCCESS) {
    s21_remove_matrix(result);
    flag = s21_mult_number(&temp2, 1.0 / det, result);
    s21_remove_matrix(&temp2);
  }

  return flag;
}