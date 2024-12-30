#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <sstream>

// Функция для заполнения файла случайными числами
void fillFileWithRandomNumbers(const std::string& filename, int rows, int numbersPerRow, int minVal, int maxVal) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка открытия файла для записи!" << std::endl;
        return;
    }

    std::srand(std::time(nullptr)); // Инициализация генератора случайных чисел

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < numbersPerRow; ++j) {
            int randomNum = minVal + std::rand() % (maxVal - minVal + 1);
            outFile << randomNum;
            if (j < numbersPerRow - 1) outFile << " "; // Разделение чисел пробелами
        }
        outFile << std::endl; // Переход на новую строку
    }

    outFile.close();
}

// Функция для вычисления минимального элемента
int findMinimum(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Ошибка открытия файла для чтения!" << std::endl;
        return 0;
    }

    int minNum = std::numeric_limits<int>::max();
    std::string line;

    // Чтение файла построчно
    while (std::getline(inFile, line)) {
        std::istringstream lineStream(line); // Поток для работы с отдельной строкой
        int num;

        while (lineStream >> num) { // Чтение чисел из строки
            if (num < minNum) minNum = num;
        }
    }

    inFile.close();
    return minNum;
}

int no5() {
    setlocale(LC_ALL, "Russian");

    const std::string filename = "numbers2.txt";
    int rows;         // Количество строк
    int numbersPerRow;    // Количество чисел в строке
    int minVal;       // Минимальное значение
    int maxVal;        // Максимальное значение

    std::cout << "Введите кол-во строк: ";
    while (!(std::cin >> rows)) {
        std::cin.ignore();
        std::cin.clear();
        cout << "Ошибка ввода.";
        return 0;
    }

    std::cout << "Введите кол-во чисел в строке: ";
    while (!(std::cin >> numbersPerRow)) {
        std::cin.ignore();
        std::cin.clear();
        cout << "Ошибка ввода.";
        return 0;
    }

    std::cout << "Введите минимальное значение: ";
    while (!(std::cin >> minVal)) {
        std::cin.ignore();
        std::cin.clear();
        cout << "Ошибка ввода.";
        return 0;
    }

    std::cout << "Введите максимальное значение: ";
    while (!(std::cin >> maxVal)) {
        std::cin.ignore();
        std::cin.clear();
        cout << "Ошибка ввода.";
        return 0;
    }

    if (maxVal < minVal) {
        std::cout << "Ошибка ввода.";
        return 0;
    }


    // Заполнение файла случайными числами
    fillFileWithRandomNumbers(filename, rows, numbersPerRow, minVal, maxVal);

    // Вычисление минимального элемента
    int minElement = findMinimum(filename);
    std::cout << "Минимальный элемент: " << minElement << std::endl;

    return 0;
}
