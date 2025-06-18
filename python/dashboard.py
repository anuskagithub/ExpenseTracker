import pandas as pd
import dash
from dash import dcc, html
from dash.dependencies import Input, Output
import plotly.express as px

# Load data
def load_data():
    df = pd.read_csv('../data/expenses.csv', names=['Date', 'Category', 'Amount', 'Budget'])
    df['Date'] = pd.to_datetime(df['Date'])
    df['Month'] = df['Date'].dt.to_period('M').astype(str)
    return df

df = load_data()

app = dash.Dash(__name__)
app.title = "Personal Finance Dashboard"

app.layout = html.Div([
    html.H1("💸 Personal Finance Dashboard"),
    dcc.Dropdown(
        id='month',
        options=[{'label': m, 'value': m} for m in df['Month'].unique()],
        value=df['Month'].max(),
        style={'width': '300px'}
    ),
    dcc.Graph(id='bar-chart'),
    dcc.Graph(id='pie-chart')
])

@app.callback(
    [Output('bar-chart', 'figure'),
     Output('pie-chart', 'figure')],
    [Input('month', 'value')]
)
def update_charts(selected_month):
    df = load_data()
    filtered = df[df['Month'] == selected_month]

    bar = px.bar(filtered, x='Category', y='Amount', color='Category', title=f'Expenses by Category ({selected_month})')
    pie = px.pie(filtered, names='Category', values='Amount', title=f'Spending Breakdown ({selected_month})')
    
    return bar, pie

if __name__ == '__main__':
    app.run(debug=True)

