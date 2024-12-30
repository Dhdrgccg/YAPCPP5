#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Метод для заполнения файла случайными числами
void fillFileWithRandomData(const string& filename, int size, int minVal, int maxVal) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "Ошибка при открытии файла для записи!" << endl;
        return;
    }

    srand(static_cast<unsigned>(time(nullptr))); // Инициализация генератора случайных чисел
    for (int i = 0; i < size; ++i) {
        int randomNumber = minVal + rand() % (maxVal - minVal + 1);
        outFile.write(reinterpret_cast<const char*>(&randomNumber), sizeof(randomNumber));
    }

    outFile.close();
    cout << "Файл \"" << filename << "\" успешно заполнен случайными числами." << endl;
}

// Метод для фильтрации данных и записи в новый файл
void filterAndWriteData(const string& sourceFile, const string& targetFile, int m, int n) {
    ifstream inFile(sourceFile, ios::binary);
    if (!inFile) {
        cerr << "Ошибка при открытии исходного файла для чтения!" << endl;
        return;
    }

    ofstream outFile(targetFile, ios::binary);
    if (!outFile) {
        cerr << "Ошибка при открытии целевого файла для записи!" << endl;
        return;
    }

    int number;
    while (inFile.read(reinterpret_cast<char*>(&number), sizeof(number))) {
        if (number % m == 0 && number % n != 0) {
            outFile.write(reinterpret_cast<const char*>(&number), sizeof(number));
        }
    }

    inFile.close();
    outFile.close();

    cout << "Данные успешно отфильтрованы и записаны в файл \"" << targetFile << "\"." << endl;
}

// Метод для чтения и вывода содержимого файла
void printFileContents(const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "Ошибка при открытии файла для чтения!" << endl;
        return;
    }

    int number;
    cout << "Содержимое файла \"" << filename << "\": ";
    while (inFile.read(reinterpret_cast<char*>(&number), sizeof(number))) {
        cout << number << " ";
    }
    cout << endl;

    inFile.close();
}

int no1() {
    setlocale(LC_ALL, "Russian");

    const string sourceFile = "source.bin";
    const string targetFile = "result.bin";

    int fileSize; // Количество чисел в файле
    int minVal;    // Минимальное значение случайного числа
    int maxVal;  // Максимальное значение случайного числа
    int m;         // Число, на которое должно делиться
    int n;         // Число, на которое не должно делиться

    cout << "Введите кол-во чисел в файле: ";
    while (!(cin >> fileSize)) {
        cin.ignore();
        cin.clear();
        cout << "Ошибка ввода.";
        return 0;
    }

    cout << "Введите минимальное значение: ";
    while (!(cin >> minVal)) {
        cin.ignore();
        cin.clear();
        cout << "Ошибка ввода.";
        return 0;
    }

    cout << "Введите максимальное значение: ";
    while (!(cin >> maxVal)) {
        cin.ignore();
        cin.clear();
        cout << "Ошибка ввода.";
        return 0;
    }

    if (maxVal < minVal) {
        cout << "Ошибка ввода.";
        return 0;
    }

    cout << "Введите число, на которое дожны делиться числа: ";
    while (!(cin >> m)) {
        cin.ignore();
        cin.clear();
        cout << "Ошибка ввода.";
        return 0;
    }

    cout << "Введите число, на которое не дожны делиться числа: ";
    while (!(cin >> n)) {
        cin.ignore();
        cin.clear();
        cout << "Ошибка ввода.";
        return 0;
    }

    // Заполнение исходного файла случайными числами
    fillFileWithRandomData(sourceFile, fileSize, minVal, maxVal);

    // Вывод содержимого исходного файла
    printFileContents(sourceFile);

    // Фильтрация и запись в новый файл
    filterAndWriteData(sourceFile, targetFile, m, n);

    // Вывод содержимого нового файла
    printFileContents(targetFile);

    return 0;
}
