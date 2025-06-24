#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <map>
#include <cmath>
#include <stdexcept>
#include <random>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

struct Expense {
    string date;
    string category;
    float amount;
    float budget;
};

// Read expenses from file
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

        if (date.empty() || category.empty() || amountStr.empty()) continue;

        Expense e = {date, category, stof(amountStr), budgetStr.empty() ? 0.0f : stof(budgetStr)};
        expenses.push_back(e);
    }
    return expenses;
}

// Write expenses to file
void writeExpenses(const vector<Expense> &expenses, const string &filename) {
    ofstream file(filename);
    for (const auto &e : expenses) {
        file << e.date << "," << e.category << "," << e.amount << "," << e.budget << endl;
    }
}

// Get today's date as YYYY-MM-DD
string getTodayDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char date[11];
    strftime(date, sizeof(date), "%Y-%m-%d", ltm);
    return string(date);
}

// Add an expense
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

// View all expenses
void viewExpenses(const vector<Expense> &expenses) {
    cout << "\n--- All Expenses ---\n";
    cout << left << setw(12) << "Date" << setw(15) << "Category" << setw(10) << "Amount" << "Budget\n";
    int idx = 1;
    for (const auto &e : expenses) {
        cout << left << setw(3) << idx++ << setw(12) << e.date << setw(15) << e.category
             << setw(10) << e.amount << e.budget << endl;
    }
}

// Filter expenses by category
void filterByCategory(const vector<Expense> &expenses) {
    string cat;
    cout << "Enter category to filter: ";
    cin >> cat;
    cout << "\n--- Expenses in " << cat << " ---\n";
    int found = 0;
    for (const auto &e : expenses) {
        if (e.category == cat) {
            cout << e.date << " - ₹" << e.amount << endl;
            found++;
        }
    }
    if (found == 0)
        cout << "No expenses found in this category.\n";
}

// Show spending summary
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
        cout << "Budget not set or zero for some expenses.\n";
}

// Delete expense
void deleteExpense(vector<Expense> &expenses, const string &filename) {
    viewExpenses(expenses);
    int index;
    cout << "\nEnter expense number to delete (1 to " << expenses.size() << "): ";
    cin >> index;
    if (index >= 1 && index <= (int)expenses.size()) {
        expenses.erase(expenses.begin() + index - 1);
        writeExpenses(expenses, filename);
        cout << "✅ Deleted successfully.\n";
    } else {
        cout << "❌ Invalid index.\n";
    }
}

// === Linear Algebra Support ===
using Matrix = vector<vector<double>>;

Matrix transpose(const Matrix &m) {
    size_t rows = m.size(), cols = m[0].size();
    Matrix t(cols, vector<double>(rows));
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            t[j][i] = m[i][j];
    return t;
}

Matrix multiply(const Matrix &a, const Matrix &b) {
    size_t a_rows = a.size(), a_cols = a[0].size();
    size_t b_rows = b.size(), b_cols = b[0].size();
    if (a_cols != b_rows)
        throw runtime_error("Matrix size mismatch for multiplication");
    Matrix c(a_rows, vector<double>(b_cols, 0.0));
    for (size_t i = 0; i < a_rows; i++)
        for (size_t j = 0; j < b_cols; j++)
            for (size_t k = 0; k < a_cols; k++)
                c[i][j] += a[i][k] * b[k][j];
    return c;
}

Matrix inverse2x2(const Matrix &m) {
    if (m.size() != 2 || m[0].size() != 2)
        throw runtime_error("Only 2x2 matrices supported for inversion");

    double det = m[0][0] * m[1][1] - m[0][1] * m[1][0];
    if (det == 0)
        throw runtime_error("Matrix is singular and cannot be inverted");

    double invdet = 1.0 / det;
    Matrix inv(2, vector<double>(2));
    inv[0][0] =  m[1][1] * invdet;
    inv[0][1] = -m[0][1] * invdet;
    inv[1][0] = -m[1][0] * invdet;
    inv[1][1] =  m[0][0] * invdet;
    return inv;
}

// Linear Regression to predict next month's expense
void predictNextMonthExpense(const vector<Expense> &expenses) {
    if(expenses.empty()){
        cout << "No expenses data available.\n";
        return;
    }

    map<string, float> monthlyTotals;
    for (const auto &e : expenses) {
        if(e.date.size() < 7) continue;
        string month = e.date.substr(0, 7);
        monthlyTotals[month] += e.amount;
    }

    if (monthlyTotals.size() < 2) {
        cout << "Not enough data to predict (need at least 2 months).\n";
        return;
    }

    vector<double> x;
    vector<double> y;
    int idx = 1;
    for (const auto &entry : monthlyTotals) {
        x.push_back(idx++);
        y.push_back(entry.second);
    }

    Matrix X(x.size(), vector<double>(2, 1.0));
    for (size_t i = 0; i < x.size(); i++)
        X[i][1] = x[i];

    Matrix Y(y.size(), vector<double>(1));
    for (size_t i = 0; i < y.size(); i++)
        Y[i][0] = y[i];

    try {
        auto Xt = transpose(X);
        auto XtX = multiply(Xt, X);
        auto XtX_inv = inverse2x2(XtX);
        auto XtY = multiply(Xt, Y);
        auto B = multiply(XtX_inv, XtY);

        double intercept = B[0][0];
        double slope = B[1][0];

        int nextMonth = x.back() + 1;
        double predictedExpense = intercept + slope * nextMonth;

        cout << "\n--- Expense Prediction using Linear Regression ---\n";
        cout << "Regression line: expense = " << intercept << " + " << slope << " * month_index\n";
        cout << "Predicted expense for next month (month index " << nextMonth << ") = ₹" << predictedExpense << "\n";
    }
    catch (const exception &e) {
        cout << "Error in linear regression: " << e.what() << endl;
    }
}


string toLower(const string& s) {
    string result = s;
    for (char &ch : result) ch = tolower(ch);
    return result;
}

// Show probability distribution of categories
void showCategoryProbabilities(const vector<Expense> &expenses) {
    if (expenses.empty()) {
        cout << "No expenses to analyze.\n";
        return;
    }

    map<string, int> categoryCount;
    int total = 0;

    for (const auto &e : expenses) {
        categoryCount[e.category]++;
        total++;
    }

    cout << "\n--- Probability Distribution of Expense Categories ---\n";
    cout << left << setw(15) << "Category" << "Probability (%)\n";
    for (const auto &pair : categoryCount) {
        double prob = (double(pair.second) / total) * 100;
        cout << left << setw(15) << pair.first << fixed << setprecision(2) << prob << "%\n";
    }
}

// Show mean, variance, std deviation
void showExpenseStats(const vector<Expense> &expenses) {
    if (expenses.empty()) {
        cout << "No expenses to analyze.\n";
        return;
    }

    double sum = 0.0;
    for (const auto &e : expenses)
        sum += e.amount;

    double mean = sum / expenses.size();

    double variance = 0.0;
    for (const auto &e : expenses)
        variance += pow(e.amount - mean, 2);

    variance /= expenses.size();
    double stddev = sqrt(variance);

    cout << "\n--- Expense Statistics ---\n";
    cout << "Expected Value (Mean): ₹" << fixed << setprecision(2) << mean << "\n";
    cout << "Variance: " << fixed << setprecision(2) << variance << "\n";
    cout << "Standard Deviation: " << fixed << setprecision(2) << stddev << "\n";
}

void kmeansClustering(const vector<Expense>& expenses) {
    if (expenses.empty()) {
        cout << "No expenses to analyze.\n";
        return;
    }

    // Aggregate total amount per month
    map<string, float> monthlyTotals;
    for (const auto &e : expenses) {
        if (e.date.size() >= 7) {
            string month = e.date.substr(0, 7);
            monthlyTotals[month] += e.amount;
        }
    }

    vector<double> data;
    for (const auto &entry : monthlyTotals) {
        data.push_back(entry.second);
    }

    if (data.size() < 3) {
        cout << "Not enough data for clustering (need at least 3 months).\n";
        return;
    }

    // KMeans clustering for k = 3 (Frugal, Balanced, Overspender)
    int k = 3;
    vector<double> centroids = {1000, 5000, 10000}; // initial guesses

    vector<int> labels(data.size(), 0);
    bool changed;

    for (int iter = 0; iter < 100; ++iter) {
        changed = false;

        // Assign labels
        for (size_t i = 0; i < data.size(); ++i) {
            double minDist = abs(data[i] - centroids[0]);
            int label = 0;
            for (int j = 1; j < k; ++j) {
                double dist = abs(data[i] - centroids[j]);
                if (dist < minDist) {
                    minDist = dist;
                    label = j;
                }
            }
            if (labels[i] != label) {
                labels[i] = label;
                changed = true;
            }
        }

        // Update centroids
        vector<double> sums(k, 0);
        vector<int> counts(k, 0);
        for (size_t i = 0; i < data.size(); ++i) {
            sums[labels[i]] += data[i];
            counts[labels[i]]++;
        }
        for (int j = 0; j < k; ++j) {
            if (counts[j] != 0)
                centroids[j] = sums[j] / counts[j];
        }

        if (!changed) break;
    }

    // Classify the latest month
    int lastIdx = data.size() - 1;
    int lastLabel = labels[lastIdx];

    string type;
    if (lastLabel == 0) type = "Frugal";
    else if (lastLabel == 1) type = "Balanced";
    else type = "Overspender";

    cout << "\n--- Spending Behavior Classification ---\n";
    cout << "You are classified as: 🔎 " << type << " spender (based on last " << data.size() << " months)\n";
}

// Predict expense category using Naive Bayes Classifier
void predictCategoryNaiveBayes(const vector<Expense> &expenses) {
    if (expenses.empty()) {
        cout << "Not enough data.\n";
        return;
    }

    // Group amounts by category
    map<string, vector<double>> categoryAmounts;
    for (const auto &e : expenses) {
        categoryAmounts[e.category].push_back(e.amount);
    }

    // Compute priors and Gaussian parameters
    map<string, double> priors;
    map<string, double> mean, variance;
    int total = expenses.size();

    for (const auto &pair : categoryAmounts) {
        string category = pair.first;
        const auto &amounts = pair.second;
        priors[category] = (double)amounts.size() / total;

        double sum = 0;
        for (double a : amounts) sum += a;
        mean[category] = sum / amounts.size();

        double var = 0;
        for (double a : amounts) var += pow(a - mean[category], 2);
        variance[category] = var / amounts.size();
    }

    // Ask user for new expense amount
    double inputAmount;
    cout << "Enter new expense amount: ₹";
    cin >> inputAmount;

    // Compute posterior probabilities
    string bestCategory;
    double maxProb = -1;

    for (const auto &pair : priors) {
        string category = pair.first;
        double prior = pair.second;
        double mu = mean[category];
        double var = variance[category];

        // Avoid divide by zero
        if (var == 0) var = 1e-6;

        double likelihood = (1.0 / sqrt(2 * M_PI * var)) * exp(-pow(inputAmount - mu, 2) / (2 * var));
        double posterior = prior * likelihood;

        if (posterior > maxProb) {
            maxProb = posterior;
            bestCategory = category;
        }
    }

    cout << "🔍 Predicted category: **" << bestCategory << "**\n";
}


int main() {
    const string filename = "../data/expenses.csv"; // update path if needed
    int choice;

    do {
        vector<Expense> expenses = readExpenses(filename);
        cout << "\n--- Personal Finance Tracker ---\n";
        cout << "1. Add Expense\n";
        cout << "2. View All Expenses\n";
        cout << "3. Filter by Category\n";
        cout << "4. Show Spending Summary\n";
        cout << "5. Delete Expense\n";
        cout << "6. Predict Next Month Expense\n";
        cout << "7. Show Category Probabilities\n";
        cout << "8. Show Expense Statistics\n";
        cout << "9. Classify Spending Habit (AI)\n";
        cout << "10. Predict Category using Naive Bayes\n";
        cout << "11. Exit\n";
        cout << "Choose option: ";
        cin >> choice;

        switch (choice) {
            case 1: addExpense(filename); break;
            case 2: viewExpenses(expenses); break;
            case 3: filterByCategory(expenses); break;
            case 4: spendingSummary(expenses); break;
            case 5: deleteExpense(expenses, filename); break;
            case 6: predictNextMonthExpense(expenses); break;
            case 7: showCategoryProbabilities(expenses); break;
            case 8: showExpenseStats(expenses); break;
            case 9: kmeansClustering(expenses); break;
            case 10: predictCategoryNaiveBayes(expenses); break;
            case 11: cout << "Goodbye!\n"; break;
            default: cout << "❌ Invalid option.\n";
        }
    } while (choice != 9);

    return 0;
}
