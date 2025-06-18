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
<pre><code>## 📁 Project Structure ``` ExpenseTracker/ │ ├── cpp/ │ └── expense_advanced.cpp # C++ source file (main CLI logic) │ ├── python/ │ └── dashboard.py # Dash dashboard for visualization │ ├── data/ │ └── expenses.csv # CSV file storing expenses │ └── README.md # Project overview and instructions ``` </code></pre>
