#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <conio.h>
#include <ctime>
#include <stdio.h>
#include <windows.h>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <iomanip>
#include <cstdlib>
#include <limits>
#include <locale>

using namespace std;

class Transaction
{
public:
    string date;
    double amount;
    string type;
    string description;

    Transaction(string date, double amount, string type, string description)
    {
        this->date = date;
        this->amount = amount;
        this->type = type;
        this->description = description;
    }
};

const string COLOR_RED = "\033[1;32m"; // Green color
const string COLOR_RESET = "\033[0m";

void PrintTitle()
{
    cout << COLOR_RED << R"(
  ____                _                  _     ____                _       _         
 |  _ \              | |                | |   |  _ \              | |     | |        
 | |_) |  _   _    __| |   __ _    ___  | |_  | |_) |  _   _    __| |   __| |  _   _ 
 |  _ <  | | | |  / _` |  / _` |  / _ \ | __| |  _ <  | | | |  / _` |  / _` | | | | |
 | |_) | | |_| | | (_| | | (_| | |  __/ | |_  | |_) | | |_| | | (_| | | (_| | | |_| |
 |____/   \__,_|  \__,_|  \__, |  \___|  \__| |____/   \__,_|  \__,_|  \__,_|  \__, |
                           __/ |                                                __/ |
                          |___/                                                |___/ 
    )" << COLOR_RESET
         << endl;
}

class Expense
{
public:
    string date;
    double amount;
    string type;
    string description;
    string category;

    Expense(string date, double amount, string type, string description, string category)
    {
        this->date = date;
        this->amount = amount;
        this->type = type;
        this->description = description;
        this->category = category;
    }
};

class Investment
{
public:
    string date;
    double amount;
    string type;
    string description;

    Investment(string date, double amount, string type, string description)
    {
        this->date = date;
        this->amount = amount;
        this->type = type;
        this->description = description;
    }
};

class Savings
{
public:
    string date;
    double amount;
    string type;
    string description;

    Savings(string date, double amount, string type, string description)
    {
        this->date = date;
        this->amount = amount;
        this->type = type;
        this->description = description;
    }
};

class User
{
public:
    string name;
    string email;
    string password;
    double income;
    double budget;

    User() {}

    User(string name, string email, string password, double income, double budget)
    {
        this->name = name;
        this->email = email;
        this->password = password;
        this->income = income;
        this->budget = budget;
    }
};

class FileManager
{
public:
    static void writeUserToFile(User user, string filename)
    {
        ofstream file(filename, ios::app); // Use ios::app to append to the file
        file << user.name << "," << user.email << "," << user.password << "," << user.income << "," << user.budget << endl;
        file.close();
    }

    static User readUserFromFile(string filename)
    {
        User user;
        ifstream file(filename);
        if (file.is_open())
        {
            string line;
            getline(file, line);
            stringstream ss(line);
            getline(ss, user.name, ',');
            getline(ss, user.email, ',');
            getline(ss, user.password, ',');
            ss >> user.income;
            ss.ignore();
            ss >> user.budget;
            file.close();
        }
        return user;
    }

    static void writeTransactionsToFile(vector<Transaction> transactions, string filename)
    {
        ofstream file(filename);
        for (Transaction transaction : transactions)
        {
            file << transaction.date << "," << transaction.amount << "," << transaction.type << "," << transaction.description << endl;
        }
        file.close();
    }

    static void writeExpensesToFile(vector<Expense> expenses, string filename)
    {
        ofstream file(filename);
        for (Expense expense : expenses)
        {
            file << expense.date << "," << expense.amount << "," << expense.type << "," << expense.description << "," << expense.category << endl;
        }
        file.close();
    }

    static void writeInvestmentsToFile(vector<Investment> investments, string filename)
    {
        ofstream file(filename);
        for (Investment investment : investments)
        {
            file << investment.date << "," << investment.amount << "," << investment.type << "," << investment.description << endl;
        }
        file.close();
    }

    static void writeSavingsToFile(vector<Savings> savings, string filename)
    {
        ofstream file(filename);
        for (Savings saving : savings)
        {
            file << saving.date << "," << saving.amount << "," << saving.type << "," << saving.description << endl;
        }
        file.close();
    }
};

class BudgetBuddy
{
private:
    User currentUser;
    vector<Transaction> transactions;
    vector<Expense> expenses;
    vector<Investment> investments;
    vector<Savings> savings;
    bool loggedIn;

public:
    BudgetBuddy()
    {
        loggedIn = false;
    }

    void registerUser(string name, string email, string password, double income, double budget)
    {
        currentUser = User(name, email, password, income, budget);
        FileManager::writeUserToFile(currentUser, "user.csv");
    }

    bool loginUser(string email, string password)
    {
        User user = FileManager::readUserFromFile("user.csv");
        if (user.email == email && user.password == password)
        {
            currentUser = user;
            loggedIn = true;
            return true;
        }
        return false;
    }

    void logoutUser()
    {
        loggedIn = false;
    }
    User getCurrentUser()
    {
        return currentUser;
    }

    void setIncome(double income)
    {
        cout << "\033[1;34m";
        if (!loggedIn)
        {
            cout << "Please log in to perform this action." << endl;
            return;
        }
        cout << "\033[0m";
        currentUser.income = income;
        FileManager::writeUserToFile(currentUser, "user.csv");
    }

    void setBudget(double budget)
    {
        cout << "\033[1;34m";
        if (!loggedIn)
        {
            cout << "Please log in to perform this action." << endl;
            return;
        }
        cout << "\033[0m";
        currentUser.budget = budget;
        FileManager::writeUserToFile(currentUser, "user.csv");
    }

    void addTransaction(string date, double amount, string type, string description)
    {
        cout << "\033[1;34m";
        if (!loggedIn)
        {
            cout << "Please log in to perform this action." << endl;
            return;
        }
        cout << "\033[0m";
        transactions.push_back(Transaction(date, amount, type, description));
        FileManager::writeTransactionsToFile(transactions, "transactions.txt");
    }

    void addExpense(string date, double amount, string type, string description, string category)
    {
        cout << "\033[1;34m";
        if (!loggedIn)
        {
            cout << "Please log in to perform this action." << endl;
            return;
        }
        cout << "\033[0m";
        expenses.push_back(Expense(date, amount, type, description, category));
        FileManager::writeExpensesToFile(expenses, "expenses.txt");
    }

    void addInvestment(string date, double amount, string type, string description)
    {
        cout << "\033[1;34m";
        if (!loggedIn)
        {
            cout << "Please log in to perform this action." << endl;
            return;
        }
        cout << "\033[0m";
        investments.push_back(Investment(date, amount, type, description));
        FileManager::writeInvestmentsToFile(investments, "investments.txt");
    }

    void addSavings(string date, double amount, string type, string description)
    {
        cout << "\033[1;34m";
        if (!loggedIn)
        {
            cout << "Please log in to perform this action." << endl;
            return;
        }
        savings.push_back(Savings(date, amount, type, description));
        FileManager::writeSavingsToFile(savings, "savings.txt");
    }

    void viewTransactions()
    {
        cout << "\033[1;34m";
        if (!loggedIn)
        {
            cout << "Please log in to perform this action." << endl;
            return;
        }
        cout << "Date\t\tAmount\tType\tDescription" << endl;
        cout << "\033[0m";
        for (Transaction transaction : transactions)
        {
            cout << "\033[1;34m";
            cout << transaction.date << "\t" << transaction.amount << "\t" << transaction.type << "\t" << transaction.description << endl;
            cout << "\033[0m";
        }
        cout << "\033[0m";
    }

    void viewExpenses()
    {
        cout << "\033[1;34m";
        if (!loggedIn)
        {
            cout << "Please log in to perform this action." << endl;
            return;
        }
        cout << "Date\tAmount\t\tType\tDescription\tCategory" << endl;
        cout << "\033[0m";
        for (Expense expense : expenses)
        {
            cout << "\033[1;34m";
            cout << expense.date << "\t" << expense.amount << "\t" << expense.type << "\t" << expense.description << "\t" << expense.category << endl;
            cout << "\033[0m";
        }
        cout << "\033[0m";
    }

    void viewInvestments()
    {
        cout << "\033[1;34m";
        if (!loggedIn)
        {
            cout << "Please log in to perform this action." << endl;
            return;
        }

        cout << "Date\t\tAmount\tType\tDescription" << endl;
        for (Investment investment : investments)
        {
            cout << "\033[1;34m";
            cout << investment.date << "\t" << investment.amount << "\t" << investment.type << "\t" << investment.description << endl;
            cout << "\033[0m";
        }
        cout << "\033[0m";
    }

    void viewSavings()
    {
        cout << "\033[1;34m";
        if (!loggedIn)
        {
            cout << "Please log in to perform this action." << endl;
            return;
        }

        cout << "Date\t\tAmount\tType\tDescription" << endl;

        for (Savings saving : savings)
        {
            cout << "\033[1;34m";
            cout << saving.date << "\t" << saving.amount << "\t" << saving.type << "\t" << saving.description << endl;
            cout << "\033[0m";
        }
        cout << "\033[0m";
    }
};
void printmenu()
{
    // cout << "\033[2;5;34m"; // set text to bold and increase font size
    cout << "\033[1;34m";
    cout << setw(40) << "\t\t\t\t\t-----------------------------------------\t\t\t\t\t\t" << endl;
    cout << setw(40) << "\t\t\t\t\t|          BUDGET BUDDY MENU            |\t\t\t\t\t\t" << endl;
    cout << setw(40) << "\t\t\t\t\t-----------------------------------------" << endl;
    cout << setw(40) << "\t\t\t\t\t| 1. Set Income                         |" << endl;
    cout << setw(40) << "\t\t\t\t\t| 2. Set Budget                         |" << endl;
    cout << setw(40) << "\t\t\t\t\t| 3. Add Transaction                    |" << endl;
    cout << setw(40) << "\t\t\t\t\t| 4. Add Expense                        |" << endl;
    cout << setw(40) << "\t\t\t\t\t| 5. Add Investment                     |" << endl;
    cout << setw(40) << "\t\t\t\t\t| 6. Add Savings                        |" << endl;
    cout << setw(40) << "\t\t\t\t\t| 7. View Transactions                  |" << endl;
    cout << setw(40) << "\t\t\t\t\t| 8. View Expenses                      |" << endl;
    cout << setw(40) << "\t\t\t\t\t| 9. View Investments                   |" << endl;
    cout << setw(40) << "\t\t\t\t\t| 10. View Savings                      |" << endl;
    cout << setw(40) << "\t\t\t\t\t| 11. Exit                              |" << endl;
    cout << setw(40) << "\t\t\t\t\t-----------------------------------------" << endl;
    cout << "Enter your choice: ";
    cout << "\033[0m";
}
User currentUser;

int main()
{
    BudgetBuddy budgetBuddy;
    int choice;
    string name, email, password, date, type, description, category;
    double income, budget, amount;

    bool loggedIn = false; // Flag to check if the user is logged in

    system("cls");
    char title[] = "\033[1;36m\t\t\t\t\t-----------------------------------------\n\t\t\t\t\t\t      BUDGET BUDDY\n\t\t\t\t\t-----------------------------------------\033[0m";
    char *ptr = title;
    for (int i = 0; i < sizeof(title); i++)
    {
        cout << *(ptr + i);
        Sleep(10);
    }

    PrintTitle();

    while (!loggedIn)
    {
        cout << "\033[1;34m"; // set text color to blue
        cout << "Welcome to BudgetBuddy!" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "\033[0m";

        switch (choice)
        {
        case 1:
        {
            string name;
            double income, budget;
            cout << "\033[1;34m";
            cout << "Enter your name: ";
            cin >> name;
            cout << "Enter your email: ";
            cin >> email;
            cout << "Enter your password: ";
            cin >> password;
            cout << "Enter your income: ";
            cin >> income;
            cout << "Enter your budget: ";
            cin >> budget;
            budgetBuddy.registerUser(name, email, password, income, budget);
            cout << "Registration successful!\n";
            cout << "\033[0m";

            break;
        }
        case 2:
        {
            cout << "\033[1;34m";
            cout << "Enter your email: ";
            cin >> email;
            cout << "Enter your password: ";
            cin >> password;
            if (budgetBuddy.loginUser(email, password))
            {
                loggedIn = true;
                currentUser = budgetBuddy.getCurrentUser();
                cout << "Login successful!" << endl;

                // Display user's information
                cout << "Logged in as: " << currentUser.name << endl;
                cout << "Income: " << currentUser.income << endl;
                cout << "Budget: " << currentUser.budget << endl;
            }
            else
            {
                cout << "Invalid email or password. Please try again." << endl;
            }
            break;
            cout << "\033[0m";
        }
        case 3:
        {
            cout << "\033[1;34m";
            cout << "Goodbye!" << endl;
            return 0;
            cout << "\033[0m";
        }
        default:
            cout << "\033[1;34m";
            cout << "Invalid choice. Please try again." << endl;
            cout << "\033[0m";

            break;
        }
    }

    do
    {

        printmenu();
        cout << "\033[1;34m";
        cin >> choice;
        cout << "\033[0m";

        switch (choice)
        {
        case 1:
        {
            cout << "\033[1;34m";
            double income;
            cout << "Enter your income: ";
            cin >> income;
            budgetBuddy.setIncome(income);
            cout << "\033[0m";
            break;
        }
        case 2:
        {
            cout << "\033[1;34m";
            double budget;
            cout << "Enter your budget: ";
            cin >> budget;
            budgetBuddy.setBudget(budget);
            cout << "\033[0m";
            break;
        }
        case 3:
            cout << "\033[1;34m";
            cout << "Enter the date: ";
            cin >> date;
            cout << "Enter the amount: ";
            cin >> amount;
            cout << "Enter the type: ";
            cin >> type;
            cout << "Enter the description: ";
            cout << "\033[0m";
            cin >> description;
            budgetBuddy.addTransaction(date, amount, type, description);
            break;
        case 4:
            cout << "\033[1;34m";
            cout << "Enter the date: ";
            cin >> date;
            cout << "Enter the amount: ";
            cin >> amount;
            cout << "Enter the type: ";
            cin >> type;
            cout << "Enter the description: ";
            cin >> description;
            cout << "Enter the category: ";
            cout << "\033[0m";
            cin >> category;
            budgetBuddy.addExpense(date, amount, type, description, category);
            break;
        case 5:
            cout << "\033[1;34m";
            cout << "Enter the date: ";
            cin >> date;
            cout << "Enter the amount: ";
            cin >> amount;
            cout << "Enter the type: ";
            cin >> type;
            cout << "Enter the description: ";
            cout << "\033[0m";
            cin >> description;
            budgetBuddy.addInvestment(date, amount, type, description);
            break;
        case 6:
            cout << "\033[1;34m";
            cout << "Enter the date: ";
            cin >> date;
            cout << "Enter the amount: ";
            cin >> amount;
            cout << "Enter the type: ";
            cin >> type;
            cout << "Enter the description: ";
            cout << "\033[0m";
            cin >> description;
            budgetBuddy.addSavings(date, amount, type, description);
            break;
        case 7:
            budgetBuddy.viewTransactions();
            break;
        case 8:
            budgetBuddy.viewExpenses();
            break;
        case 9:
            budgetBuddy.viewInvestments();
            break;
        case 10:
            budgetBuddy.viewSavings();
            break;
        case 11:
            cout << "\033[1;34m";
            cout << "Goodbye!" << endl;
            cout << "\033[0m";
            break;
        default:
            cout << "\033[1;34m";
            cout << "Invalid choice. Please try again." << endl;
            cout << "\033[0m";
            break; // reset text color
        }
    } while (choice != 11);
    return 0;
}
