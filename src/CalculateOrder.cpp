#include "Store.hpp"

/*
    B. Calculate Order

    Author: Giuseppe Marcoccio

    Description:
    Reads an order file and inventory file, calculates the subtotal for each item,
    applies NYC tax (8.875%), computes the grand total, and prints a receipt-style summary.
*/

void Store::calculateOrder(string orderFile, string invFile) {
    vector<Store> store;         // Order data vector
    vector<Store> inventory;     // Inventory vector
    int indexOrdVector = 0, indexInvVector = 0;
    Order order;
    StoreInventory inv;

    ifstream inOrderfile(orderFile), inInvfile(invFile);
    string line;

    if (inOrderfile.is_open() && inInvfile.is_open()) {
        getline(inOrderfile, line); // Skip headers
        getline(inInvfile, line);   // Skip headers

        cout << setw(25) << left << "Item ID Ordered"
             << setw(25) << left << "Item Name Ordered"
             << setw(25) << left << "Item Quantity Ordered"
             << setw(25) << left << "Item Price Ordered" << endl;

        while (!inOrderfile.eof() && !inInvfile.eof()) {
            // Read order data
            inOrderfile >> order.itemOrderedID >> order.itemOrderedName >> order.itemOrderedQuantity;
            store.emplace(store.begin() + indexOrdVector, order.itemOrderedName, order.itemOrderedQuantity);
            indexOrdVector++;

            // Read inventory data
            inInvfile >> inv.itemID >> inv.itemName >> inv.itemQuantity >> inv.itemPrice;
            inventory.emplace(
                inventory.begin() + indexInvVector,
                inv.itemID,
                inv.itemName,
                order.itemOrderedQuantity,   // override quantity with order
                inv.itemPrice
            );
            indexInvVector++;
        }

    } else {
        cout << "Error: Could not open \"" << orderFile << "\" or \"" << invFile << "\"." << endl;
        return;
    }

    inOrderfile.close();
    inInvfile.close();

    // Calculate and display receipt
    double subTotal = 0.0, tax = 0.0, total = 0.0;

    for (const auto& elementInv : inventory) {
        cout << setw(25) << elementInv.getItemID()
             << setw(25) << elementInv.getName()
             << setw(25) << elementInv.getUnits()
             << setw(25) << elementInv.getRetailPrice() << endl;

        subTotal += elementInv.getUnits() * elementInv.getRetailPrice();
    }

    tax = subTotal * (TAXNYC * 0.01);
    total = subTotal + tax;

    cout << setprecision(4);
    cout << string(90, '-') << endl;
    cout << setw(25) << "Sub-total: $" << subTotal << endl;
    cout << setw(25) << "Tax: $" << tax << endl;
    cout << string(90, '-') << endl;
    cout << setw(25) << "Total: $" << total << endl;

    // Update inventory after processing the order
    inventoryUpdate(orderFile, invFile);
}
