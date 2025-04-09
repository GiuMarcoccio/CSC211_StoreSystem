// Giuseppe Marcoccio  
// CSC 211 - 1900

#ifndef STORE_H
#define STORE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

// Constant NYC tax rate
const double TAXNYC = 8.875;

// Structure for inventory items
struct StoreInventory {
    long itemID;
    string itemName;
    double itemQuantity;
    double itemPrice;
};

// Structure for customer orders
struct Order {
    long itemOrderedID;
    string itemOrderedName;
    double itemOrderedQuantity;
};

// Store class definition
class Store {
private:
    int iD;
    string name;
    int units;
    double retailPrice;

protected:
    // Totals used for calculations and receipts
    double subTotal = 0.0;
    double tax = 0.0;
    double total = 0.0;

public:
    // Constructors
    Store(int id = 0, string n = "", int u = 0, double rp = 0.0)
        : iD(id), name(n), units(u), retailPrice(rp) {}

    Store(string n, int u)
        : name(n), units(u) {}

    // Functional methods
    void displayInventory(string invFile);
    void setOrder(string orderFile);
    void inventoryUpdate(string orderFile, string invFile);
    void calculateOrder(string orderFile, string invFile);
    void orderReceipt(string orderFile, string sumOrderFile);
    void displayOrder(string orderFile);
    void addInventory(string invFile, string addInvFile);

    // Setters
    void setItemID(int id) { iD = id; }
    void setName(string n) { name = n; }
    void setUnits(int u) { units = u; }
    void setRetailPrice(double rp) { retailPrice = rp; }

    // Getters
    int getItemID() const { return iD; }
    string getName() const { return name; }
    int getUnits() const { return units; }
    double getRetailPrice() const { return retailPrice; }

    // Totals access (if needed externally)
    double getSubTotal() const { return subTotal; }
    double getTax() const { return tax; }
    double getTotal() const { return total; }
};

#endif
