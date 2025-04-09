//  Giuseppe Marcoccio
//  CSC 211 - 1900

#include <iostream>
#include <iomanip>
#include <map>
#include "Store.hpp"                

using namespace std;

void DisplayMenu();
map<int, string> mapOrder;
void mapOrderSet(int, string);
string mapOrderGet(int);

int main() {
    char option;
    string orderFile, sumOrderFile, addnewInv;
    int numKeyFile, oNum;

    cout << "\n\n\t\tWelcome to Giuseppe's Store" << endl;
    cout << "\n\nLoading Inventory...\n\n";

    Store store(0, "", 0, 0.0);
    store.displayInventory("data/Inventory.txt");


    do {
        cout << "\n\n";
        DisplayMenu();
        cin >> option;

        switch (tolower(option)) {
            case 'a':
                cout << "\nEnter the order file name: ";
                cin >> orderFile;
                cout << "Enter key number for this order: ";
                cin >> numKeyFile;
                mapOrderSet(numKeyFile, orderFile);
                cout << "\nLoading Order #" << numKeyFile << "...\n\n";
                store.setOrder(orderFile);
                break;

            case 'b':
                if (orderFile.empty()) {
                    cout << "\nError: Please select an order file first using option A.\n";
                } else {
                    cout << "\nCalculating totals...\n\n";
                    store.calculateOrder(orderFile, "data/Inventory.txt");
                }
                break;

                case 'c':
                if (orderFile.empty()) {
                    cout << "\nError: Please select an order file first using option A.\n";
                } else {
                    cout << "\nEnter Order Key #: ";
                    cin >> oNum;
                    cout << "Enter file name to export order summary: ";
                    cin >> sumOrderFile;
                    store.generateReceipt(mapOrderGet(oNum), "data/Inventory.txt", sumOrderFile);
                    cout << "\nOrder exported to: " << sumOrderFile << endl;
                }
                break;

            case 'd':
                cout << "\nCurrent Inventory:\n\n";
                store.displayInventory("data/Inventory.txt");
                break;

            case 'e':
                if (orderFile.empty()) {
                    cout << "\nError: Please select an order file first using option A.\n";
                } else {
                    cout << "Enter Order Key #: ";
                    cin >> oNum;
                    cout << "\nDisplaying Order #" << oNum << "...\n\n";
                    store.displayOrder(mapOrderGet(oNum));
                }
                break;

            case 'f':
                cout << "\nEnter the new order file name: ";
                cin >> orderFile;
                cout << "Enter key number for this order: ";
                cin >> numKeyFile;
                mapOrderSet(numKeyFile, orderFile);
                cout << "\nLoading new Order #" << numKeyFile << "...\n\n";
                store.setOrder(orderFile);
                break;

            case 'g':
                cout << "\nEnter the new inventory file name: ";
                cin >> addnewInv;
                cout << "\nAdding inventory...\n\n";
                store.addInventory("data/Inventory.txt", addnewInv);
                store.displayInventory("data/Inventory.txt");
                break;

            case 'h':
                cout << "\nProgram terminated. Goodbye!\n";
                return 0;

            default:
                cout << "\n'" << option << "' is not a valid option. Please choose A through H.\n";
        }

    } while (true);

    return 0;
}

void DisplayMenu() {
    cout << "\n========== MENU ==========\n";
    cout << "A. Read order from file\n";
    cout << "B. Calculate order total\n";
    cout << "C. Export order to file\n";
    cout << "D. Print current inventory\n";
    cout << "E. Display order by number\n";
    cout << "F. Load new order\n";
    cout << "G. Add inventory\n";
    cout << "H. Exit\n";
    cout << "==========================\n";
    cout << "Select option: ";
}

void mapOrderSet(int numKey, string numOrder) {
    mapOrder.insert({numKey, numOrder});
}

string mapOrderGet(int num) {
    if (mapOrder.count(num)) {
        return mapOrder.at(num);
    } else {
        cout << "Error: Invalid order key.\n";
        return "";
    }
}
