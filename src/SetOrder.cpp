#include "Store.hpp"

/*
    Set Order

    Author: Giuseppe Marcoccio

    Description:
    Reads and displays the user's order from a given file.
    Each order line includes item ID, item name, and quantity ordered.
*/

void Store::setOrder(string orderFile) {
    Order order;
    ifstream infile(orderFile);
    string line;

    if (!infile.is_open()) {
        cout << "Error: Order file \"" << orderFile << "\" not found.\n";
        return;
    }

    // Skip header
    getline(infile, line);

    cout << setw(20) << left << "Item ID Ordered"
         << setw(20) << left << "Item Name Ordered"
         << setw(20) << left << "Quantity Ordered" << endl;

    while (infile >> order.itemOrderedID >> order.itemOrderedName >> order.itemOrderedQuantity) {
        cout << setw(20) << left << order.itemOrderedID
             << setw(20) << left << order.itemOrderedName
             << setw(20) << left << order.itemOrderedQuantity << endl;
    }

    infile.close();
}
