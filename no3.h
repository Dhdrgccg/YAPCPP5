#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Структура для описания багажа
struct Baggage {
    char name[20];  // Название единицы багажа (чемодан, сумка и т.д.)
    double weight;  // Масса багажа
};

// Функция для заполнения исходного файла случайными данными
void fillBaggageFile(const string& filename, int passengerCount) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "Ошибка при открытии файла для записи!" << endl;
        return;
    }

    srand(static_cast<unsigned>(time(0)));
    vector<string> baggageTypes = { "Чемодан", "Сумка", "Коробка", "Рюкзак" };

    for (int i = 0; i < passengerCount; ++i) {
        int baggageCount = 1 + rand() % 5;  // От 1 до 5 единиц багажа на пассажира
        for (int j = 0; j < baggageCount; ++j) {
            Baggage item;
            // Заменяем strcpy на strcpy_s
            strcpy_s(item.name, sizeof(item.name), baggageTypes[rand() % baggageTypes.size()].c_str());
            item.weight = 1 + (rand() % 50) + (rand() % 10) / 10.0; // Вес от 1 до 50.9 кг
            outFile.write(reinterpret_cast<const char*>(&item), sizeof(Baggage));
        }
    }

    outFile.close();
    cout << "Файл \"" << filename << "\" успешно заполнен данными." << endl;
}

// Функция для чтения данных из бинарного файла
vector<Baggage> readBaggageFile(const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "Ошибка при открытии файла для чтения!" << endl;
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

// Функция для проверки наличия пассажира с заданным условием
bool checkPassengerWithSingleLightBaggage(const vector<Baggage>& baggageList, double m) {
    bool found = false;
    int baggageCount = 0;  // Счётчик багажа для текущего пассажира
    bool hasLightBaggage = false;  // Флаг, есть ли у пассажира легкий багаж

    for (size_t i = 0; i < baggageList.size(); ++i) {
        // Если у текущего пассажира только одна единица багажа с массой < m
        if (baggageList[i].weight < m) {
            if (baggageCount == 0) {
                hasLightBaggage = true;
            }
        }

        // Считаем количество единиц багажа для текущего пассажира
        baggageCount++;

        // Когда количество багажа превышает 1, значит это следующий пассажир
        if (i + 1 < baggageList.size() && baggageList[i].weight != baggageList[i + 1].weight) {
            if (baggageCount == 1 && hasLightBaggage) {
                found = true;
            }
            baggageCount = 0; // Сброс счётчика багажа для следующего пассажира
            hasLightBaggage = false;
        }
    }

    return found;
}

int No3() {
    setlocale(LC_ALL, "Russian");

    const string filename = "baggage.bin";
    int passengerCount;  // Количество пассажиров
    double weightThreshold; // Масса менее m кг

    cout << "Введите кол-во пассажиров: ";
    while (!(cin >> passengerCount)) {
        cin.ignore();
        cin.clear();
        cout << "Ошибка ввода.";
        return 0;
    }

    cout << "Введите нужную массу багажа: ";
    while (!(cin >> weightThreshold)) {
        cin.ignore();
        cin.clear();
        cout << "Ошибка ввода.";
        return 0;
    }

    // Заполняем бинарный файл данными
    fillBaggageFile(filename, passengerCount);

    // Читаем данные из файла
    vector<Baggage> baggageList = readBaggageFile(filename);

    // Проверяем пассажиров
    if (checkPassengerWithSingleLightBaggage(baggageList, weightThreshold)) {
        cout << "Найден пассажир, у которого багаж состоит из одной единицы массой менее "
            << weightThreshold << " кг." << endl;
    }
    else {
        cout << "Такого пассажира не найдено." << endl;
    }

    return 0;
}
