#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <ctime>

using namespace std;

struct Date {
    int day;
    int month;
    int year;
};

struct Medicine {
    int id;
    string name;
    string category;
    double price;
    int quantity;
    Date expiryDate;

    Medicine(int i, string n, string cat, double p, int q, int d, int m, int y) {
        id = i;
        name = n;
        category = cat;
        price = p;
        quantity = q;
        expiryDate.day = d;
        expiryDate.month = m;
        expiryDate.year = y;
    }
};

void clearScreen() {
    system("clear");
}

bool isExpired(Date d) {
    time_t t = time(0);
    tm* now = localtime(&t);
    int currYear = now->tm_year + 1900;
    int currMonth = now->tm_mon + 1;
    int currDay = now->tm_mday;

    if (d.year < currYear) return true;
    if (d.year == currYear && d.month < currMonth) return true;
    if (d.year == currYear && d.month == currMonth && d.day < currDay) return true;
    return false;
}

void printHeader() {
    cout << "=============================================================" << endl;
    cout << "             АПТЕЧНА ІНФОРМАЦІЙНА СИСТЕМА v2.0              " << endl;
    cout << "=============================================================" << endl;
}

void showMedicine(const Medicine& m) {
    cout << left << setw(4) << m.id 
         << setw(20) << m.name 
         << setw(15) << m.category 
         << setw(8) << m.price 
         << setw(6) << m.quantity 
         << m.expiryDate.day << "." << m.expiryDate.month << "." << m.expiryDate.year;
    
    if (isExpired(m.expiryDate)) {
        cout << " [УВАГА: ПРОСТРОЧЕНО]";
    }
    cout << endl;
}

void saveReport(const vector<Medicine>& inventory) {
    ofstream file("pharmacy_report.txt");
    file << "ЗВІТ ПО СКЛАДУ АПТЕКИ\n";
    file << "-------------------------------------------------------------\n";
    for (const auto& m : inventory) {
        file << m.name << " | " << m.category << " | " << m.price << " грн | " << m.quantity << " шт.\n";
    }
    file.close();
}

int main() {
    setlocale(LC_ALL, "Ukrainian");

    vector<Medicine> inventory;
    inventory.push_back(Medicine(101, "Парацетамол", "Знеболювальні", 45.50, 50, 10, 12, 2025));
    inventory.push_back(Medicine(102, "Аспірин", "Знеболювальні", 30.00, 30, 1, 5, 2024));
    inventory.push_back(Medicine(103, "Вітамін C", "Вітаміни", 120.00, 100, 15, 8, 2026));
    inventory.push_back(Medicine(104, "Амоксицилін", "Антибіотики", 210.00, 15, 20, 11, 2025));
    inventory.push_back(Medicine(105, "Но-шпа", "Спазмолітики", 85.00, 40, 5, 3, 2025));
    inventory.push_back(Medicine(106, "Ібупрофен", "Знеболювальні", 55.00, 25, 12, 10, 2024));

    int choice = 0;
    while (choice != 7) {
        clearScreen();
        printHeader();
        cout << "1. Весь список ліків" << endl;
        cout << "2. Пошук за назвою" << endl;
        cout << "3. Пошук аналогів (за категорією)" << endl;
        cout << "4. Оформити продаж" << endl;
        cout << "5. Додати новий товар" << endl;
        cout << "6. Сформувати звіт у файл" << endl;
        cout << "7. Вихід" << endl;
        cout << "\nОберіть дію: ";
        cin >> choice;

        if (choice == 1) {
            clearScreen();
            printHeader();
            cout << left << setw(4) << "ID" << setw(20) << "Назва" << setw(15) << "Категорія" << setw(8) << "Ціна" << setw(6) << "К-сть" << "Термін дії" << endl;
            cout << "-------------------------------------------------------------" << endl;
            for (const auto& m : inventory) showMedicine(m);
            cout << "\nНатисніть Enter...";
            cin.ignore(); cin.get();
        } 
        else if (choice == 2) {
            string searchName;
            cout << "Введіть назву ліків: ";
            cin >> searchName;
            bool found = false;
            for (const auto& m : inventory) {
                if (m.name == searchName) {
                    showMedicine(m);
                    found = true;
                }
            }
            if (!found) cout << "Товар не знайдено." << endl;
            cin.ignore(); cin.get();
        }
        else if (choice == 3) {
            string cat;
            cout << "Введіть категорію для пошуку аналогів: ";
            cin >> cat;
            cout << "\nЗнайдені аналоги:\n";
            for (const auto& m : inventory) {
                if (m.category == cat) showMedicine(m);
            }
            cin.ignore(); cin.get();
        }
        else if (choice == 4) {
            int sellId, sellQty;
            cout << "Введіть ID товару: ";
            cin >> sellId;
            cout << "Кількість: ";
            cin >> sellQty;

            for (auto& m : inventory) {
                if (m.id == sellId) {
                    if (isExpired(m.expiryDate)) {
                        cout << "ПОМИЛКА: Товар прострочений! Продаж заборонено." << endl;
                    } else if (m.quantity >= sellQty) {
                        m.quantity -= sellQty;
                        cout << "Продано успішно. Сума: " << m.price * sellQty << " грн" << endl;
                    } else {
                        cout << "Недостатньо товару на складі!" << endl;
                    }
                }
            }
            cin.ignore(); cin.get();
        }
        else if (choice == 5) {
            int id, q, d, m, y;
            string name, cat;
            double p;
            cout << "ID: "; cin >> id;
            cout << "Назва: "; cin >> name;
            cout << "Категорія: "; cin >> cat;
            cout << "Ціна: "; cin >> p;
            cout << "Кількість: "; cin >> q;
            cout << "Термін дії (день місяць рік): "; cin >> d >> m >> y;
            inventory.push_back(Medicine(id, name, cat, p, q, d, m, y));
            cout << "Товар додано." << endl;
            cin.ignore(); cin.get();
        }
        else if (choice == 6) {
            saveReport(inventory);
            cout << "Звіт збережено у файл pharmacy_report.txt" << endl;
            cin.ignore(); cin.get();
        }
    }

    return 0;
}