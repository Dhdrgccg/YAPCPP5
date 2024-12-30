#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// ��������� ��� �������� ������
struct Baggage {
    char name[20];  // �������� ������� ������ (�������, ����� � �.�.)
    double weight;  // ����� ������
};

// ������� ��� ���������� ��������� ����� ���������� �������
void fillBaggageFile(const string& filename, int passengerCount) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "������ ��� �������� ����� ��� ������!" << endl;
        return;
    }

    srand(static_cast<unsigned>(time(0)));
    vector<string> baggageTypes = { "�������", "�����", "�������", "������" };

    for (int i = 0; i < passengerCount; ++i) {
        int baggageCount = 1 + rand() % 5;  // �� 1 �� 5 ������ ������ �� ���������
        for (int j = 0; j < baggageCount; ++j) {
            Baggage item;
            // �������� strcpy �� strcpy_s
            strcpy_s(item.name, sizeof(item.name), baggageTypes[rand() % baggageTypes.size()].c_str());
            item.weight = 1 + (rand() % 50) + (rand() % 10) / 10.0; // ��� �� 1 �� 50.9 ��
            outFile.write(reinterpret_cast<const char*>(&item), sizeof(Baggage));
        }
    }

    outFile.close();
    cout << "���� \"" << filename << "\" ������� �������� �������." << endl;
}

// ������� ��� ������ ������ �� ��������� �����
vector<Baggage> readBaggageFile(const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "������ ��� �������� ����� ��� ������!" << endl;
        return {};
    }

    vector<Baggage> baggageList;
    Baggage item;

    while (inFile.read(reinterpret_cast<char*>(&item), sizeof(Baggage))) {
        baggageList.push_back(item);
    }

    inFile.close();
    return baggageList;
}

// ������� ��� �������� ������� ��������� � �������� ��������
bool checkPassengerWithSingleLightBaggage(const vector<Baggage>& baggageList, double m) {
    bool found = false;
    int baggageCount = 0;  // ������� ������ ��� �������� ���������
    bool hasLightBaggage = false;  // ����, ���� �� � ��������� ������ �����

    for (size_t i = 0; i < baggageList.size(); ++i) {
        // ���� � �������� ��������� ������ ���� ������� ������ � ������ < m
        if (baggageList[i].weight < m) {
            if (baggageCount == 0) {
                hasLightBaggage = true;
            }
        }

        // ������� ���������� ������ ������ ��� �������� ���������
        baggageCount++;

        // ����� ���������� ������ ��������� 1, ������ ��� ��������� ��������
        if (i + 1 < baggageList.size() && baggageList[i].weight != baggageList[i + 1].weight) {
            if (baggageCount == 1 && hasLightBaggage) {
                found = true;
            }
            baggageCount = 0; // ����� �������� ������ ��� ���������� ���������
            hasLightBaggage = false;
        }
    }

    return found;
}

int No3() {
    setlocale(LC_ALL, "Russian");

    const string filename = "baggage.bin";
    int passengerCount;  // ���������� ����������
    double weightThreshold; // ����� ����� m ��

    cout << "������� ���-�� ����������: ";
    while (!(cin >> passengerCount)) {
        cin.ignore();
        cin.clear();
        cout << "������ �����.";
        return 0;
    }

    cout << "������� ������ ����� ������: ";
    while (!(cin >> weightThreshold)) {
        cin.ignore();
        cin.clear();
        cout << "������ �����.";
        return 0;
    }

    // ��������� �������� ���� �������
    fillBaggageFile(filename, passengerCount);

    // ������ ������ �� �����
    vector<Baggage> baggageList = readBaggageFile(filename);

    // ��������� ����������
    if (checkPassengerWithSingleLightBaggage(baggageList, weightThreshold)) {
        cout << "������ ��������, � �������� ����� ������� �� ����� ������� ������ ����� "
            << weightThreshold << " ��." << endl;
    }
    else {
        cout << "������ ��������� �� �������." << endl;
    }

    return 0;
}
