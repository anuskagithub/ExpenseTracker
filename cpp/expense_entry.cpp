#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <iomanip>
using namespace std;

struct Expense {
    string date;
    string category;
    float amount;
    float budget;
};

vector<Expense> readExpenses(const string &filename) {
    vector<Expense> expenses;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string date, category, amountStr, budgetStr;
        getline(ss, date, ',');
        getline(ss, category, ',');
        getline(ss, amountStr, ',');
        getline(ss, budgetStr, ',');

        Expense e = {date, category, stof(amountStr), stof(budgetStr)};
        expenses.push_back(e);
    }
    return expenses;
}

void writeExpenses(const vector<Expense> &expenses, const string &filename) {
    ofstream file(filename);
    for (const auto &e : expenses) {
        file << e.date << "," << e.category << "," << e.amount << "," << e.budget << endl;
    }
}

string getTodayDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char date[11];
    strftime(date, sizeof(date), "%Y-%m-%d", ltm);
    return string(date);
}

void addExpense(const string &filename) {
    Expense e;
    string choice;
    cout << "Use today's date? (y/n): ";
    cin >> choice;
    if (choice == "y" || choice == "Y") {
        e.date = getTodayDate();
    } else {
        cout << "Enter date (YYYY-MM-DD): ";
        cin >> e.date;
    }

    cout << "Enter category: ";
    cin >> e.category;
    cout << "Enter amount: ";
    cin >> e.amount;
    cout << "Enter monthly budget (optional, enter 0 if not applicable): ";
    cin >> e.budget;

    ofstream file(filename, ios::app);
    file << e.date << "," << e.category << "," << e.amount << "," << e.budget << endl;
    file.close();
    cout << "✅ Expense added successfully!\n";
}

void viewExpenses(const vector<Expense> &expenses) {
    cout << "\n--- All Expenses ---\n";
    cout << left << setw(12) << "Date" << setw(12) << "Category" << setw(10) << "Amount" << "Budget\n";
    for (const auto &e : expenses) {
        cout << left << setw(12) << e.date << setw(12) << e.category
             << setw(10) << e.amount << e.budget << endl;
    }
}

void filterByCategory(const vector<Expense> &expenses) {
    string cat;
    cout << "Enter category to filter: ";
    cin >> cat;
    cout << "\n--- Expenses in " << cat << " ---\n";
    for (const auto &e : expenses) {
        if (e.category == cat) {
            cout << e.date << " - " << e.amount << endl;
        }
    }
}

void spendingSummary(const vector<Expense> &expenses) {
    float total = 0, budget = 0;
    for (const auto &e : expenses) {
        total += e.amount;
        budget += e.budget;
    }
    cout << "\n--- Spending Summary ---\n";
    cout << "Total Spent: ₹" << total << "\n";
    if (budget > 0)
        cout << "Budget: ₹" << budget << " (" << ((total / budget) * 100) << "% used)\n";
    else
        cout << "Budget not set for some expenses.\n";
}

void deleteExpense(vector<Expense> &expenses, const string &filename) {
    viewExpenses(expenses);
    int index;
    cout << "\nEnter expense number to delete (1 to " << expenses.size() << "): ";
    cin >> index;
    if (index >= 1 && index <= expenses.size()) {
        expenses.erase(expenses.begin() + index - 1);
        writeExpenses(expenses, filename);
        cout << "✅ Deleted successfully.\n";
    } else {
        cout << "❌ Invalid index.\n";
    }
}

int main() {
    const string filename = "../data/expenses.csv";
    int choice;

    do {
        cout << "\n--- Personal Finance Tracker ---\n";
        cout << "1. Add Expense\n";
        cout << "2. View All Expenses\n";
        cout << "3. Filter by Category\n";
        cout << "4. Show Spending Summary\n";
        cout << "5. Delete Expense\n";
        cout << "6. Exit\n";
        cout << "Choose option: ";
        cin >> choice;

        vector<Expense> expenses = readExpenses(filename);

        switch (choice) {
            case 1: addExpense(filename); break;
            case 2: viewExpenses(expenses); break;
            case 3: filterByCategory(expenses); break;
            case 4: spendingSummary(expenses); break;
            case 5: deleteExpense(expenses, filename); break;
            case 6: cout << "Goodbye!\n"; break;
            default: cout << "❌ Invalid option.\n";
        }
    } while (choice != 6);

    return 0;
}
