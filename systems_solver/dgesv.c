#include "dgesv.h"

int my_dgesv(int n, int nrhs, double *a, double *b)
{
  for (int current = 0; current < n; current += 1)
  {
    int pivot_row = find_pivot_row(a, n, current);
    if (fabs(a[current * n + pivot_row]) < EPSILON)
      return current + 1;
    if (pivot_row != current)
      swap_rows(current, pivot_row, a, b, n, nrhs);
    normalize_pivot_row(a, b, n, nrhs, current);
    eliminate_column(a, b, n, nrhs, current);
  }
  return 0;
}

int find_pivot_row(double *matrix, int n, int position)
{
  int pivot = position;
  double maximum = fabs(matrix[position * n + position]);
  for (int row = position + 1; row < n; row += 1)
  {
    double value = fabs(matrix[position * n + row]);
    if (value > maximum)
    {
      maximum = value;
      pivot = row;
    }
  }
  return pivot;
}

void swap_rows(int row1, int row2, double *matrix, double *rhs, int n, int nrhs)
{
  for (int column = 0; column < n; column += 1)
  {
    double aux = matrix[column * n + row1];
    matrix[column * n + row1] = matrix[column * n + row2];
    matrix[column * n + row2] = aux;
  }

  for (int rhs_column = 0; rhs_column < nrhs; rhs_column += 1)
  {
    double aux = rhs[rhs_column * n + row1];
    rhs[rhs_column * n + row1] = rhs[rhs_column * n + row2];
    rhs[rhs_column * n + row2] = aux;
  }
}

void normalize_pivot_row(double *matrix, double *rhs, int n, int nrhs, int pivot)
{
  double pivot_element = matrix[pivot * n + pivot];
  for (int column = pivot; column < n; column += 1)
    matrix[column * n + pivot] /= pivot_element;
  for (int rhs_column = 0; rhs_column < nrhs; rhs_column += 1)
    rhs[rhs_column * n + pivot] /= pivot_element;
}

void eliminate_column(double *matrix, double *rhs, int n, int nrhs, int pivot)
{
  for (int row = 0; row < n; row += 1)
  {
    if (row == pivot)
      continue;
    double factor = matrix[pivot * n + row];
    for (int column = pivot; column < n; column += 1)
      matrix[column * n + row] -= factor * matrix[column * n + pivot];
    for (int rhs_column = 0; rhs_column < nrhs; rhs_column += 1)
      rhs[rhs_column * n + row] -= factor * rhs[rhs_column * n + pivot];
  }
}
