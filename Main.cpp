#include <iostream>
#include <vector>
#include <string>
#include "String.h"
#include "Number.h"
#include <fstream>
#include <iomanip>
#include "Char.h"


using namespace std;

const string filename = "Bank.txt";
const string seperator = "#...#";


struct stClientsInfo {
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double Balance;
    bool   MarkForDelete = false;
};

enum enBankOptions {
    ShowClients = 1, AddClient = 2,
    DeleteClient = 3, UpdateClient = 4,
    FindClient = 5, Transactions = 6,
    Exit = 7
};

enum enTransactionsOptions
{
    Desposit = 1, Withdraw = 2, TotalBalances = 3, MainMenue = 4
};

void ShowMenue(vector <stClientsInfo>& vClientData);

stClientsInfo ConvertLineToRecord(string line)
{
    stClientsInfo client;

    vector <string> Data = str::SplitString(line, seperator);

    client.AccountNumber = Data[0];
    client.PinCode = Data[1];
    client.Name = Data[2];
    client.Phone = Data[3];
    client.Balance = stod(Data[4]);

    return client;
}

vector <stClientsInfo> LoadDataFromFileToVector()
{
    fstream file;
    vector <stClientsInfo> vClients;
    string line;

    file.open(filename, ios::in);

    while (getline(file, line))
    {
        if (line != "")
        {
            vClients.push_back(ConvertLineToRecord(line));
        }
    }
    file.close();
    return vClients;
}

string ConvertRecordToLine(stClientsInfo client)
{
    string line;
    line += client.AccountNumber + seperator;
    line += client.PinCode + seperator;
    line += client.Name + seperator;
    line += client.Phone + seperator;
    line += to_string(client.Balance);

    return line;
}

void LoadDataFromVectortoFile(vector <stClientsInfo>& vClientData)
{
    fstream file;

    file.open(filename, ios::out);

    for (stClientsInfo client : vClientData)
    {
        string line = ConvertRecordToLine(client);
        if (client.MarkForDelete == false)
        {
            file << line << endl;
        }
    }
}

string ReadClientAccountNumber()
{
    string accountNumber;

    cout << "\nEnter account Number: ";
    getline(cin >> ws, accountNumber);

    return accountNumber;
}

bool IsClientExisteByAccountNumber(vector <stClientsInfo>& vClientData, stClientsInfo& Client, string accountnumber)
{

    for (stClientsInfo& client : vClientData)
    {
        if (client.AccountNumber == accountnumber)
        {
            Client = client;
            return true;
        }
    }
    return false;
}

void PerformTransactionOptions(enTransactionsOptions option, vector <stClientsInfo>& vClientData);

void PrintClientInfo(stClientsInfo Client)
{
    cout << "\nThe following are the clients details:\n";
    cout << "----------------------------------------\n";
    cout << "\nAccount Number  : " << Client.AccountNumber;
    cout << "\nPin Code        : " << Client.PinCode;
    cout << "\nName            : " << Client.Name;
    cout << "\nPhone           : " << Client.Phone;
    cout << "\nAccount Balance : " << Client.Balance;
    cout << "\n----------------------------------------\n";

}

void PrintClientRecord(stClientsInfo Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.Balance;
}

void PrintClientsBalances(stClientsInfo Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Balance;

}

void ShowAllClientsScreen(vector <stClientsInfo>& vClientData)
{
    cout << "\n\t\t\t\t\tClient List (" << vClientData.size() << ")Client(s).";
    cout << "\n________________________________________________________________________________________________\n";

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n________________________________________________________________________________________________\n" << endl;

    if (vClientData.size() > 0)
    {
        for (stClientsInfo client : vClientData)
        {
            PrintClientRecord(client);
            cout << endl;
        }
    }
    else
    {
        cout << "\t\t\t\tNo Clients Available in the System!";
    }
    cout << "\n________________________________________________________________________________________________\n" << endl;



}

void ShowAllClientsBalances(vector <stClientsInfo>& vClientData)
{
    system("cls");
    cout << "\n\t\t\t\t\tBalances List (" << vClientData.size() << ")Client(s).";
    cout << "\n________________________________________________________________________________________________\n";

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n________________________________________________________________________________________________\n" << endl;

    double totalBalances = 0;

    if (vClientData.size() > 0)
    {
        for (stClientsInfo& client : vClientData)
        {
            PrintClientsBalances(client);

            totalBalances += client.Balance;

            cout << endl;


        }
    }
    else
    {
        cout << "\t\t\t\tNo Clients Available in the System!";
    }
    cout << "\n________________________________________________________________________________________________\n";
    cout << "\t\t\t\t\t Total Balances = " << totalBalances << endl;



}

stClientsInfo ReadClientInfo(vector <stClientsInfo>& vClientData)
{
    stClientsInfo client;
    string accountnumber = ReadClientAccountNumber();

    if (vClientData.size() > 0)
    {
        while (IsClientExisteByAccountNumber(vClientData, client, accountnumber))
        {
            cout << "\nClient with [" << accountnumber << "] already exists, ";
            cout << ("Enter another account number: ");
            getline(cin >> ws, accountnumber);
        }
    }

    client.AccountNumber = accountnumber;
    client.PinCode = str::Readtext("Enter Pin Code: ");
    client.Name = str::Readtext("Enter name: ");
    client.Phone = str::Readtext("Enter Phone: ");
    client.Balance = Num::ReadFLoat("Enter Account Balance: ");

    return client;
}

void AddNewClientToFile(vector <stClientsInfo>& vClientData, stClientsInfo& client)
{
    fstream file;

    file.open(filename, ios::app);

    string line;

    line += client.AccountNumber + seperator;
    line += client.PinCode + seperator;
    line += client.Name + seperator;
    line += client.Phone + seperator;
    line += to_string(client.Balance);

    file << line << endl;
    file.close();
}

void AddNewClient(vector <stClientsInfo>& vClientData)
{
    stClientsInfo client;
    client = ReadClientInfo(vClientData);

    vClientData.push_back(client);
    AddNewClientToFile(vClientData, client);

}

void AddNewClients(vector <stClientsInfo>& vClientData)
{
    char AddMore = 'Y';
    do
    {
        system("cls");

        cout << "\nAdding New Client:\n\n";

        AddNewClient(vClientData);

        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> AddMore;


    } while (toupper(AddMore) == 'Y');

}

void ShowAddNewClientsScreen(vector <stClientsInfo>& vClientData)
{

    system("cls");
    cout << "\n----------------------------------\n";
    cout << "       Add New Client Screen";
    cout << "\n----------------------------------\n";

    AddNewClients(vClientData);
}

void MarkClientForDelete(vector <stClientsInfo>& vClientData, string accountNumber)
{
    for (stClientsInfo& client : vClientData)
    {
        if (client.AccountNumber == accountNumber)
        {
            client.MarkForDelete = true;
        }
    }
}

bool DeleteClientByAccountNumber(vector <stClientsInfo>& vClientData, string accountNumber)
{
    stClientsInfo client;

    if (IsClientExisteByAccountNumber(vClientData, client, accountNumber))
    {
        PrintClientInfo(client);

        char answer = Char::ReadChar("\n\nAre you sure you want to delete this client? (y/n): ");

        if (toupper(answer) == 'Y')
        {
            MarkClientForDelete(vClientData, accountNumber);

            LoadDataFromVectortoFile(vClientData);
            vClientData = LoadDataFromFileToVector();

            cout << "\n\nClient Deleted successfully";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number [" << accountNumber << "] is Not Found...!\n";
    }
}

void ShowDeleteClientScreen(vector <stClientsInfo>& vClientData)
{

    cout << "\n----------------------------------\n";
    cout << "       Delete Client Screen";
    cout << "\n----------------------------------\n";

    DeleteClientByAccountNumber(vClientData, ReadClientAccountNumber());

}

stClientsInfo ReadInfoToUpdate(vector <stClientsInfo>& vClientData, string accountNumber)
{
    for (stClientsInfo& Client : vClientData)
    {
        if (Client.AccountNumber == accountNumber)
        {
            Client.AccountNumber = accountNumber;

            cout << ("Enter Pin Code: ");
            getline(cin >> ws, Client.PinCode);
            Client.Name = str::Readtext("Enter name: ");
            Client.Phone = str::Readtext("Enter Phone: ");
            Client.Balance = Num::ReadFLoat("Enter Account Balance: ");

            return Client;

        }
    }
}

bool UpdateClientByAccountNumber(vector <stClientsInfo>& vClientData, string accountNumber)
{
    stClientsInfo client;


    if (IsClientExisteByAccountNumber(vClientData, client, accountNumber))
    {
        PrintClientInfo(client);
        char answer = Char::ReadChar("\n\nAre you sure you want to update this client? (y/n): ");

        if (toupper(answer) == 'Y')
        {
            client = ReadInfoToUpdate(vClientData, accountNumber);

            LoadDataFromVectortoFile(vClientData);

            cout << "\n\nClient Updated successfully";

            return true;

        }

    }
    else
    {
        cout << "\nClient with Account Number [" << accountNumber << "] is Not Found...!\n";
    }
}

void ShowUpdatedClientScreen(vector <stClientsInfo>& vClientData)
{
    cout << "\n----------------------------------\n";
    cout << "\     Update Client Info Screen  ";
    cout << "\n----------------------------------\n";

    UpdateClientByAccountNumber(vClientData, ReadClientAccountNumber());
}

void ShowFindClientScreen(vector <stClientsInfo>& vClientData)
{
    cout << "\n----------------------------------\n";
    cout << "\        Find Client  Screen";
    cout << "\n----------------------------------\n";

    string accountNumber = ReadClientAccountNumber();
    stClientsInfo client;

    if (IsClientExisteByAccountNumber(vClientData, client, accountNumber))
    {
        PrintClientInfo(client);
    }
    else
    {
        cout << "\nClient with Account Number [" << accountNumber << "] is Not Found...!\n";
    }
}

double ReadAmount(string message)
{
    double amount;
    amount = double(Num::ReadAnyNumber(message));

    return amount;
}

double DepositOrWithdrawUsingAccountNumber(vector <stClientsInfo>& vClientData, double amount, string accountNumber)
{
    for (stClientsInfo& client : vClientData)
    {
        if (client.AccountNumber == accountNumber)
        {
            client.Balance += amount;
            return client.Balance;
        }

    }
}

void DespositBalanceByAccountNumber(vector <stClientsInfo>& vClientData, string accountNumber)
{
    stClientsInfo client;

    while (!IsClientExisteByAccountNumber(vClientData, client, accountNumber))
    {
        cout << "\nClient with [" << accountNumber << "] does not exist...!\n";

        cout << ("Enter another account number: ");
        getline(cin >> ws, accountNumber);
    }

    PrintClientInfo(client);

    double amount = (ReadAmount("\n\nPlease Enter desposit amount: ")); //1000

    char answer = Char::ReadChar("\n\nAre you sure you want perform this transaction? (y/n): ");

    if (toupper(answer) == 'Y')
    {
        double NewBalance = DepositOrWithdrawUsingAccountNumber(vClientData, amount, accountNumber);

        LoadDataFromVectortoFile(vClientData);

        cout << "\n\nDone successfully, New Balance is: " << NewBalance << endl;



    }


}

void ShowDespositScreen(vector <stClientsInfo>& vClientData)
{
    cout << "\n----------------------------------\n";
    cout << "       Desposit Screen";
    cout << "\n----------------------------------\n";

    DespositBalanceByAccountNumber(vClientData, ReadClientAccountNumber());
}

bool WithDrawBalanceByAccountNumber(vector <stClientsInfo>& vClientData, string accountNumber)
{
    stClientsInfo client;

    while (!IsClientExisteByAccountNumber(vClientData, client, accountNumber))
    {
        cout << "\nClient with [" << accountNumber << "] does not exist...!\n";

        cout << ("Enter another account number: ");
        getline(cin >> ws, accountNumber);
    }

    PrintClientInfo(client);

    double amount = ReadAmount("\n\nPlease Enter desposit amount: ");

    while (client.Balance < amount)
    {
        cout << "\nAmount Exceeds the balance, you cannot draw up to: " << client.Balance << "\n";
        cout << "Please enter another amount: ";
        cin >> amount;
    }

    char answer = Char::ReadChar("\n\nAre you sure you want perform this transaction? (y/n): ");

    if (toupper(answer) == 'Y')
    {
        double NewBalance = DepositOrWithdrawUsingAccountNumber(vClientData, (amount * -1), accountNumber);

        LoadDataFromVectortoFile(vClientData);

        cout << "\n\nDone successfully, New Balance is: " << NewBalance << endl;

        return true;

    }


}

void ShowWithdrawScreen(vector <stClientsInfo>& vClientData)
{
    cout << "\n----------------------------------\n";
    cout << "       WithDraw Screen";
    cout << "\n----------------------------------\n";

    WithDrawBalanceByAccountNumber(vClientData, ReadClientAccountNumber());
}

void ShowTransactionsScreen(vector <stClientsInfo>& vClientData)
{
    cout << "\n=================================================\n";
    cout << "           Transactions Menu Screen                  \n";
    cout << "=================================================\n";
    cout << "\t [1] Desposit \n";
    cout << "\t [2] WithDraw\n";
    cout << "\t [3] Total Balances\n";
    cout << "\t [4] Main Menue\n";
    cout << "=================================================\n";

    PerformTransactionOptions(enTransactionsOptions(Num::ReadAnyNumber("\nChoose what do you want to do? [1 / 4]: ")), vClientData);
}

void GoBackToTransactionsScreen(vector <stClientsInfo>& vClientData)
{
    cout << "\n\nPress any key to go back to Transactions Menue...";
    system("pause>0");
    system("cls");
    ShowTransactionsScreen(vClientData);
}

bool ShowEndScreen()
{
    cout << "\n----------------------------------\n";
    cout << "           Program Ends :-) ";
    cout << "\n----------------------------------\n";

    return true;

}

void GoBackToMainMenue(vector <stClientsInfo>& vClientData)
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");

    system("cls");

    ShowMenue(vClientData);

}

void PerformTransactionOptions(enTransactionsOptions option, vector <stClientsInfo>& vClientData)
{
    system("cls");
    switch (option)
    {
    case (enTransactionsOptions::Desposit):
    {
        ShowDespositScreen(vClientData);
        GoBackToTransactionsScreen(vClientData);
        break;
    }

    case (enTransactionsOptions::Withdraw):
    {
        ShowWithdrawScreen(vClientData);
        GoBackToTransactionsScreen(vClientData);
        break;
    }

    case (enTransactionsOptions::TotalBalances):
    {
        ShowAllClientsBalances(vClientData);
        GoBackToTransactionsScreen(vClientData);
        break;
    }

    case (enTransactionsOptions::MainMenue):
    {
        system("cls");
        ShowMenue(vClientData);
    }
    }
}

void PerfromMainMenueOption(enBankOptions option, vector <stClientsInfo>& vClientData)
{
    system("cls");
    switch (option)
    {
    case (enBankOptions::ShowClients):
    {
        ShowAllClientsScreen(vClientData);
        GoBackToMainMenue(vClientData);
        break;
    }


    case (enBankOptions::AddClient):
    {
        ShowAddNewClientsScreen(vClientData);
        GoBackToMainMenue(vClientData);
        break;
    }

    case (enBankOptions::DeleteClient):
    {
        ShowDeleteClientScreen(vClientData);
        GoBackToMainMenue(vClientData);
        break;
    }

    case (enBankOptions::UpdateClient):
    {
        ShowUpdatedClientScreen(vClientData);
        GoBackToMainMenue(vClientData);
        break;
    }

    case (enBankOptions::FindClient):
    {
        ShowFindClientScreen(vClientData);
        GoBackToMainMenue(vClientData);
        break;
    }

    case (enBankOptions::Transactions):
    {
        ShowTransactionsScreen(vClientData);
        GoBackToMainMenue(vClientData);
        break;
    }

    case (enBankOptions::Exit):
    {
        ShowEndScreen();
        exit(0);
    }
    }
}

void ShowMenue(vector <stClientsInfo>& vClientData)
{
    cout << "\n=================================================\n";
    cout << "               Main Menu Screen                  \n";
    cout << "=================================================\n";
    cout << "\t [1] Show Client List. \n";
    cout << "\t [2] Add New Client.\n";
    cout << "\t [3] Delete Client.\n";
    cout << "\t [4] Update Client Info.\n";
    cout << "\t [5] Find Client.\n";
    cout << "\t [6] Transactions.\n";
    cout << "\t [7] Exit\n";
    cout << "=================================================\n";

    PerfromMainMenueOption(enBankOptions(Num::ReadAnyNumber("\nChoose what do you want to do ? [1 / 7] : ")), vClientData);


}




int main()
{
    vector <stClientsInfo> vClientsInfo = LoadDataFromFileToVector();

    ShowMenue(vClientsInfo);




    return 0;
}
