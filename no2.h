#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

// Функция для заполнения бинарного файла случайными числами
void fillBinaryFile(const string& filename, int count, int minValue, int maxValue) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "Ошибка при открытии файла для записи!" << endl;
        return;
    }

    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < count; ++i) {
        int randomValue = minValue + rand() % (maxValue - minValue + 1);
        outFile.write(reinterpret_cast<const char*>(&randomValue), sizeof(int));
    }

    outFile.close();
    cout << "Файл \"" << filename << "\" успешно заполнен случайными числами." << endl;
}

// Функция для чтения данных из бинарного файла
vector<int> readBinaryFile(const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "Ошибка при открытии файла для чтения!" << endl;
        return {};
    }

    vector<int> data;
    int value;
    while (inFile.read(reinterpret_cast<char*>(&value), sizeof(int))) {
        data.push_back(value);
    }

    inFile.close();
    return data;
}

// Функция для копирования данных в матрицу размером n×n
vector<vector<int>> fillMatrix(const vector<int>& data, int n) {
    vector<vector<int>> matrix(n, vector<int>(n, 0)); // Заполняем нулями
    int index = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (index < data.size()) {
                matrix[i][j] = data[index++];
            }
        }
    }

    return matrix;
}

// Функция для замены элементов строк на минимальный элемент строки
void replaceRowElementsWithMin(vector<vector<int>>& matrix) {
    for (auto& row : matrix) {
        int minElement = *min_element(row.begin(), row.end());
        fill(row.begin(), row.end(), minElement);
    }
}

// Функция для вывода матрицы
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}

int no2() {
    setlocale(LC_ALL, "Russian");

    const string filename = "source2.bin";
    double coun;  // Количество случайных чисел для заполнения файла
    int minValue;
    int maxValue;
    int n;       // Размер матрицы n×n

    cout << "Введите кол-во чисел в файле: ";
    while (!(cin >> coun)) {
        cin.ignore();
        cin.clear();
        cout << "Ошибка ввода.";
        return 0;
    }

    cout << "Введите минимальное значение: ";
    while (!(cin >> minValue)) {
        cin.ignore();
        cin.clear();
        cout << "Ошибка ввода.";
        return 0;
    }

    cout << "Введите максимальное значение: ";
    while (!(cin >> maxValue)) {
        cin.ignore();
        cin.clear();
        cout << "Ошибка ввода.";
        return 0;
    }

    if (maxValue < minValue) {
        cout << "Ошибка ввода.";
        return 0;
    }

    n = int(pow(coun, 0.5)) + 1;

    // Заполняем бинарный файл случайными числами
    fillBinaryFile(filename, coun, minValue, maxValue);

    // Читаем данные из файла
    vector<int> data = readBinaryFile(filename);

    // Копируем данные в квадратную матрицу размером n×n
    vector<vector<int>> matrix = fillMatrix(data, n);

    cout << "Исходная матрица:" << endl;
    printMatrix(matrix);

    // Заменяем элементы строк на минимальный элемент строки
    replaceRowElementsWithMin(matrix);

    cout << "Матрица после обработки:" << endl;
    printMatrix(matrix);

    return 0;
}
