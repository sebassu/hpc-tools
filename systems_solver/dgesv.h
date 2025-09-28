const double EPSILON = 1e-5;

int my_dgesv(int n, int nrhs, double *a, double *b);
int find_pivot_row(double *matrix, int n, int current_column);
void swap_rows(int row1, int row2, double *matrix, double *rhs, int n, int nrhs);
void normalize_pivot_row(double *matrix, double *rhs, int n, int nrhs, int pivot);
void eliminate_column(double *matrix, double *rhs, int n, int nrhs, int pivot);
