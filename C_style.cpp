#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cstring>

using namespace std;

/*                                    Завдання 1.
1. Використовуючи введення - виведення в стилі С створити файл та записати в нього
структуровані дані.
2. Вивести створений файл на екран.
3. Видалити з файлу дані відповідно до варіанта.
4. Додати в файл дані відповідно до варіанта.
5. Вивести змінений файл на екран.

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

void createFileC(const char* filename) {
    FILE* f = fopen(filename, "wb");
    if (f == NULL) {
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

        if (fwrite(&a, sizeof(Abiturient), 1, f) != 1) {
            cout << "Помилка запису у файл.\n";
            fclose(f);
            return;
        }
    }

    fclose(f);
    cout << "\nФайл успішно створено.\n";
}

void showFileC(const char* filename) {
    FILE* f = fopen(filename, "rb");
    if (f == NULL) {
        cout << "Помилка відкриття файлу для читання.\n";
        return;
    }

    Abiturient a;
    int i = 1;
    bool empty = true;

    cout << "\nВміст файлу:\n";
    printHeader();

    while (fread(&a, sizeof(Abiturient), 1, f) == 1) {
        printAbiturient(a, i++);
        empty = false;
    }

    if (empty) {
        cout << "Файл порожній.\n";
    }

    fclose(f);
}

void searchBySurnameC(const char* filename, const char* surname) {
    FILE* f = fopen(filename, "rb");
    if (f == NULL) {
        cout << "Помилка відкриття файлу для пошуку.\n";
        return;
    }

    Abiturient a;
    int i = 1;
    bool found = false;

    cout << "\nРезультат пошуку за прізвищем \"" << surname << "\":\n";
    printHeader();

    while (fread(&a, sizeof(Abiturient), 1, f) == 1) {
        if (strcmp(a.prizvyshche, surname) == 0) {
            printAbiturient(a, i);
            found = true;
        }
        i++;
    }

    if (!found) {
        cout << "Записів із таким прізвищем не знайдено.\n";
    }

    fclose(f);
}

void deleteByNumberC(const char* filename, int number) {
    FILE* f = fopen(filename, "rb");
    FILE* temp = fopen("temp_c.dat", "wb");

    if (f == NULL || temp == NULL) {
        cout << "Помилка відкриття файлу.\n";
        if (f) fclose(f);
        if (temp) fclose(temp);
        return;
    }

    Abiturient a;
    int i = 1;
    bool found = false;

    while (fread(&a, sizeof(Abiturient), 1, f) == 1) {
        if (i != number) {
            fwrite(&a, sizeof(Abiturient), 1, temp);
        }
        else {
            found = true;
        }
        i++;
    }

    fclose(f);
    fclose(temp);

    remove(filename);
    rename("temp_c.dat", filename);

    if (found)
        cout << "Елемент №" << number << " успішно видалено.\n";
    else
        cout << "Елемент із таким номером не знайдено.\n";
}

void addToBeginningC(const char* filename, int k) {
    FILE* f = fopen(filename, "rb");
    FILE* temp = fopen("temp_c.dat", "wb");

    if (temp == NULL) {
        cout << "Помилка відкриття тимчасового файлу.\n";
        if (f) fclose(f);
        return;
    }

    Abiturient a;

    cout << "\nВведення " << k << " нових елементів для додавання на початок:\n";
    for (int i = 0; i < k; i++) {
        cout << "\nНовий абітурієнт " << i + 1 << ":\n";
        inputAbiturient(a);
        fwrite(&a, sizeof(Abiturient), 1, temp);
    }

    if (f != NULL) {
        while (fread(&a, sizeof(Abiturient), 1, f) == 1) {
            fwrite(&a, sizeof(Abiturient), 1, temp);
        }
        fclose(f);
    }

    fclose(temp);

    remove(filename);
    rename("temp_c.dat", filename);

    cout << "\nНові елементи успішно додано на початок файлу.\n";
}

int main() {
    system("chcp 1251 > nul");

    const char* filename = "abiturient_c.dat";
    int deleteNumber, k;
    char surname[30];

    cout << "========= РОБОТА З ФАЙЛОМ У СТИЛІ C =========\n";

    createFileC(filename);
    showFileC(filename);

    cout << "\nВведіть прізвище для пошуку: ";
    cin >> surname;
    searchBySurnameC(filename, surname);

    cout << "\nВведіть номер елемента для видалення: ";
    cin >> deleteNumber;
    deleteByNumberC(filename, deleteNumber);

    cout << "Введіть кількість K елементів для додавання на початок: ";
    cin >> k;
    addToBeginningC(filename, k);

    cout << "\nЗмінений файл:\n";
    showFileC(filename);

    cout << "\nПовторний пошук у зміненому файлі.\n";
    cout << "Введіть прізвище для пошуку: ";
    cin >> surname;
    searchBySurnameC(filename, surname);

    return 0;
}