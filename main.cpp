#include <iostream>

void print_matrix(double **&mat, int n_rows, int n_cols)
{
  for (int i = 0; i < n_rows; i++)
  {
    for (int j = 0; j < n_cols; j++)
    {
      std::cout << mat[i][j] << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

void delete_matrix_from_memory(double **&mat, int n_rows, int n_cols)
{
  for (int i = 0; i < n_rows; i++)
  {
    delete[] mat[i];
  }
  delete[] mat;
}

void populate_matrix(double **&mat, int n_rows, int n_cols)
{
  std::cout << "\n";
  std::cout << "Enter values one row at a time, separated by space " << std::endl;
  for (int i = 0; i < n_rows; i++)
  {
    for (int j = 0; j < n_cols; j++)
    {
      std::cin >> mat[i][j];
    }
  }
}

void allocate_matrix_memory(double **&mat, int n_rows, int n_cols)
{
  // Allocate rows
  mat = new double *[n_rows];

  // Allocate columns for rows
  for (int i = 0; i < n_rows; i++)
  {
    mat[i] = new double[n_cols];
  }
}

void set_matrix_dimensions(int &n_rows, int &n_cols)
{
  std::cout << "Number of rows: ";
  std::cin >> n_rows;
  std::cout << "Number of columns: ";
  std::cin >> n_cols;
}

void get_n_column(double **mat, double col[], int col_num, int size)
{
  for (int i = 0; i < size; i++)
  {
    col[i] = mat[i][col_num];
  }
}

double get_vector_dot_product(double vec_a[], double vec_b[], int size)
{
  int product = 0;
  for (int i = 0; i < size; i++)
  {
    product += vec_a[i] * vec_b[i];
  }
  return product;
}

void calculate_dot_product(double **&mat_a, int a_rows, int a_cols,
                           double **&mat_b, int b_rows, int b_cols,
                           double **&result_matrix)
{

  // Allocate memory for the result matrix
  allocate_matrix_memory(result_matrix, a_rows, b_cols);

  // Two vectors, first horizontal, second vertical
  if (a_rows == 1 && b_cols == 1)
  {
    double b_col[b_rows];
    get_n_column(mat_b, b_col, 0, b_rows);
    result_matrix[0][0] = get_vector_dot_product(mat_a[0], b_col, b_rows);
    return;
  }

  // Two vectors, first vertical, second horizontal
  if (a_cols == 1 && b_rows == 1)
  {
    double a_column[a_rows];
    get_n_column(mat_a, a_column, 0, a_rows);

    for (int i = 0; i < a_rows; i++)
    {
      for (int j = 0; j < b_cols; j++)
      {
        double curr_b_value = mat_b[0][j];
        result_matrix[i][j] = a_column[i] * curr_b_value;
      }
    }
    return;
  }

  // Two matrices, m x n and n x p, where m and p > 1
  for (int i = 0; i < a_rows; i++)
  {
    for (int j = 0; j < b_cols; j++)
    {
      double curr_b_col[a_rows];
      get_n_column(mat_b, curr_b_col, j, a_rows);
      result_matrix[i][j] = get_vector_dot_product(mat_a[i], curr_b_col, a_rows);
    }
  }
}

void element_wise_product(double **&mat_a, int a_rows, int a_cols,
                          double **&mat_b, int b_rows, int b_cols,
                          double **&result_matrix)
{
  for (int i = 0; i < a_rows; i++)
  {
    for (int j = 0; j < b_cols; j++)
    {
      result_matrix[i][j] = mat_a[i][j] * mat_b[i][j];
    }
  }
}

void set_up_matrix(double **&matrix, int n_rows, int n_cols)
{
  allocate_matrix_memory(matrix, n_rows, n_cols);
  populate_matrix(matrix, n_rows, n_cols);
  // print_matrix(matrix, n_rows, n_cols);
}

int main(int argc, char const *argv[])
{

  bool keep_alive = true;

  while (keep_alive)
  {

    int a_rows, a_columns, b_rows, b_columns;

    double **mat_a;
    double **mat_b;
    double **mat_result;

    std::cout << "\nEnter values for matrix A" << std::endl;
    set_matrix_dimensions(a_rows, a_columns);
    set_up_matrix(mat_a, a_rows, a_columns);

    std::cout
        << "\nEnter values for matrix B" << std::endl;
    set_matrix_dimensions(b_rows, b_columns);
    set_up_matrix(mat_b, b_rows, b_columns);

    std::cout << "\n";

    std::cout << "Select functionality" << std::endl;
    std::cout << "1. Dot product\n2. Element-wise product" << std::endl;

    int choice;
    std::cin >> choice;

    switch (choice)
    {
    case 1:

      // Must be m x n and n x p
      if (a_rows != b_columns)
      {
        std::cout << "\nInvalid dimensions" << std::endl;
        return -1;
      }

      // Allocate memory for the result and calculate the results
      allocate_matrix_memory(mat_result, a_rows, b_columns);
      calculate_dot_product(mat_a, a_rows, a_columns, mat_b, b_rows, b_columns, mat_result);

      std::cout << "\nDot product:" << std::endl;
      print_matrix(mat_result, a_rows, b_columns);

      // Release memory
      delete_matrix_from_memory(mat_a, a_rows, a_columns);
      delete_matrix_from_memory(mat_b, b_rows, b_columns);
      delete_matrix_from_memory(mat_result, a_rows, b_columns);

      break;

    case 2:
      // Must be equal
      if (a_rows != b_rows || a_columns != b_columns)
      {
        std::cout << "\nInvalid dimensions, must be equal size" << std::endl;
        return -1;
      }

      // Allocate memory for the result and calculate the results
      allocate_matrix_memory(mat_result, a_rows, b_columns);
      element_wise_product(mat_a, a_rows, a_columns, mat_b, b_rows, b_columns, mat_result);

      std::cout << "\nElement-wise product:" << std::endl;
      print_matrix(mat_result, a_rows, b_columns);

      // Release memory
      delete_matrix_from_memory(mat_a, a_rows, a_columns);
      delete_matrix_from_memory(mat_b, b_rows, b_columns);
      delete_matrix_from_memory(mat_result, a_rows, b_columns);

      break;

    default:
      break;
    }

    std::string cmd;
    std::cout << "Continue with any key or quit with q" << std::endl;

    std::cin >> cmd;

    for (auto c : cmd)
      c = tolower(c);

    if (cmd == "q")
      return 0;
  }

  return 0;
}
