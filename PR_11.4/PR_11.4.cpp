#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

const int MAX_PRODUCTS = 100;

struct Tovar {
    string nazva;
    double vartis;
    int kilkist;
    string odun_vum;
};

void Create(Tovar tovary[], int& n);
void Print(const Tovar tovary[], int n);
void SearchTovarByName(const Tovar tovary[], int n);
void SearchTovarByRange(const Tovar tovary[], int n);
void SaveToFile(const Tovar tovary[], int n, const string& filename);
void LoadFromFile(Tovar tovary[], int& n, const string& filename);
bool IsValidNumber(const string& str);
bool IsValidDouble(const string& str);
bool IsValidInteger(const string& str);
void SortByName(Tovar tovary[], int n);
void SortByTotalValue(Tovar tovary[], int n);
bool CompareByName(const Tovar& a, const Tovar& b);
bool CompareByTotalValue(const Tovar& a, const Tovar& b);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Tovar tovary[MAX_PRODUCTS];
    int n = 0;
    string filename;

    cout << "Введіть ім'я файлу: ";
    cin >> filename;

    LoadFromFile(tovary, n, filename);

    int menuItem;
    do {
        cout << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - Вивід товарів на екран" << endl;
        cout << " [2] - Додавання нового товару" << endl;
        cout << " [3] - Пошук товару за назвою" << endl;
        cout << " [4] - Пошук товарів за діапазоном вартості" << endl;
        cout << " [5] - Сортувати за назвою товару" << endl;
        cout << " [6] - Сортувати за загальною вартістю" << endl;
        cout << " [0] - Зберегти та вийти" << endl << endl;
        cout << "Введіть значення: ";
        cin >> menuItem;
        cout << endl << endl;

        switch (menuItem) {
        case 1:
            Print(tovary, n);
            break;
        case 2:
            Create(tovary, n);
            break;
        case 3:
            SearchTovarByName(tovary, n);
            break;
        case 4:
            SearchTovarByRange(tovary, n);
            break;
        case 5:
            SortByName(tovary, n);
            break;
        case 6:
            SortByTotalValue(tovary, n);
            break;
        case 0:
            SaveToFile(tovary, n, filename);
            break;
        default:
            cout << "Ви ввели помилкове значення! "
                << "Слід ввести число - номер вибраного пункту меню" << endl;
        }
    } while (menuItem != 0);

    return 0;
}

void Create(Tovar tovary[], int& n) {
    if (n >= MAX_PRODUCTS) {
        cout << "Перевищено максимальну кількість товарів." << endl;
        return;
    }

    cout << "Назва товару: "; cin >> tovary[n].nazva;
    cout << "Вартість товару за одиницю товару: ";
    string vartisInput;
    cin >> vartisInput;
    while (!IsValidDouble(vartisInput)) {
        cout << "Введено некоректну вартість. Спробуйте ще раз: ";
        cin >> vartisInput;
    }
    tovary[n].vartis = stod(vartisInput);

    cout << "Кількість товару: ";
    string kilkistInput;
    cin >> kilkistInput;
    while (!IsValidInteger(kilkistInput)) {
        cout << "Введено некоректну кількість. Спробуйте ще раз: ";
        cin >> kilkistInput;
    }
    tovary[n].kilkist = stoi(kilkistInput);

    cout << "Одиниця вимірювання: "; cin >> tovary[n].odun_vum;
    n++;
}

void Print(const Tovar tovary[], int n) {
    if (n == 0) {
        cout << "Список товарів порожній." << endl;
        return;
    }

    cout << "=========================================================="
        << endl;
    cout << "| № | Назва товару | Вартість | Кількість | Одиниця вим. |"
        << endl;
    cout << "----------------------------------------------------------"
        << endl;

    for (int i = 0; i < n; ++i) {
        cout << "| " << setw(1) << right << i + 1 << " ";
        cout << "| " << setw(13) << left << tovary[i].nazva
            << "| " << setw(8) << right << fixed << setprecision(2) << tovary[i].vartis << " "
            << "| " << setw(9) << left << tovary[i].kilkist << " "
            << "| " << setw(12) << left << tovary[i].odun_vum << " |" << endl;
    }
    cout << "=========================================================="
        << endl;
    cout << endl;
}

void SearchTovarByName(const Tovar tovary[], int n) {
    if (n == 0) {
        cout << "Список товарів порожній." << endl;
        return;
    }

    string nazva;
    cout << "Введіть назву товару: ";
    cin >> nazva;

    bool found = false;
    for (int i = 0; i < n; ++i) {
        if (tovary[i].nazva == nazva) {
            cout << "Товар знайдено:" << endl;
            cout << "| Назва товару | Вартість | Кількість | Одиниця вим. |" << endl;
            cout << "| " << setw(13) << left << tovary[i].nazva
                << "| " << setw(8) << right << fixed << setprecision(2) << tovary[i].vartis << " "
                << "| " << setw(9) << left << tovary[i].kilkist << " "
                << "| " << setw(14) << left << tovary[i].odun_vum << " |" << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Такого товару немає в асортименті" << endl;
    }
}

void SearchTovarByRange(const Tovar tovary[], int n) {
    if (n == 0) {
        cout << "Список товарів порожній." << endl;
        return;
    }

    double minPrice, maxPrice;
    cout << "Введіть діапазон вартості товару (мінімальна та максимальна ціна): ";
    string minPriceInput, maxPriceInput;
    cin >> minPriceInput >> maxPriceInput;

    while (!IsValidDouble(minPriceInput) || !IsValidDouble(maxPriceInput) || stod(minPriceInput) >= stod(maxPriceInput)) {
        cout << "Введено некоректний діапазон. Спробуйте ще раз: ";
        cin >> minPriceInput >> maxPriceInput;
    }

    minPrice = stod(minPriceInput);
    maxPrice = stod(maxPriceInput);

    cout << "Товари з вартістю в діапазоні [" << minPrice << ", " << maxPrice << "]:" << endl;
    cout << "| Назва товару | Вартість | Кількість | Одиниця вим. |" << endl;
    for (int i = 0; i < n; ++i) {
        double totalValue = tovary[i].vartis;// *tovary[i].kilkist;
        if (totalValue >= minPrice && totalValue <= maxPrice) {
            cout << "| " << setw(13) << left << tovary[i].nazva
                << "| " << setw(8) << right << fixed << setprecision(2) << tovary[i].vartis << " "
                << "| " << setw(9) << left << tovary[i].kilkist << " "
                << "| " << setw(14) << left << tovary[i].odun_vum << " |" << endl;
        }
    }
}

void SaveToFile(const Tovar tovary[], int n, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < n; ++i) {
            file << tovary[i].nazva << "," << tovary[i].vartis << "," << tovary[i].kilkist << "," << tovary[i].odun_vum << endl;
        }
        file.close();
        cout << "Список товарів збережено у файл " << filename << endl;
    }
    else {
        cout << "Помилка відкриття файлу для запису." << endl;
    }
}

void LoadFromFile(Tovar tovary[], int& n, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line) && n < MAX_PRODUCTS) {
            size_t pos = 0;
            pos = line.find(',');
            tovary[n].nazva = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(',');
            tovary[n].vartis = stod(line.substr(0, pos));
            line.erase(0, pos + 1);

            pos = line.find(',');
            tovary[n].kilkist = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);

            tovary[n].odun_vum = line;
            n++;
        }
        file.close();
        cout << "Список товарів завантажено з файлу " << filename << endl;
    }
    else {
        cout << "Файл " << filename << " не знайдено. Новий список буде створено." << endl;
    }
}

bool IsValidNumber(const string& str) {
    for (char c : str) {
        if (!isdigit(c) && c != '.') {
            return false;
        }
    }
    return true;
}

bool IsValidDouble(const string& str) {
    if (str.empty()) {
        return false;
    }

    int dotCount = 0;
    for (char c : str) {
        if (!isdigit(c) && c != '.') {
            return false;
        }
        if (c == '.') {
            dotCount++;
        }
    }

    return dotCount <= 1;
}

bool IsValidInteger(const string& str) {
    if (str.empty()) {
        return false;
    }

    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }

    return true;
}

bool CompareByName(const Tovar& a, const Tovar& b) {
    return a.nazva < b.nazva;
}

bool CompareByTotalValue(const Tovar& a, const Tovar& b) {
    return (a.vartis * a.kilkist) < (b.vartis * b.kilkist);
}

void SortByName(Tovar tovary[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (CompareByName(tovary[j], tovary[j + 1])) {
                Tovar temp = tovary[j];
                tovary[j] = tovary[j + 1];
                tovary[j + 1] = temp;
            }
        }
    }
}

void SortByTotalValue(Tovar tovary[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (CompareByTotalValue(tovary[j], tovary[j + 1])) {
                Tovar temp = tovary[j];
                tovary[j] = tovary[j + 1];
                tovary[j + 1] = temp;
            }
        }
    }
}
