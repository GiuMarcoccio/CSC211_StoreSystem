#include "Store.hpp"

/*
    Inventory Update

    Author: Giuseppe Marcoccio

    Description:
    Subtracts the quantity of each item ordered from the current inventory.
    Reads both the order file and inventory file, updates the inventory,
    and writes the new inventory back to file.
*/

void Store::inventoryUpdate(string orderFile, string invFile) {
    vector<Store> store;         // Stores order data
    vector<Store> inventory;     // Stores inventory data
    int indexOrdVector = 0, indexInvVector = 0;
    Order order;
    StoreInventory inv;

    ifstream inOrderfile(orderFile), inInvfile(invFile);
    string line;

    if (inOrderfile.is_open() && inInvfile.is_open()) {
        getline(inOrderfile, line); // Skip headers
        getline(inInvfile, line);   // Skip headers

        while (!inOrderfile.eof() && !inInvfile.eof()) {
            // Read order data
            inOrderfile >> order.itemOrderedID >> order.itemOrderedName >> order.itemOrderedQuantity;
            store.emplace(store.begin() + indexOrdVector, order.itemOrderedName, order.itemOrderedQuantity);
            indexOrdVector++;

            // Read inventory data and subtract ordered quantity
            inInvfile >> inv.itemID >> inv.itemName >> inv.itemQuantity >> inv.itemPrice;
            inventory.emplace(
                inventory.begin() + indexInvVector,
                inv.itemID,
                inv.itemName,
                inv.itemQuantity - order.itemOrderedQuantity,
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

    // Write updated inventory back to file
    ofstream outFile(invFile, ios::out);
    if (outFile.is_open()) {
        outFile << setw(25) << left << "Item ID Ordered"
                << setw(25) << left << "Item Name Ordered"
                << setw(25) << left << "Item Quantity Ordered"
                << setw(25) << left << "Item Price Ordered" << endl;

        for (const auto& elementInv : inventory) {
            outFile << setw(25) << elementInv.getItemID()
                    << setw(25) << elementInv.getName()
                    << setw(25) << elementInv.getUnits()
                    << setw(25) << elementInv.getRetailPrice() << endl;
        }
    } else {
        cout << "Error: Could not write to file \"" << invFile << "\"." << endl;
    }

    outFile.close();
}
