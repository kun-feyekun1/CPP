#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

// =============================
// Utility: Clear invalid input
// g++ bcd.cpp -o bcd.exe
// =============================
void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// =============================
// Main calculator operations
// =============================
double add(double a, double b) { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }
double divide(double a, double b)
{
    if (b == 0)
    {
        throw runtime_error("Error: Cannot divide by zero!");
    }
    return a / b;
}
double power(double base, double exp) { return pow(base, exp); }
double squareRoot(double num)
{
    if (num < 0)
    {
        throw runtime_error("Error: Cannot take square root of negative number!");
    }
    return sqrt(num);
}

// =============================
// Menu display
// =============================
void printMenu()
{
    cout << "\n==============================\n";
    cout << "        CALCULATOR APP\n";
    cout << "==============================\n";
    cout << "1. Addition\n";
    cout << "2. Subtraction\n";
    cout << "3. Multiplication\n";
    cout << "4. Division\n";
    cout << "5. Power (a^b)\n";
    cout << "6. Square Root\n";
    cout << "7. Exit\n";
    cout << "Choose an option (1-7): ";
}

// =============================
// Input two numbers
// =============================
void getTwoNumbers(double &a, double &b)
{
    cout << "Enter first number: ";
    while (!(cin >> a))
    {
        cout << "Invalid input! Try again: ";
        clearInput();
    }

    cout << "Enter second number: ";
    while (!(cin >> b))
    {
        cout << "Invalid input! Try again: ";
        clearInput();
    }
}

// =============================
// Main function
// =============================
int main()
{
    int choice;
    double a, b, result;

    while (true)
    {
        printMenu();
        cin >> choice;

        if (!cin)
        {
            cout << "Invalid input! Enter numbers only.\n";
            clearInput();
            continue;
        }

        try
        {
            switch (choice)
            {
            case 1:
                getTwoNumbers(a, b);
                result = add(a, b);
                cout << "Result: " << result << endl;
                break;

            case 2:
                getTwoNumbers(a, b);
                result = subtract(a, b);
                cout << "Result: " << result << endl;
                break;

            case 3:
                getTwoNumbers(a, b);
                result = multiply(a, b);
                cout << "Result: " << result << endl;
                break;

            case 4:
                getTwoNumbers(a, b);
                result = divide(a, b);
                cout << "Result: " << result << endl;
                break;

            case 5:
                getTwoNumbers(a, b);
                result = power(a, b);
                cout << "Result: " << result << endl;
                break;

            case 6:
                cout << "Enter a number: ";
                while (!(cin >> a))
                {
                    cout << "Invalid input! Try again: ";
                    clearInput();
                }
                result = squareRoot(a);
                cout << "Result: " << result << endl;
                break;

            case 7:
                cout << "Thank you for using the calculator!\n";
                return 0;

            default:
                cout << "Invalid choice! Enter 1–7.\n";
            }
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    return 0;
}
