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
│   └── expense_entry.cpp       # C++ source file (main CLI logic)
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
<img width="409" alt="image" src="https://github.com/user-attachments/assets/515916ef-3125-4f45-bc43-d62cc21929dd" />


### 📋 View All Expenses
<img width="331" alt="image" src="https://github.com/user-attachments/assets/49f72cda-44f4-4a40-9768-3acdef2c6f35" />

### 🧾 Spending Summary
<img width="322" alt="image" src="https://github.com/user-attachments/assets/8f68e1a3-5b48-420e-9401-10a91ec47e08" />

### 🔍 Filter By Category
<img width="318" alt="image" src="https://github.com/user-attachments/assets/200a1934-cbb5-4f73-9458-cf1eb321dac5" />


## 📊 Dashboard Preview

### 🖥️ Full Dashboard View
<img width="620" alt="image" src="https://github.com/user-attachments/assets/8f6595bf-6c1d-4e2f-a563-d6d4350f3e56" />






