#include "Store.hpp"

/*
    E. Display Inventory

    Author: Giuseppe Marcoccio

    Description:
    Reads the inventory file and displays the available items with ID, name,
    quantity, and price in a formatted table.
*/

void Store::displayInventory(string invFile) {
    StoreInventory inv;
    ifstream infile(invFile);
    string line;

    if (!infile.is_open()) {
        cout << "Error: Inventory file \"" << invFile << "\" not found." << endl;
        exit(EXIT_FAILURE);
    }

    getline(infile, line); // Skip header

    cout << setw(20) << left << "Item ID"
         << setw(20) << left << "Item Name"
         << setw(20) << left << "Quantity"
         << setw(20) << left << "Price Per Item"
         << endl;

    while (infile >> inv.itemID >> inv.itemName >> inv.itemQuantity >> inv.itemPrice) {
        cout << setw(20) << left << inv.itemID
             << setw(20) << left << inv.itemName
             << setw(20) << left << inv.itemQuantity
             << setw(20) << left << inv.itemPrice
             << endl;
    }

    infile.close();
}
