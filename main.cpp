#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <sstream>

using namespace std;

struct Date {
    int day, month, year;
};

struct Medicine {
    int id;
    string name;
    string category;
    double price;
    int quantity;
    Date expiryDate;

    Medicine(int i, string n, string cat, double p, int q, int d, int m, int y) 
        : id(i), name(n), category(cat), price(p), quantity(q) {
        expiryDate.day = d; expiryDate.month = m; expiryDate.year = y;
    }
};

bool isExpired(Date d) {
    time_t t = time(0);
    tm* now = localtime(&t);
    int cY = now->tm_year + 1900;
    int cM = now->tm_mon + 1;
    int cD = now->tm_mday;
    if (d.year < cY) return true;
    if (d.year == cY && d.month < cM) return true;
    if (d.year == cY && d.month == cM && d.day < cD) return true;
    return false;
}

// Проста функція: додаємо пробіли, поки довжина не стане потрібною
// Ніякої магії, просто механічне додавання
void printCell(string text, int targetWidth) {
    cout << " " << text;
    
    // Рахуємо реальну довжину (кирилиця - це нюанс, але тут ми просто беремо запас)
    int currentLen = 0;
    for (int i = 0; i < text.length(); i++) {
        if ((text[i] & 0xC0) != 0x80) currentLen++;
    }
    
    int spaces = targetWidth - currentLen;
    if (spaces < 0) spaces = 0;
    
    for(int i = 0; i < spaces; i++) cout << " ";
    cout << " |";
}

void showMedicine(const Medicine& m) {
    cout << "|";
    printCell(to_string(m.id), 5);
    printCell(m.name, 18);        // Збільшив до 18
    printCell(m.category, 18);    // Збільшив до 18
    
    stringstream ss;
    ss << m.price;
    string priceStr = ss.str();
    printCell(priceStr, 8);       // Ціна без "грн" щоб було простіше вирівняти, або змінимо нижче
    
    printCell(to_string(m.quantity), 6);
    
    cout << " " << m.expiryDate.day << "." << m.expiryDate.month << "." << m.expiryDate.year;
    
    if (isExpired(m.expiryDate)) cout << " [ПРОСТРОЧЕНО]";
    cout << endl;
}

int main() {
    setlocale(LC_ALL, ""); // Стандартне налаштування мови

    vector<Medicine> inventory;
    inventory.push_back(Medicine(101, "Парацетамол", "Знеболювальні", 45.5, 50, 10, 12, 2026));
    inventory.push_back(Medicine(103, "ВітамінC", "Вітаміни", 120, 100, 15, 8, 2026));
    inventory.push_back(Medicine(105, "Ношпа", "Спазмолітики", 85, 40, 5, 3, 2027));
    inventory.push_back(Medicine(107, "Цитрамон", "Знеболювальні", 25, 80, 20, 1, 2027));
    inventory.push_back(Medicine(108, "Мезим", "Травлення", 150, 20, 10, 5, 2026));
    inventory.push_back(Medicine(109, "Корвалол", "Серцеві", 40, 60, 14, 2, 2027));
    inventory.push_back(Medicine(110, "Лоратадин", "Алергія", 65, 35, 11, 11, 2026));
    inventory.push_back(Medicine(111, "Пантенол", "Опіки", 110, 15, 30, 6, 2026));
    inventory.push_back(Medicine(112, "АЦЦ", "Кашель", 190, 25, 12, 12, 2026));
    inventory.push_back(Medicine(113, "Дексаметазон", "Протизапальні", 95, 10, 5, 7, 2027));
    inventory.push_back(Medicine(102, "Аспірин", "Знеболювальні", 30, 30, 1, 5, 2024));
    inventory.push_back(Medicine(106, "Ібупрофен", "Знеболювальні", 55, 25, 12, 10, 2024));

    int choice = 0;
    while (choice != 7) {
        system("clear"); 
        cout << "==================================================================================" << endl;
        cout << "                            АПТЕЧНА ІНФОРМАЦІЙНА СИСТЕМА                          " << endl;
        cout << "==================================================================================" << endl;
        cout << "1. Список ліків  2. Пошук  3. Аналоги  4. Продаж  5. Додати  6. Звіт  7. Вихід" << endl;
        cout << "\nОберіть дію: ";
        cin >> choice;

        if (choice == 1) {
            system("clear");
            cout << "----------------------------------------------------------------------------------" << endl;
            cout << "|";
            // ТУТ Я ВИСТАВИВ ТІ Ж ЦИФРИ ЩО І В ДАНИХ: 5, 18, 18, 8, 6
            printCell("ID", 5);
            printCell("Назва", 18);
            printCell("Категорія", 18);
            printCell("Ціна", 8);
            printCell("К-сть", 6);
            cout << " Термін дії" << endl;
            cout << "----------------------------------------------------------------------------------" << endl;
            
            for (const auto& m : inventory) showMedicine(m);
            cout << "----------------------------------------------------------------------------------" << endl;
            
            cout << "\nНатисніть Enter...";
            cin.ignore(); cin.get();
        }
        // ... (решта коду без змін) ...
        else if (choice == 2) {
            string searchName;
            cout << "Введіть назву ліків: "; cin >> searchName;
            bool found = false;
            for (const auto& m : inventory) {
                if (m.name == searchName) { showMedicine(m); found = true; }
            }
            if (!found) cout << "Не знайдено." << endl;
            cin.ignore(); cin.get();
        }
        else if (choice == 3) {
            string cat;
            cout << "Введіть категорію: "; cin >> cat;
            for (const auto& m : inventory) {
                if (m.category == cat) showMedicine(m);
            }
            cin.ignore(); cin.get();
        }
        else if (choice == 4) {
            int sId, sQ;
            cout << "ID: "; cin >> sId; cout << "Кількість: "; cin >> sQ;
            for (auto& m : inventory) {
                if (m.id == sId) {
                    if (isExpired(m.expiryDate)) cout << "ПРОСТРОЧЕНО!" << endl;
                    else if (m.quantity >= sQ) {
                        m.quantity -= sQ;
                        cout << "Продано. Сума: " << m.price * sQ << endl;
                    } else cout << "Недостатньо." << endl;
                }
            }
            cin.ignore(); cin.get();
        }
        else if (choice == 5) {
             int id, q, d, m, y; string name, cat; double p;
             cout << "Введіть дані: "; cin >> id >> name >> cat >> p >> q >> d >> m >> y;
             inventory.push_back(Medicine(id, name, cat, p, q, d, m, y));
             cin.ignore(); cin.get();
        }
        else if (choice == 6) {
            ofstream f("pharmacy_report.txt");
            for (const auto& m : inventory) f << m.name << " " << m.quantity << "\n";
            f.close();
            cout << "Звіт збережено." << endl;
            cin.ignore(); cin.get();
        }
    }
    return 0;
}