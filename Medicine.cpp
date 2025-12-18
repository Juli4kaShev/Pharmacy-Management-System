#include "Medicine.h"
#include <ctime>
#include <iomanip>
#include <sstream>

Medicine::Medicine(int i, string n, string cat, double p, int q, int d, int m, int y) {
    id = i;
    name = n;
    category = cat;
    price = p;
    quantity = q;
    expiryDate.day = d;
    expiryDate.month = m;
    expiryDate.year = y;
}

bool Medicine::isExpired() const {
    time_t t = time(0);
    tm* now = localtime(&t);
    int cY = now->tm_year + 1900;
    int cM = now->tm_mon + 1;
    int cD = now->tm_mday;
    
    if (expiryDate.year < cY) return true;
    if (expiryDate.year == cY && expiryDate.month < cM) return true;
    if (expiryDate.year == cY && expiryDate.month == cM && expiryDate.day < cD) return true;
    return false;
}

void printCell(string text, int targetWidth) {
    cout << " " << text;
    int currentLen = 0;
    for (int i = 0; i < text.length(); i++) {
        if ((text[i] & 0xC0) != 0x80) currentLen++;
    }
    int spaces = targetWidth - currentLen;
    if (spaces < 0) spaces = 0;
    for(int i = 0; i < spaces; i++) cout << " ";
    cout << " |";
}

void Medicine::printRow() const {
    cout << "|";
    printCell(to_string(id), 5);
    printCell(name, 18);
    printCell(category, 18);
    
    stringstream ss;
    ss << price;
    printCell(ss.str(), 8);
    
    printCell(to_string(quantity), 6);
    
    cout << " " << expiryDate.day << "." << expiryDate.month << "." << expiryDate.year;
    
    if (isExpired()) cout << " [ПРОСТРОЧЕНО]";
    cout << endl;
}

int Medicine::getId() const { return id; }
string Medicine::getName() const { return name; }
string Medicine::getCategory() const { return category; }
double Medicine::getPrice() const { return price; }
int Medicine::getQuantity() const { return quantity; }

void Medicine::reduceQuantity(int amount) {
    if (amount <= quantity) quantity -= amount;
}