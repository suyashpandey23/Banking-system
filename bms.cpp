#include <iostream>
#include <iomanip>
#include <cctype>
#include <fstream>
#include <stdlib.h>
using namespace std;

class Bank_Account
{

    int account_number;
    char name[100];
    char type;
    int Money_Deposit;

public:
    void modify();
    void report() const;
    int retacno() const
    {
        return account_number;
    }
    void dep(int x)
    {
        Money_Deposit += x;
    }
    void draw(int x)
    {
        Money_Deposit -= x;
    }
    int retdeposit() const
    {
        return Money_Deposit;
    }
    void create_account();
    void Display_account();
};

void Bank_Account::modify()
{
    cout << "\t Account Number: " << account_number << endl;
    cout << "\t Modify Account Holder name : ";
    cin.ignore();
    cin.getline(name, 100);
    cout << "\t Modify Type of account : ";
    cin >> type;

    type = toupper(type);
    cout << "\t Modify Balance amount: ";
    cin >> Money_Deposit;
}
void Bank_Account::create_account()
{
    system("clear");
    cout << "\t Enter the Account Number : ";
    cin >> account_number;
    cout << "\t Enter the name of the account holder : ";
    cin.ignore();
    cin.getline(name, 100);

    cout << "\t Enter the type of account(current:C/saving:S) : ";
    cin >> type;
    toupper(type);
    cout << "\t Enter the initial ammount (>=500 for a saving account and >=1000 for current account) : ";
    cin >> Money_Deposit;
    cout << endl;
    cout << "\t Account Created successfully... :-)" << endl;

    cout << endl;
}

void Bank_Account::Display_account()
{

    cout << "\t Bank account Number : " << account_number << endl;
    cout << "\t Account Holder Name : " << name << endl;
    cout << "\t Type of account : " << type << endl;
    cout << "\t Account Balance : " << Money_Deposit << endl;
}

void Bank_Account::report() const
{
    cout << account_number << setw(9) << " " << name << setw(9) << " " << type << setw(12) << " " << Money_Deposit << endl;
}
void write_account()
{ // writes record in binary file

    Bank_Account ac;
    ofstream outfile;
    outfile.open("account.dat", ios::binary | ios::app);
    ac.create_account();
    outfile.write(reinterpret_cast<char *>(&ac), sizeof(Bank_Account));
    outfile.close();
}
void delete_account(int n)
{

    Bank_Account ac;
    ifstream infile;
    ofstream outfile;
    infile.open("account.dat", ios::binary);
    if (!infile)
    {
        cout << "File could not be open || Press any key...." << endl;
        return;
    }

    outfile.open("Temp.dat", ios::binary);
    infile.seekg(0, ios::beg);

    while (infile.read(reinterpret_cast<char *>(&ac), sizeof(Bank_Account)))
    {
        if (ac.retacno() != n)
        {
            outfile.write(reinterpret_cast<char *>(&ac), sizeof(Bank_Account));
        }
    }
    infile.close();
    outfile.close();
    remove("Bank_Account.dat");
    rename("Temo.dat", "Bank_account.dat");

    cout << "\t Record Deleted...." << endl;
}

void display_details(int n)
{

    Bank_Account ac;
    bool flag = false;
    ifstream infile;
    infile.open("account.dat", ios::binary);

    if (!infile)
    {
        cout << "File could not be open || Press any key...." << endl;
        return;
    }

    cout << "\t Bank Account Details are as follows :- " << endl;
    while (infile.read(reinterpret_cast<char *>(&ac), sizeof(Bank_Account)))
    {
        if (ac.retacno() == n)
        {
            ac.Display_account();
            flag = true;
        }
    }

    infile.close();
    if (flag == false)
    {
        cout << "Account number does not exist!" << endl;
    }
}

void display_all()
{
    system("clear");
    Bank_Account ac;

    ifstream infile;
    infile.open("account.dat", ios::binary);

    if (!infile)
    {
        cout << "File could not be open || Press any key...." << endl;
        return;
    }

    cout << "\t Bank account Holder List :-" << endl;
    cout << "================================================" << endl;

    cout << "A/C no.       Name         Type          Balance" << endl;

    cout << "================================================" << endl;

    while (infile.read(reinterpret_cast<char *>(&ac), sizeof(Bank_Account)))
    {
        ac.report();
    }

    infile.close();
}
void Money_deposit_withdrwal(int n, int option)
{
    int amt;
    bool found = false;
    Bank_Account ac;
    fstream file;
    file.open("account.dat", ios::binary | ios::in | ios::out);

    if (!file)
    {
        cout << "File could not be open || Press any key...." << endl;
        return;
    }

    while (!file.eof() && found == false)
    {
        file.read(reinterpret_cast<char *>(&ac), sizeof(Bank_Account));
        if (ac.retacno() == n)
        {
            ac.Display_account();
            if (option == 1)
            {
                cout << "\t Enter the Amount of money you want to deposit : ";
                cin >> amt;
                ac.dep(amt);
            }
            if (option == 2)
            {
                cout << "\t Enter the Amount to be Withdraw : ";
                cin >> amt;
                int balance = ac.retdeposit() - amt;
                if (balance < 0)
                {
                    cout << "\t Insufficient Balance..." << endl;
                }
                else
                {
                    ac.draw(n);
                }
            }

            int pos = (-1) * static_cast<int>(sizeof(Bank_Account));
            file.seekp(pos, ios::cur);                                       // move the pointer to the pos of the file
            file.write(reinterpret_cast<char *>(&ac), sizeof(Bank_Account)); // record updation

            cout << "\t Record Updated..." << endl;
            found = true;
        }
    }
    file.close();
    if (found == false)
    {
        cout << "\t Record Not Found!..." << endl;
    }
}
void updation_bank_account(int n)
{
    bool found = false;
    Bank_Account ac;
    fstream file;
    file.open("account.dat", ios::binary | ios::in | ios::out);

    if (!file)
    {
        cout << "File could not be open || Press any key...." << endl;
        return;
    }

    while (!file.eof() && found == false)
    {
        file.read(reinterpret_cast<char *>(&ac), sizeof(Bank_Account));
        if (ac.retacno() == n)
        {
            ac.Display_account();
            cout << endl;
            cout << "Enter the detail of the account" << endl;
            ac.modify();

            int pos = (-1) * static_cast<int>(sizeof(Bank_Account));
            file.seekp(pos, ios::cur);                                       // move the pointer to the pos of the file
            file.write(reinterpret_cast<char *>(&ac), sizeof(Bank_Account)); // record updation

            cout << "\t Record Updated..." << endl;
            found = true;
        }
    }
    file.close();
    if (found == false)
    {
        cout << "\t Record Not Found!..." << endl;
    }
}
int main()
{
    char ch;
    int num;

    do
    {
        cout << "\t\t--------------------------------------------" << endl;
        cout << "\t\t || Welcome to Bank Management System ||" << endl;
        cout << "\t\t--------------------------------------------" << endl;

        cout << endl;

        cout << "\t---------Main Menu-----------" << endl;
        cout << "\t 1.Create Account" << endl;
        cout << "\t 2.Deposit Money" << endl;
        cout << "\t 3.Withdraw Money" << endl;
        cout << "\t 4.Balance Enquiry" << endl;
        cout << "\t 5.All Account Holder List" << endl;
        cout << "\t 6.Close an Account" << endl;
        cout << "\t 7.Modify an Account" << endl;
        cout << "\t 8.Exit" << endl;

        cout << endl;
        cout << "\t Enter your Choice(1-8) : ";
        cin >> ch;

        switch (ch)
        {
        case '1':
            write_account();
            break;
        case '2':
            system("clear");
            cout << "\t Enter the account number : ";
            cin >> num;
            Money_deposit_withdrwal(num, 1); // deposit fun
            break;
        case '3':
            system("clear");
            cout << "\t Enter the account number : ";
            cin >> num;
            Money_deposit_withdrwal(num, 2); // withdraw fun
            break;
        case '4':
            system("clear");
            cout << "\t Enter the account number : ";
            cin >> num;
            display_details(num); // balance enquiry fun
            break;
        case '5':
            display_all();
            break;
        case '6':
            system("clear");
            cout << "\t Enter the account number : ";
            cin >> num;
            delete_account(num); // close acc fun
            break;
        case '7':
            system("clear");
            cout << "\t Enter the account number : ";
            cin >> num;
            updation_bank_account(num); // modify acc fun
            break;
        case '8':
            cout << "\t Thanks for using the Bank Management System !. Press any key to exit..." << endl;
            break;
        }
        cin.ignore();
        cin.get();

    } while (ch != '8');
    return 0;
}