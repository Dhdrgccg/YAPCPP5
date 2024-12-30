#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

// Функция для заполнения файла случайными числами
void fillFileWithRandomNumbers(const std::string& filename, int count, int minVal, int maxVal) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка открытия файла для записи!" << std::endl;
        return;
    }

    std::srand(std::time(nullptr)); // Инициализация генератора случайных чисел

    for (int i = 0; i < count; ++i) {
        int randomNum = minVal + std::rand() % (maxVal - minVal + 1);
        outFile << randomNum << std::endl;
    }

    outFile.close();
}

// Функция для чтения чисел из файла и вычисления разности
int findDifference(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Ошибка открытия файла для чтения!" << std::endl;
        return 0;
    }

    int num;
    int maxNum = std::numeric_limits<int>::min();
    int minNum = std::numeric_limits<int>::max();

    while (inFile >> num) {
        if (num > maxNum) maxNum = num;
        if (num < minNum) minNum = num;
    }

    inFile.close();
    return maxNum - minNum;
}

int no4() {
    setlocale(LC_ALL, "Russian");

    const std::string filename = "numbers.txt";
    int coun;       // Количество случайных чисел
    int minVal;    // Минимальное значение
    int maxVal;     // Максимальное значение

    std::cout << "Введите кол-во чисел: ";
    while (!(std::cin >> coun)) {
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
    fillFileWithRandomNumbers(filename, coun, minVal, maxVal);

    // Вычисление разности максимального и минимального элементов
    int difference = findDifference(filename);
    std::cout << "Разность максимального и минимального элементов: " << difference << std::endl;

    return 0;
}
