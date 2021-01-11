#pragma once

#include <iostream>

void print_matrix(double **&mat, int n_rows, int n_cols);
void delete_matrix_from_memory(double **&mat, int n_rows, int n_cols);
void populate_matrix(double **&mat, int n_rows, int n_cols);
void allocate_matrix_memory(double **&mat, int n_rows, int n_cols);
void set_matrix_dimensions(int &n_rows, int &n_cols);

void calculate_dot_product(double **&mat_a, int a_rows, int a_cols,
                           double **&mat_b, int b_rows, int b_cols,
                           double **&result_matrix);

void element_wise_product(double **&mat_a, int a_rows, int a_cols,
                          double **&mat_b, int b_rows, int b_cols,
                          double **&result_matrix);

void set_up_matrix(double **&matrix, int n_rows, int n_cols);