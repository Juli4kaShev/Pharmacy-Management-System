#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "Medicine.h"

using namespace std;

int main() {
    setlocale(LC_ALL, ""); 
    srand(time(0));

    vector<Medicine> inventory;
    
    inventory.push_back(Medicine(101, "Парацетамол", "Знеболювальні", 45.5, 50, 10, 12, 2026));
    inventory.push_back(Medicine(103, "Вітамін C", "Вітаміни", 120, 100, 15, 8, 2026));
    inventory.push_back(Medicine(105, "Но-шпа", "Спазмолітики", 85, 40, 5, 3, 2027));
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
        cout << "1. Список ліків  2. Пошук  3. Аналоги  4. Продаж (+РАНДОМ)  5. Додати  6. Звіт  7. Вихід" << endl;
        cout << "\nОберіть дію: ";
        cin >> choice;

        if (choice == 1) {
            system("clear");
            cout << "----------------------------------------------------------------------------------" << endl;
            cout << "|";
            printCell("ID", 5);
            printCell("Назва", 18);
            printCell("Категорія", 18);
            printCell("Ціна", 8);
            printCell("К-сть", 6);
            cout << " Термін дії" << endl;
            cout << "----------------------------------------------------------------------------------" << endl;
            
            for (const auto& m : inventory) m.printRow();
            
            cout << "----------------------------------------------------------------------------------" << endl;
            cout << "\nНатисніть Enter...";
            cin.ignore(); cin.get();
        }
        else if (choice == 2) {
            string searchName;
            cout << "Введіть назву ліків: "; cin >> searchName;
            bool found = false;
            cout << "----------------------------------------------------------------------------------" << endl;
            for (const auto& m : inventory) {
                if (m.getName() == searchName) { m.printRow(); found = true; }
            }
            if (!found) cout << "Товар не знайдено." << endl;
            cin.ignore(); cin.get();
        }
        else if (choice == 3) {
            string cat;
            cout << "Введіть категорію: "; cin >> cat;
            cout << "----------------------------------------------------------------------------------" << endl;
            for (const auto& m : inventory) {
                if (m.getCategory() == cat) m.printRow();
            }
            cin.ignore(); cin.get();
        }
        else if (choice == 4) {
            int sId, sQ;
            cout << "Введіть ID товару: "; cin >> sId;
            cout << "Кількість: "; cin >> sQ;
            
            bool found = false;
            for (auto& m : inventory) {
                if (m.getId() == sId) {
                    found = true;
                    if (m.isExpired()) {
                        cout << "ПОМИЛКА: Товар прострочений! Продаж заборонено." << endl;
                    } 
                    else if (m.getQuantity() >= sQ) {
                        m.reduceQuantity(sQ);
                        double total = m.getPrice() * sQ;
                        
                        int discountPercent = rand() % 21;
                        double discountAmount = total * (discountPercent / 100.0);
                        double finalPrice = total - discountAmount;
                        
                        cout << "\n--- ЧЕК ---" << endl;
                        cout << "Сума: " << total << " грн" << endl;
                        if (discountPercent > 0) {
                            cout << "ВАМ ПОЩАСТИЛО! Знижка: " << discountPercent << "% (-" << discountAmount << " грн)" << endl;
                        }
                        cout << "ДО СПЛАТИ: " << finalPrice << " грн" << endl;
                    } 
                    else cout << "Недостатньо товару." << endl;
                }
            }
            if (!found) cout << "ID не знайдено." << endl;
            cin.ignore(); cin.get();
        }
        else if (choice == 5) {
             int id, q, d, m, y; string name, cat; double p;
             cout << "Дані (ID Назва Категорія Ціна Кількість Д М Р): ";
             cin >> id >> name >> cat >> p >> q >> d >> m >> y;
             inventory.push_back(Medicine(id, name, cat, p, q, d, m, y));
             cin.ignore(); cin.get();
        }
        else if (choice == 6) {
            ofstream f("pharmacy_report.txt");
            f << "ЗВІТ АПТЕКИ\n";
            for (const auto& m : inventory) f << m.getName() << " | " << m.getQuantity() << " шт\n";
            f.close();
            cout << "Звіт збережено." << endl;
            cin.ignore(); cin.get();
        }
    }
    return 0;
}