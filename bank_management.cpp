
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class Account {
public:
    int accNo;
    string name;
    double balance;
};

void createAccount() {
    Account a;

    cout << "\nEnter Account Number: ";
    cin >> a.accNo;
    cin.ignore();

    cout << "Enter Customer Name: ";
    getline(cin, a.name);

    cout << "Enter Initial Deposit: ";
    cin >> a.balance;

    ofstream file("bank_data.txt", ios::app);

    file << a.accNo << "|"
         << a.name << "|"
         << a.balance << endl;

    file.close();

    cout << "\nAccount Created Successfully!\n";
}

void displayAccounts() {
    ifstream file("bank_data.txt");

    string line;

    cout << "\n===== CUSTOMER RECORDS =====\n";

    while (getline(file, line)) {
        stringstream ss(line);

        string acc, name, bal;

        getline(ss, acc, '|');
        getline(ss, name, '|');
        getline(ss, bal, '|');

        cout << "\n----------------------";
        cout << "\nAccount No : " << acc;
        cout << "\nName       : " << name;
        cout << "\nBalance    : " << bal;
        cout << "\n----------------------";
    }

    file.close();
}

void checkBalance() {
    int accNo;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    ifstream file("bank_data.txt");

    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);

        string acc, name, bal;

        getline(ss, acc, '|');
        getline(ss, name, '|');
        getline(ss, bal, '|');

        if (stoi(acc) == accNo) {
            cout << "\nCustomer Name : " << name;
            cout << "\nCurrent Balance : ₹" << bal << endl;
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nAccount Not Found!\n";
}

void depositMoney() {
    int accNo;
    double amount;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    cout << "Enter Amount to Deposit: ";
    cin >> amount;

    ifstream file("bank_data.txt");

    vector<string> records;
    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);

        string acc, name, bal;

        getline(ss, acc, '|');
        getline(ss, name, '|');
        getline(ss, bal, '|');

        if (stoi(acc) == accNo) {
            double balance = stod(bal);
            balance += amount;

            line = acc + "|" + name + "|" + to_string(balance);
            found = true;
        }

        records.push_back(line);
    }

    file.close();

    ofstream out("bank_data.txt");

    for (string record : records)
        out << record << endl;

    out.close();

    if (found)
        cout << "\nDeposit Successful!\n";
    else
        cout << "\nAccount Not Found!\n";
}

void withdrawMoney() {
    int accNo;
    double amount;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    cout << "Enter Amount to Withdraw: ";
    cin >> amount;

    ifstream file("bank_data.txt");

    vector<string> records;
    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);

        string acc, name, bal;

        getline(ss, acc, '|');
        getline(ss, name, '|');
        getline(ss, bal, '|');

        if (stoi(acc) == accNo) {
            double balance = stod(bal);

            if (balance >= amount) {
                balance -= amount;
                line = acc + "|" + name + "|" + to_string(balance);
                cout << "\nWithdrawal Successful!\n";
            } else {
                cout << "\nInsufficient Balance!\n";
            }

            found = true;
        }

        records.push_back(line);
    }

    file.close();

    ofstream out("bank_data.txt");

    for (string record : records)
        out << record << endl;

    out.close();

    if (!found)
        cout << "\nAccount Not Found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n\n===== BANK MANAGEMENT SYSTEM =====";
        cout << "\n1. Create Account";
        cout << "\n2. Deposit Money";
        cout << "\n3. Withdraw Money";
        cout << "\n4. Check Balance";
        cout << "\n5. Display All Accounts";
        cout << "\n6. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                createAccount();
                break;

            case 2:
                depositMoney();
                break;

            case 3:
                withdrawMoney();
                break;

            case 4:
                checkBalance();
                break;

            case 5:
                displayAccounts();
                break;

            case 6:
                cout << "\nThank You!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while(choice != 6);

    return 0;
}
