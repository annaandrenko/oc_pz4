#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdio>

using namespace std;

/*                                    Завдання 1.
6. Використовуючи введення - виведення в стилі С + +створити файл та записати в нього
структуровані дані.
7. Вивести створений файл на екран.
8. Видалити з файлу дані відповідно до варіанта.
9. Додати в файл дані відповідно до варіанта.
10. Вивести змінений файл на екран.

                                       Варіант 1
Структура данных
Структура "Абитуриент":
фамилия, имя, отчество;
год рождения;
оценки вступительных экзаменов (3);
средний балл аттестата.

Удаление
Удалить элемент с указанным номером.

Добавление
Добавить K элементов в начало файла
*/

struct Abiturient {
    char prizvyshche[30];
    char imya[30];
    char poBatkovi[30];
    int rikNarodzhennya;
    int ocinka1;
    int ocinka2;
    int ocinka3;
    float seredniyBal;
};

void inputAbiturient(Abiturient& a) {
    cout << "Прізвище: ";
    cin >> a.prizvyshche;
    cout << "Ім'я: ";
    cin >> a.imya;
    cout << "По батькові: ";
    cin >> a.poBatkovi;
    cout << "Рік народження: ";
    cin >> a.rikNarodzhennya;
    cout << "Оцінка 1: ";
    cin >> a.ocinka1;
    cout << "Оцінка 2: ";
    cin >> a.ocinka2;
    cout << "Оцінка 3: ";
    cin >> a.ocinka3;
    cout << "Середній бал атестата: ";
    cin >> a.seredniyBal;
}

void printHeader() {
    cout << left
        << setw(4) << "№"
        << setw(15) << "Прізвище"
        << setw(15) << "Ім'я"
        << setw(15) << "По батькові"
        << setw(8) << "Рік"
        << setw(6) << "Оц1"
        << setw(6) << "Оц2"
        << setw(6) << "Оц3"
        << setw(10) << "Сер.бал"
        << endl;
    cout << string(85, '-') << endl;
}

void printAbiturient(const Abiturient& a, int index) {
    cout << left
        << setw(4) << index
        << setw(15) << a.prizvyshche
        << setw(15) << a.imya
        << setw(15) << a.poBatkovi
        << setw(8) << a.rikNarodzhennya
        << setw(6) << a.ocinka1
        << setw(6) << a.ocinka2
        << setw(6) << a.ocinka3
        << setw(10) << fixed << setprecision(2) << a.seredniyBal
        << endl;
}

void createFile(const char* filename) {
    ofstream f(filename, ios::binary);
    if (!f) {
        cout << "Помилка відкриття файлу для запису.\n";
        return;
    }

    int n;
    cout << "Введіть кількість абітурієнтів: ";
    cin >> n;

    Abiturient a;
    for (int i = 0; i < n; i++) {
        cout << "\nВведення даних абітурієнта " << i + 1 << ":\n";
        inputAbiturient(a);
        f.write(reinterpret_cast<char*>(&a), sizeof(Abiturient));
    }

    f.close();
    cout << "\nФайл успішно створено.\n";
}

void showFile(const char* filename) {
    ifstream f(filename, ios::binary);
    if (!f) {
        cout << "Помилка відкриття файлу для читання.\n";
        return;
    }

    Abiturient a;
    int i = 1;
    bool empty = true;

    cout << "\nВміст файлу:\n";
    printHeader();

    while (f.read(reinterpret_cast<char*>(&a), sizeof(Abiturient))) {
        printAbiturient(a, i++);
        empty = false;
    }

    if (empty) {
        cout << "Файл порожній.\n";
    }

    f.close();
}

void searchBySurname(const char* filename, const char* surname) {
    ifstream f(filename, ios::binary);
    if (!f) {
        cout << "Помилка відкриття файлу для пошуку.\n";
        return;
    }

    Abiturient a;
    int i = 1;
    bool found = false;

    cout << "\nРезультат пошуку за прізвищем \"" << surname << "\":\n";
    printHeader();

    while (f.read(reinterpret_cast<char*>(&a), sizeof(Abiturient))) {
        if (strcmp(a.prizvyshche, surname) == 0) {
            printAbiturient(a, i);
            found = true;
        }
        i++;
    }

    if (!found) {
        cout << "Записів із таким прізвищем не знайдено.\n";
    }

    f.close();
}

void deleteByNumber(const char* filename, int number) {
    ifstream fin(filename, ios::binary);
    ofstream fout("temp_cpp.dat", ios::binary);

    if (!fin || !fout) {
        cout << "Помилка відкриття файлу.\n";
        return;
    }

    Abiturient a;
    int i = 1;
    bool found = false;

    while (fin.read(reinterpret_cast<char*>(&a), sizeof(Abiturient))) {
        if (i != number) {
            fout.write(reinterpret_cast<char*>(&a), sizeof(Abiturient));
        }
        else {
            found = true;
        }
        i++;
    }

    fin.close();
    fout.close();

    remove(filename);
    rename("temp_cpp.dat", filename);

    if (found)
        cout << "Елемент №" << number << " успішно видалено.\n";
    else
        cout << "Елемент із таким номером не знайдено.\n";
}

void addToBeginning(const char* filename, int k) {
    ifstream fin(filename, ios::binary);
    ofstream fout("temp_cpp.dat", ios::binary);

    if (!fout) {
        cout << "Помилка відкриття тимчасового файлу.\n";
        return;
    }

    Abiturient a;

    cout << "\nВведення " << k << " нових елементів для додавання на початок:\n";
    for (int i = 0; i < k; i++) {
        cout << "\nНовий абітурієнт " << i + 1 << ":\n";
        inputAbiturient(a);
        fout.write(reinterpret_cast<char*>(&a), sizeof(Abiturient));
    }

    if (fin) {
        while (fin.read(reinterpret_cast<char*>(&a), sizeof(Abiturient))) {
            fout.write(reinterpret_cast<char*>(&a), sizeof(Abiturient));
        }
        fin.close();
    }

    fout.close();

    remove(filename);
    rename("temp_cpp.dat", filename);

    cout << "\nНові елементи успішно додано на початок файлу.\n";
}

int main() {
    system("chcp 1251 > nul");

    const char* filename = "abiturient_cpp.dat";
    int deleteNumber, k;
    char surname[30];

    cout << "========= РОБОТА З ФАЙЛОМ У СТИЛІ C++ =========\n";

    createFile(filename);
    showFile(filename);

    cout << "\nВведіть прізвище для пошуку: ";
    cin >> surname;
    searchBySurname(filename, surname);

    cout << "\nВведіть номер елемента для видалення: ";
    cin >> deleteNumber;
    deleteByNumber(filename, deleteNumber);

    cout << "Введіть кількість K елементів для додавання на початок: ";
    cin >> k;
    addToBeginning(filename, k);

    cout << "\nЗмінений файл:\n";
    showFile(filename);

    cout << "\nПовторний пошук у зміненому файлі.\n";
    cout << "Введіть прізвище для пошуку: ";
    cin >> surname;
    searchBySurname(filename, surname);

    return 0;
}