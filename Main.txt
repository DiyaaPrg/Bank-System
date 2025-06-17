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

enum enBankChoices { ShowClients = 1, AddClient = 2, DeleteClient = 3, UpdateClient = 4, FindClient = 5, Exit = 6};

stClientsInfo ConvertLineToRecord(string line)
{
    stClientsInfo client;

    vector <string> Data = str::SplitString(line, seperator);

    client.AccountNumber = Data[0];
    client.PinCode       = Data[1];
    client.Name          = Data[2];
    client.Phone         = Data[3];
    client.Balance       = stod(Data[4]);

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
    line += client.PinCode       + seperator;
    line += client.Name          + seperator;
    line += client.Phone         + seperator;
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

bool IsClientExisted(vector <stClientsInfo>& vClientData, stClientsInfo &Client, string accountnumber)
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

void ShowMenue()
{
    cout << "\n=================================================\n";
    cout << "               Main Menu Screen                  \n";
    cout << "=================================================\n";
    cout << "\t [1] Show Client List. \n";
    cout << "\t [2] Add New Client.\n";
    cout << "\t [3] Delete Client.\n";
    cout << "\t [4] Update Client Info.\n";
    cout << "\t [5] Find Client.\n";
    cout << "\t [6] Exit\n";
    cout << "=================================================\n";

}

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

void ShowClientList(vector <stClientsInfo>& vClientData)
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
        for (stClientsInfo &client: vClientData)
        {
            PrintClientRecord(client);
            cout << endl;
        }
    }
    cout << "\n________________________________________________________________________________________________\n" << endl;



}

stClientsInfo ReadClientInfo(vector <stClientsInfo>& vClientData, string accountNumber)
{
    stClientsInfo client;

    client.AccountNumber = accountNumber;
    client.PinCode       = str::Readtext("Enter Pin Code: ");
    client.Name          = str::Readtext("Enter name: ");
    client.Phone         = str::Readtext("Enter Phone: ");
    client.Balance       = Num::ReadFLoat("Enter Account Balance: ");

    return client;
}

void AddNewClientToFile(vector <stClientsInfo>& vClientData, stClientsInfo &client)
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

void AddNewclient(vector <stClientsInfo>& vClientData)
{
    string accountnumber;
    stClientsInfo client; 

    char to_continue = 'Y';
    do
    {
        system("cls");
        cout << "\nEnter account Number: ";
        getline(cin >> ws, accountnumber);

        if (vClientData.size() > 0)
        {
            
            while (IsClientExisted(vClientData, client, accountnumber))
            {
                cout << "\nClient with [" << accountnumber << "] already exists, ";
                cout << ("Enter another account number: ");
                getline(cin >> ws, accountnumber);
            }
        }
        client = ReadClientInfo(vClientData, accountnumber);

        vClientData.push_back(client);
        AddNewClientToFile(vClientData, client);

        cout << "\nClient added successfully! ";
        to_continue = Char::ReadChar("Do you want to add more clients? (y/n): ");


    } while (toupper(to_continue) == 'Y');
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

bool Deleteclient(vector <stClientsInfo>& vClientData)
{
    stClientsInfo client;
    string accountNumber;
    cout << "\n----------------------------------\n";
    cout << "       Delete Client Screen";
    cout << "\n----------------------------------\n";

    cout << "\nEnter account Number: ";
    getline(cin >> ws, accountNumber);

    if (IsClientExisted(vClientData, client, accountNumber))
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

stClientsInfo ReadInfoToUpdate(vector <stClientsInfo>& vClientData, string accountNumber)
{
    for (stClientsInfo &Client : vClientData)
    {
        if (Client.AccountNumber == accountNumber)
        {
            Client.AccountNumber = accountNumber;

            cout << ("Enter Pin Code: ");
            getline(cin >> ws, Client.PinCode);
            Client.Name     = str::Readtext("Enter name: ");
            Client.Phone    = str::Readtext("Enter Phone: ");
            Client.Balance  = Num::ReadFLoat("Enter Account Balance: ");
            return Client;

        }
    }
}

void SaveUpdatedClientToFile(vector <stClientsInfo>& vClientData, string accountNumber, stClientsInfo &client)
{
    fstream file;
    file.open(filename, ios::out |ios::app);

    string line_of_updated_client = ConvertRecordToLine(client);
    string line;
    while (getline(file, line))
    {
        if (line.substr(0, line_of_updated_client.length()) == accountNumber)
        {
            line = line_of_updated_client;
        }
    }


    file.close();
}

void Updateclient(vector <stClientsInfo>& vClientData)
{
    cout << "\n----------------------------------\n";
    cout << "\     Update Client Info Screen  ";
    cout << "\n----------------------------------\n";

    stClientsInfo client;
    string accountNumber;
    cout << "\nEnter account Number: ";
    getline(cin >> ws, accountNumber);

    if (IsClientExisted(vClientData, client, accountNumber))
    {
        PrintClientInfo(client);
        char answer = Char::ReadChar("\n\nAre you sure you want to update this client? (y/n): ");

        if (toupper(answer) == 'Y')
        {
            client = ReadInfoToUpdate(vClientData, accountNumber);

            SaveUpdatedClientToFile(vClientData, accountNumber, client);

            cout << "\n\nClient Updated successfully";

        }

    }
    else
    {
        cout << "\nClient with Account Number [" << accountNumber << "] is Not Found...!\n";
    }
}

void Findclient(vector <stClientsInfo>& vClientData)
{
    cout << "\n----------------------------------\n";
    cout << "\        Find Client  Screen";
    cout << "\n----------------------------------\n";

    string accountNumber;
    stClientsInfo client;
    cout << "Please enter the Account Number: ";
    getline(cin >> ws, accountNumber);

    if (IsClientExisted(vClientData, client, accountNumber))
    {
        PrintClientInfo(client);
    }
    else
    {
        cout << "\nClient with Account Number [" << accountNumber << "] is Not Found...!\n";
    }
}

void EndsProgram()
{
    cout << "\n----------------------------------\n";
    cout << "           Program Ends :-) ";
    cout << "\n----------------------------------\n";

    system("pause>0");
}

void ProcessChoice(enBankChoices choice, vector <stClientsInfo>& vClientData)
{
    switch (choice)
    {
    case (enBankChoices::ShowClients):
        ShowClientList(vClientData);
        break;
    case (enBankChoices::AddClient):
        AddNewclient(vClientData);

        break;
    case (enBankChoices::DeleteClient):
        Deleteclient(vClientData);

        break;
    case (enBankChoices::UpdateClient):
        Updateclient(vClientData);

        break;
    case (enBankChoices::FindClient):
        Findclient(vClientData);

        break;
    case (enBankChoices::Exit):
        EndsProgram();

        break;
    default:
        ShowClientList(vClientData);
        break;
    }
}

void RunTheBank(vector <stClientsInfo>& vClientData)
{
    short answer;
    do
    {
        ShowMenue();
        answer = Num::ReadAnyNumber("\nChoose what do you want to do? [1 / 6]: ");
        system("cls");
        ProcessChoice(enBankChoices(answer), vClientData);

        if (answer == 6)
        {
            break;
        }
        cout << "\n\nPress Any Key to go back to Main Menue....";
        system("pause>0");

        system("cls");



    } while (answer > 0 && answer < 7);
}


int main()
{
    vector <stClientsInfo> vClientsInfo = LoadDataFromFileToVector();

    RunTheBank(vClientsInfo);








    return 0;
}
