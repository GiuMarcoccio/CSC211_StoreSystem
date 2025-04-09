#include "Store.hpp"

void Store::generateReceipt(string orderFile, string invFile, string outFile) {
    vector<Store> inventory;
    int index = 0;
    Order order;
    StoreInventory inv;

    ifstream inOrderfile(orderFile), inInvfile(invFile);
    string line;

    if (inOrderfile.is_open() && inInvfile.is_open()) {
        getline(inOrderfile, line);
        getline(inInvfile, line);

        cout << setw(25) << left <<"Item ID Ordered";
        cout << setw(25) << left <<"Item Name Ordered";
        cout << setw(25) << left <<"Item Quantity Ordered";
        cout << setw(25) << left <<"Item Price Ordered" << endl;

        while (!inOrderfile.eof() && !inInvfile.eof()) {
            inOrderfile >> order.itemOrderedID >> order.itemOrderedName >> order.itemOrderedQuantity;
            inInvfile >> inv.itemID >> inv.itemName >> inv.itemQuantity >> inv.itemPrice;

            inventory.emplace(inventory.begin() + index, inv.itemID, inv.itemName, order.itemOrderedQuantity, inv.itemPrice);
            index++;
        }
    } else {
        cout << "Error: Could not open \"" << orderFile << "\" or \"" << invFile << "\"." << endl;
        return;
    }

    inOrderfile.close();
    inInvfile.close();

    // Calculate totals and show on screen
    subTotal = 0;
    for (auto& item : inventory) {
        cout << setw(25) << item.getItemID();
        cout << setw(25) << item.getName();
        cout << setw(25) << item.getUnits();
        cout << setw(25) << item.getRetailPrice() << endl;
        subTotal += item.getUnits() * item.getRetailPrice();
    }

    tax = subTotal * (TAXNYC * 0.01);
    total = subTotal + tax;

    cout << string(90, '-') << endl;
    cout << setw(25) << "Sub-total: $" << setw(25) << subTotal << endl;
    cout << setw(25) << "Tax: $" << setw(25) << tax << endl;
    cout << string(90, '-') << endl;
    cout << setw(25) << "Total: $" << setw(25) << total << endl;

    // Export to file
    ofstream outfile(outFile);
    if (outfile.is_open()) {
        outfile << string(40, '*') << endl;
        outfile << "******  S T O R E  R E C E I P T  ******" << endl;
        outfile << string(40, '*') << endl;

        outfile << setw(20) << left << "Item Name" << setw(20) << "Quantity" << endl;
        for (auto& item : inventory) {
            outfile << setw(20) << item.getName() << setw(20) << item.getUnits() << endl;
        }

        outfile << string(40, '-') << endl;
        outfile << setw(20) << "Sub-total: $" << setw(20) << subTotal << endl;
        outfile << setw(20) << "Tax: $" << setw(20) << tax << endl;
        outfile << string(40, '-') << endl;
        outfile << setw(20) << "Total: $" << setw(20) << total << endl;
        outfile << string(40, '*') << endl;
    }

    outfile.close();
}
