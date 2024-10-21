#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = 0;
  if (rows >= 1 && columns >= 1) {
    result->matrix = (double **)malloc(rows * columns * sizeof(double) +
                                       rows * sizeof(double *));
    double *pointer = (double *)(result->matrix + rows);
    result->rows = rows;
    result->columns = columns;
    if (result->matrix == NULL) {
      error = 1;
    } else {
      for (int i = 0; i < rows; i++) result->matrix[i] = pointer + i * columns;
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
          result->matrix[i][j] = 0;
        }
      }
    }
  } else {
    error = 1;
  }

  return error;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL && A->matrix != NULL) {
    free(A->matrix);
    A->rows = 0;
    A->columns = 0;
    A->matrix = NULL;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  int rows = A->rows, columns = A->columns;
  if (A->rows == B->rows && A->columns == B->columns) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        if (A->matrix[i][j] - B->matrix[i][j] > ACCURACY) result = FAILURE;
      }
    }
  } else {
    result = FAILURE;
  }

  return result;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  if ((conditions(A) && conditions(B)) || result != NULL) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  } else if (A->rows != B->rows || A->columns != B->columns) {
    error = 2;
  } else {
    error = 1;
  }

  return error;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  if ((conditions(A) && conditions(B)) || result != NULL) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  } else if (A->rows != B->rows || A->columns != B->columns) {
    error = 2;
  } else {
    error = 1;
  }

  return error;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = 0;
  if (conditions(A) || result != NULL) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  } else {
    error = 1;
  }

  return error;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  if ((conditions(A) && conditions(B)) || result != NULL) {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  } else if (A->rows != B->columns || A->columns != B->rows) {
    error = 2;
  } else {
    error = 1;
  }

  return error;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (conditions(A) || result != NULL) {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  } else {
    error = 1;
  }

  return error;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (conditions(A) || result != NULL) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        matrix_t temp;
        s21_minor(i, j, A, &temp);
        double number = 0;
        s21_determinant(&temp, &number);
        result->matrix[i][j] = pow(-1, i + j) * number;
        s21_remove_matrix(&temp);
      }
    }
  } else if (A->rows != A->columns) {
    error = 2;
  } else {
    error = 1;
  }

  return error;
}

int s21_minor(int row, int column, matrix_t *A, matrix_t *result) {
  int error = 0;
  if (conditions(A) || result != NULL) {
    s21_create_matrix(A->rows - 1, A->columns - 1, result);
    for (int line_horizontal = 0, i = 0; line_horizontal < result->rows;
         i++, line_horizontal++) {
      if (i == row) i++;
      for (int line_vertical = 0, j = 0; line_vertical < result->columns;
           j++, line_vertical++) {
        if (j == column) j++;
        result->matrix[line_horizontal][line_vertical] = A->matrix[i][j];
      }
    }
  } else {
    error = 1;
  }

  return error;
}

int s21_determinant(matrix_t *A, double *result) {
  int error = 0;
  if (conditions(A) || result != NULL) {
    *result = 0;
    switch (A->rows) {
      case 1:
        *result = A->matrix[0][0];
        break;
      case 2:
        *result += A->matrix[0][0] * A->matrix[1][1] -
                   A->matrix[0][1] * A->matrix[1][0];
        break;
      default:
        for (int i = 0; i < A->columns; i++) {
          matrix_t temp;
          double number = 0;
          s21_minor(0, i, A, &temp);
          error = s21_determinant(&temp, &number);
          *result += pow(-1, i) * A->matrix[0][i] * number;
          s21_remove_matrix(&temp);
        }
        break;
    }
  } else if (A->rows != A->columns) {
    error = 2;
  } else {
    error = 1;
  }

  return error;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (conditions(A) || result != NULL) {
    double determinant = 0;
    s21_determinant(A, &determinant);
    if (fabs(determinant) < 10e-12) {
      error = 2;
    } else if (A->rows == 1) {
      s21_create_matrix(A->rows, A->columns, result);
      result->matrix[0][0] = 1.0 / A->matrix[0][0];
    } else {
      matrix_t complements, transpose;
      s21_calc_complements(A, &complements);
      s21_transpose(&complements, &transpose);
      s21_mult_number(&transpose, 1 / determinant, result);
      s21_remove_matrix(&complements);
      s21_remove_matrix(&transpose);
    }
  } else if (A->rows != A->columns) {
    error = 2;
  } else {
    error = 1;
  }

  return error;
}

int conditions(matrix_t *A) {
  int error = 0;
  if (A == NULL)
    error = 1;
  else if (A->rows < 1 || A->columns < 1 || A->matrix == NULL)
    error = 1;

  return error;
}

void s21_numb_matrix(double numb, matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = numb;
      numb += 1.0;
    }
  }
}