#pragma once
#include <iostream>
#include <fstream>
#include <string>

// Функция для копирования строк, начинающихся с заданного символа
void copyLinesStartingWith(const std::string& inputFile, const std::string& outputFile, char startChar) {
    std::ifstream inFile(inputFile);
    if (!inFile.is_open()) {
        std::cerr << "Ошибка открытия входного файла!" << std::endl;
        return;
    }

    std::ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка открытия выходного файла!" << std::endl;
        inFile.close();
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        if (!line.empty() && line[0] == startChar) { // Проверяем первый символ строки
            outFile << line << std::endl;
        }
    }

    inFile.close();
    outFile.close();
}

int no6() {
    setlocale(LC_ALL, "Russian");

    const std::string inputFile = "input.txt";
    const std::string outputFile = "output.txt";
    char startChar; // Заданный символ для проверки

    std::cout << "Введите символ с которого должны начинаться слова или строки: ";
    std::cin >> startChar;

    // Копируем строки в новый файл
    copyLinesStartingWith(inputFile, outputFile, startChar);

    std::cout << "Строки, начинающиеся с '" << startChar << "', скопированы в файл \"" << outputFile << "\"." << std::endl;

    return 0;
}
