#include <iostream>
#include <vector>
#include <cmath>
#include <stdio.h>
std::ostream &operator<<(std::ostream &os, const std::vector<double> &res)
{
    for (int i = 0; i < res.size(); i++)
    {
        os << "Root[" << i << "] = " << res[i] << '\n';
    }
    os << '\n';
    return os;
}

void multiply_row(std::vector<double> &row, double coef)
{
    for (int i = 0; i < row.size(); i++)
    {
        row[i] *= coef;
    }
}

void print_row(const std::vector<double> &r)
{
    for (auto x : r)
    {
        std::cout << x << '\t';
    }
    std::cout << '\n';
}

void subtract_rows(std::vector<double> &r1, std::vector<double> &r2)
{
    for (int i = 0; i < r1.size(); i++)
    {
        r1[i] = r1[i] - r2[i];
    }
}

bool check_gaussian(std::vector<std::vector<double>> &matrix, std::vector<double> &solution)
{
    bool is_ok = true;
}

std::vector<double> gaussian_method(std::vector<std::vector<double>> matrix)
{
    int col_size = matrix.size();
    int row_size = matrix[0].size();

    std::cout << "Input matrix:\n";
    for (std::vector<double> row : matrix)
    {
        for (int i = 0; i < row.size(); i++)
        {
            if (i == row.size() - 1)
            {
                std::cout << "|\t";
            }
            std::cout << row[i] << '\t';
        }
        std::cout << '\n';
    }
    std::vector<double> result(col_size, 0.0);
    if (row_size - col_size != 1)
    {
        throw std::runtime_error{"Size error"};
    }

    // std::cout << "Straight move\n";

    /*
    i - перемещение по горизонали
    j - перемещение по вертикали
     */

    for (int i = 0; i < row_size - 1; i++)
    {
        for (int j = i + 1; j < col_size; j++)
        {
            if (matrix[i][i] == 0)
            {
                std::swap(matrix[i], matrix[0 + std::rand() % (col_size + 1)]);
                i = 0;
                j = i + 1;
                std::cout << "Input matrix:\n";
                for (std::vector<double> row : matrix)
                {
                    for (int i = 0; i < row.size(); i++)
                    {
                        if (i == row.size() - 1)
                        {
                            std::cout << "|\t";
                        }
                        std::cout << row[i] << '\t';
                    }
                    std::cout << '\n';
                }
                break;
            }
            double coefficient = matrix[j][i] / matrix[i][i];

            int row_to_multiply = i;

            multiply_row(matrix[row_to_multiply], coefficient);
#ifdef DEBUG
            std::cout << "Matrix after multyplying row " << row_to_multiply << " by " << coefficient << '\n';
            for (std::vector<double> row : matrix)
            {
                for (double el : row)
                {
                    std::cout << el << '\t';
                }
                std::cout << '\n';
            }
            system("pause");
#endif
            int minuend = j;
            int subtrahend = i;
            subtract_rows(matrix[minuend], matrix[subtrahend]);
#ifdef DEBUG
            std::cout << "Matrix after subtracting row " << subtrahend << " from " << minuend << '\n';
            for (std::vector<double> row : matrix)
            {
                for (double el : row)
                {
                    std::cout << el << '\t';
                }
                std::cout << '\n';
            }
            system("pause");
#endif
        }
    }
    // std::cout << "Straight move matrix:\n";
    // for (std::vector<double> row : matrix)
    // {
    //     for (double el : row)
    //     {
    //         std::cout << el << '\t';
    //     }
    //     std::cout << '\n';
    // }

    result[col_size - 1] = matrix[col_size - 1][row_size - 1] / matrix[col_size - 1][col_size - 1];
    // std::cout << result[col_size - 1] << '\n';
    for (int i = col_size - 2; i >= 0; i--)
    {

        double free = matrix[i][row_size - 1];

        for (int j = i + 1; j < col_size; j++)
        {
            free -= matrix[i][j] * result[j];
        }

        result[i] = free / matrix[i][i];
    }

    return result;
}

int main()
{
    std::vector<std::vector<double>> G;
    int order = 12;
    for (int i = 0; i < order; i++)
    {
        for (int i = 0; i < order; i++)
        {
        }
    }

    std::vector<double> res = gaussian_method(G);
    std::cout << "Solution of system: \n";
    std::cout << res;

    return 0;
}