#include "mat_math.h"
#include <iostream>

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
