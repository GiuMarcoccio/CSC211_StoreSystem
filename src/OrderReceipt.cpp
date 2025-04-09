#include "Store.hpp"

/*
    C. Order Receipt Export

    Author: Giuseppe Marcoccio

    Description:
    Reads the order file, extracts item names and quantities,
    and writes a receipt-style summary to a new file including
    subtotal, tax, and total.
*/

void Store::orderReceipt(string orderFile, string sumOrderFile) {
    vector<Store> store;
    Order order;

    ifstream infile(orderFile);
    string line;

    if (!infile.is_open()) {
        cout << "Error: Order file \"" << orderFile << "\" not found." << endl;
        return;
    }

    getline(infile, line); // Skip header

    while (infile >> order.itemOrderedID >> order.itemOrderedName >> order.itemOrderedQuantity) {
        store.emplace_back(order.itemOrderedName, order.itemOrderedQuantity);
    }

    infile.close();

    ofstream outfile(sumOrderFile);
    if (!outfile.is_open()) {
        cout << "Error: Could not write to file \"" << sumOrderFile << "\"." << endl;
        return;
    }

    outfile << string(40, '*') << endl;
    outfile << "******  S T O R E  R E C E I P T  ******" << endl;
    outfile << string(40, '*') << endl;

    outfile << setw(20) << left << "Item Name"
            << setw(20) << left << "Quantity" << endl;

    for (const auto& element : store) {
        outfile << setw(20) << left << element.getName()
                << setw(20) << left << element.getUnits() << endl;
    }

    outfile << fixed << setprecision(2);
    outfile << string(40, '-') << endl;
    outfile << setw(20) << left << "Sub-total: $" << subTotal << endl;
    outfile << setw(20) << left << "Tax: $" << tax << endl;
    outfile << string(40, '-') << endl;
    outfile << setw(20) << left << "Total: $" << total << endl;
    outfile << string(40, '*') << endl << endl;

    outfile.close();
}
