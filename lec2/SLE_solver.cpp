

#include "SLE_solver.h"
#include "../helpers/print_helper.h"
#include "stdio.h"
#include <limits>
#include <cmath>
void multyply_row_by_number(std::vector<double> &row, double num)
{
    for (auto &x : row)
    {
        x *= num;
    }
}

void add_rows(std::vector<double> &row1, const std::vector<double> &row2)
{
    for (int i = 0; i < row1.size(); i++)
    {
        row1[i] += row2[i];
    }
}

void subtract_rows(std::vector<double> &row1, const std::vector<double> &row2)
{
    for (int i = 0; i < row1.size(); i++)
    {
        row1[i] -= row2[i];
    }
}

void print_system(const std::vector<std::vector<double>> &M, const std::vector<double> &D)
{
    for (int k = 0; k < M.size(); k++)
    {
        for (int c = 0; c < M[k].size(); c++)
        {
            std::cout << M[k][c] << '\t';
        }
        std::cout << D[k];
        std::cout << '\n';
    }
    std::cout << '\n';
}

/**
 * @brief Нахождение максимального элемента в колонке
 *
 * @param M Матрица
 * @param col Номер колоки для поиска
 * @param skip_row Пропускаемый ряд
 * @return int - номер ряда с максимальным элементом
 */
int find_max_in_col(const std::vector<std::vector<double>> &M, int col, int skip_row)
{
    double max = -std::numeric_limits<double>::max();
    int index = -1;
    for (int i = 0; i < M.size(); i++)
    {
        // std::cout << M[i][col] << '\n';
        if (i == skip_row)
        {
            continue;
        }
        if (fabs(M[i][col]) >= max)
        {
            std::cout << M[i][col] << '\n';
            max = M[i][col];
            index = i;
        }
    }
    return index;
}

void forward_move(std::vector<std::vector<double>> &M, std::vector<double> &D)
{

    for (int j = 0; j < M.size(); j++)
    {
        if (M[j][j] == 0)
        {
            int index = find_max_in_col(M, j, j);
            std::swap(M[index], M[j]);
            std::swap(D[index], D[j]);
        }
        for (int i = j + 1; i < M.size(); i++)
        {
            double ratio = M[i][j] / M[j][j];
            auto row = M[j];
            multyply_row_by_number(row, ratio);
            subtract_rows(M[i], row);
            double dj = D[j];
            dj *= ratio;
            D[i] -= dj;
        }
    }

    // std::cout << "System after forward mowe\n";
    // print_system(M, D);
}

void backward_move(std::vector<std::vector<double>> &M, std::vector<double> &D, std::vector<double> &solution)
{
    int N = D.size();
    solution[N - 1] = D[N - 1] / M[N - 1][N - 1];

    for (int i = N - 2; i >= 0; i--)
    {
        double free = D[i];
        for (int j = i + 1; j < N; j++)
        {
            free -= M[i][j] * solution[j];
        }
        solution[i] = free / M[i][i];
        // std::cout << '\n';
    }
}

std::vector<double> SLE_Solver(std::vector<std::vector<double>> M, std::vector<double> D)
{
    if (M.size() != D.size())
    {
        throw std::invalid_argument{"Размеры матрицы коэффициентов и столбца свободных членов не совпадают."};
    }
    forward_move(M, D);
    int N = M.size();
    std::vector<double> solution(N, 0);
    backward_move(M, D, solution);
    return solution;
}

double det(std::vector<std::vector<double>> M)
{
    if (M.size() != M[0].size())
    {
        throw std::invalid_argument{"Определитель может быть посчитан только для квадратной матрицы"};
    }

    std::vector<double> placeholder(M.size(), 0); // Лень писать новую функцию (мб потом)
    forward_move(M, placeholder);

    double determinant = 1;
    for (int i = 0; i < M.size(); i++)
    {
        determinant *= M[i][i];
    }
    return determinant;
}