#include "Store.hpp"

/*
    G. Add Inventory

    Author: Giuseppe Marcoccio
    Description:
    This function updates the inventory by combining current inventory data
    with additional inventory data from another file. The result is saved 
    back into the main inventory file.
*/

void Store::addInventory(string invFile, string addInvFile) {
    vector<Store> store;           // Stores current inventory orders
    vector<Store> inventory;       // Stores updated inventory
    int indexOrdVector = 0, indexInvVector = 0;
    Order order;                   // Struct for current orders
    StoreInventory inv;           // Struct for inventory items

    ifstream inInvFile(invFile);
    ifstream inAddInvfile(addInvFile);
    string line;

    if (inInvFile.is_open() && inAddInvfile.is_open()) {
        getline(inInvFile, line);      // Skip headers
        getline(inAddInvfile, line);   // Skip headers

        while (!inInvFile.eof() && !inAddInvfile.eof()) {
            // Read from current inventory
            inInvFile >> order.itemOrderedID >> order.itemOrderedName >> order.itemOrderedQuantity;
            store.emplace(store.begin() + indexOrdVector, order.itemOrderedName, order.itemOrderedQuantity);
            indexOrdVector++;

            // Read from additional inventory
            inAddInvfile >> inv.itemID >> inv.itemName >> inv.itemQuantity >> inv.itemPrice;
            inventory.emplace(
                inventory.begin() + indexInvVector,
                inv.itemID,
                inv.itemName,
                inv.itemQuantity + order.itemOrderedQuantity,  // Update quantity
                inv.itemPrice
            );
            indexInvVector++;
        }
    } else {
        cout << "Error: Could not open file \"" << invFile << "\" or \"" << addInvFile << "\"." << endl;
        return;
    }

    inInvFile.close();
    inAddInvfile.close();

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
