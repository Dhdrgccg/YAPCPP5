#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// ����� ��� ���������� ����� ���������� �������
void fillFileWithRandomData(const string& filename, int size, int minVal, int maxVal) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "������ ��� �������� ����� ��� ������!" << endl;
        return;
    }

    srand(static_cast<unsigned>(time(nullptr))); // ������������� ���������� ��������� �����
    for (int i = 0; i < size; ++i) {
        int randomNumber = minVal + rand() % (maxVal - minVal + 1);
        outFile.write(reinterpret_cast<const char*>(&randomNumber), sizeof(randomNumber));
    }

    outFile.close();
    cout << "���� \"" << filename << "\" ������� �������� ���������� �������." << endl;
}

// ����� ��� ���������� ������ � ������ � ����� ����
void filterAndWriteData(const string& sourceFile, const string& targetFile, int m, int n) {
    ifstream inFile(sourceFile, ios::binary);
    if (!inFile) {
        cerr << "������ ��� �������� ��������� ����� ��� ������!" << endl;
        return;
    }

    ofstream outFile(targetFile, ios::binary);
    if (!outFile) {
        cerr << "������ ��� �������� �������� ����� ��� ������!" << endl;
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

    cout << "������ ������� ������������� � �������� � ���� \"" << targetFile << "\"." << endl;
}

// ����� ��� ������ � ������ ����������� �����
void printFileContents(const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "������ ��� �������� ����� ��� ������!" << endl;
        return;
    }

    int number;
    cout << "���������� ����� \"" << filename << "\": ";
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

    int fileSize; // ���������� ����� � �����
    int minVal;    // ����������� �������� ���������� �����
    int maxVal;  // ������������ �������� ���������� �����
    int m;         // �����, �� ������� ������ ��������
    int n;         // �����, �� ������� �� ������ ��������

    cout << "������� ���-�� ����� � �����: ";
    while (!(cin >> fileSize)) {
        cin.ignore();
        cin.clear();
        cout << "������ �����.";
        return 0;
    }

    cout << "������� ����������� ��������: ";
    while (!(cin >> minVal)) {
        cin.ignore();
        cin.clear();
        cout << "������ �����.";
        return 0;
    }

    cout << "������� ������������ ��������: ";
    while (!(cin >> maxVal)) {
        cin.ignore();
        cin.clear();
        cout << "������ �����.";
        return 0;
    }

    if (maxVal < minVal) {
        cout << "������ �����.";
        return 0;
    }

    cout << "������� �����, �� ������� ����� �������� �����: ";
    while (!(cin >> m)) {
        cin.ignore();
        cin.clear();
        cout << "������ �����.";
        return 0;
    }

    cout << "������� �����, �� ������� �� ����� �������� �����: ";
    while (!(cin >> n)) {
        cin.ignore();
        cin.clear();
        cout << "������ �����.";
        return 0;
    }

    // ���������� ��������� ����� ���������� �������
    fillFileWithRandomData(sourceFile, fileSize, minVal, maxVal);

    // ����� ����������� ��������� �����
    printFileContents(sourceFile);

    // ���������� � ������ � ����� ����
    filterAndWriteData(sourceFile, targetFile, m, n);

    // ����� ����������� ������ �����
    printFileContents(targetFile);

    return 0;
}
