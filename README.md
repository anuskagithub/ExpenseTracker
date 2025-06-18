# Personal Expense Tracker
Track your daily expenses from the command line using C++ and visualize your monthly spending with an interactive Python dashboard.

## 📌 Features
### 🖥️ C++ CLI Application
- Add expenses with date, category, amount, and monthly budget
- View all expenses
- Filter by category
- View total spending vs. budget
- Delete incorrect entries
- Stores data in `expenses.csv` (CSV format)

### 📊 Python Dashboard
- Reads data from the CSV file
- Displays interactive **bar** and **pie charts** using Dash & Plotly
- Launches a local server (`localhost:8050`) for real-time insights


## 📁 Project Structure
```
ExpenseTracker/
│
├── cpp/
│   └── expense_advanced.cpp       # C++ source file (main CLI logic)
│
├── python/
│   └── dashboard.py               # Dash dashboard for visualization
│
├── data/
│   └── expenses.csv               # CSV file storing expenses
```


## 📸 CLI Working Screenshots

<img width="271" src="https://github.com/user-attachments/assets/a8d4ca4a-9bd1-446c-86d9-7b0e20ad19c6" />

### ➕ Add Expense
<img width="422" src="https://github.com/user-attachments/assets/6f076b87-5182-4c26-917a-3efe837ee883" />

### 📋 View All Expenses
<img width="260" src="https://github.com/user-attachments/assets/2154ab69-875d-46a0-b5d9-c3f3a5372189" />

### 🧾 Spending Summary
<img width="283" src="https://github.com/user-attachments/assets/9b27c437-f78f-44bc-ac68-e22df009b1bf" />





