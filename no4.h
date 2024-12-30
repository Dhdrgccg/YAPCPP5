#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

// ������� ��� ���������� ����� ���������� �������
void fillFileWithRandomNumbers(const std::string& filename, int count, int minVal, int maxVal) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "������ �������� ����� ��� ������!" << std::endl;
        return;
    }

    std::srand(std::time(nullptr)); // ������������� ���������� ��������� �����

    for (int i = 0; i < count; ++i) {
        int randomNum = minVal + std::rand() % (maxVal - minVal + 1);
        outFile << randomNum << std::endl;
    }

    outFile.close();
}

// ������� ��� ������ ����� �� ����� � ���������� ��������
int findDifference(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "������ �������� ����� ��� ������!" << std::endl;
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
    int coun;       // ���������� ��������� �����
    int minVal;    // ����������� ��������
    int maxVal;     // ������������ ��������

    std::cout << "������� ���-�� �����: ";
    while (!(std::cin >> coun)) {
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
    fillFileWithRandomNumbers(filename, coun, minVal, maxVal);

    // ���������� �������� ������������� � ������������ ���������
    int difference = findDifference(filename);
    std::cout << "�������� ������������� � ������������ ���������: " << difference << std::endl;

    return 0;
}
