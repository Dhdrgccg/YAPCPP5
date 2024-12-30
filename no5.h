#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <sstream>

// ������� ��� ���������� ����� ���������� �������
void fillFileWithRandomNumbers(const std::string& filename, int rows, int numbersPerRow, int minVal, int maxVal) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "������ �������� ����� ��� ������!" << std::endl;
        return;
    }

    std::srand(std::time(nullptr)); // ������������� ���������� ��������� �����

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < numbersPerRow; ++j) {
            int randomNum = minVal + std::rand() % (maxVal - minVal + 1);
            outFile << randomNum;
            if (j < numbersPerRow - 1) outFile << " "; // ���������� ����� ���������
        }
        outFile << std::endl; // ������� �� ����� ������
    }

    outFile.close();
}

// ������� ��� ���������� ������������ ��������
int findMinimum(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "������ �������� ����� ��� ������!" << std::endl;
        return 0;
    }

    int minNum = std::numeric_limits<int>::max();
    std::string line;

    // ������ ����� ���������
    while (std::getline(inFile, line)) {
        std::istringstream lineStream(line); // ����� ��� ������ � ��������� �������
        int num;

        while (lineStream >> num) { // ������ ����� �� ������
            if (num < minNum) minNum = num;
        }
    }

    inFile.close();
    return minNum;
}

int no5() {
    setlocale(LC_ALL, "Russian");

    const std::string filename = "numbers2.txt";
    int rows;         // ���������� �����
    int numbersPerRow;    // ���������� ����� � ������
    int minVal;       // ����������� ��������
    int maxVal;        // ������������ ��������

    std::cout << "������� ���-�� �����: ";
    while (!(std::cin >> rows)) {
        std::cin.ignore();
        std::cin.clear();
        cout << "������ �����.";
        return 0;
    }

    std::cout << "������� ���-�� ����� � ������: ";
    while (!(std::cin >> numbersPerRow)) {
        std::cin.ignore();
        std::cin.clear();
        cout << "������ �����.";
        return 0;
    }

    std::cout << "������� ����������� ��������: ";
    while (!(std::cin >> minVal)) {
        std::cin.ignore();
        std::cin.clear();
        cout << "������ �����.";
        return 0;
    }

    std::cout << "������� ������������ ��������: ";
    while (!(std::cin >> maxVal)) {
        std::cin.ignore();
        std::cin.clear();
        cout << "������ �����.";
        return 0;
    }

    if (maxVal < minVal) {
        std::cout << "������ �����.";
        return 0;
    }


    // ���������� ����� ���������� �������
    fillFileWithRandomNumbers(filename, rows, numbersPerRow, minVal, maxVal);

    // ���������� ������������ ��������
    int minElement = findMinimum(filename);
    std::cout << "����������� �������: " << minElement << std::endl;

    return 0;
}
