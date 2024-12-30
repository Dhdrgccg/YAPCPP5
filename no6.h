#pragma once
#include <iostream>
#include <fstream>
#include <string>

// ������� ��� ����������� �����, ������������ � ��������� �������
void copyLinesStartingWith(const std::string& inputFile, const std::string& outputFile, char startChar) {
    std::ifstream inFile(inputFile);
    if (!inFile.is_open()) {
        std::cerr << "������ �������� �������� �����!" << std::endl;
        return;
    }

    std::ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        std::cerr << "������ �������� ��������� �����!" << std::endl;
        inFile.close();
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        if (!line.empty() && line[0] == startChar) { // ��������� ������ ������ ������
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
    char startChar; // �������� ������ ��� ��������

    std::cout << "������� ������ � �������� ������ ���������� ����� ��� ������: ";
    std::cin >> startChar;

    // �������� ������ � ����� ����
    copyLinesStartingWith(inputFile, outputFile, startChar);

    std::cout << "������, ������������ � '" << startChar << "', ����������� � ���� \"" << outputFile << "\"." << std::endl;

    return 0;
}
