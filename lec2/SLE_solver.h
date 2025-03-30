/**
 * @file SLE_solver.h
 * @author Vyacheslav
 * @version 0.1
 * @brief Вроде как рабочая программа по решению СЛАУ методом Гаусса. Бонусом функция ищующая определитель. Потом нуждо будет до конца обработать случай когда система несовместна.
 * @date 2025-03-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once
#include <vector>
#include <iostream>

/**
 * @brief Решатель систем линейных алгебраических уравнений
 *
 * @param M Квадратная матрица (NxN) известных коэффициентов
 * @param D Вектор-столбец (N) свободных коэфициентов
 * @return std::vector<double> - вектор-столбец корней
 */
std::vector<double> SLE_Solver(std::vector<std::vector<double>> M, std::vector<double> D);

double det(std::vector<std::vector<double>> M);
