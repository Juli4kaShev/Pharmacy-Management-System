#ifndef MEDICINE_H
#define MEDICINE_H

#include <string>
#include <iostream>

using namespace std;

struct Date {
    int day, month, year;
};

class Medicine {
private:
    int id;
    string name;
    string category;
    double price;
    int quantity;
    Date expiryDate;

public:
    Medicine(int i, string n, string cat, double p, int q, int d, int m, int y);

    bool isExpired() const;
    void printRow() const;
    
    int getId() const;
    string getName() const;
    string getCategory() const;
    double getPrice() const;
    int getQuantity() const;
    
    void reduceQuantity(int amount);
};

void printCell(string text, int targetWidth);

#endif