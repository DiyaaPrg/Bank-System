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
const string UserFile = "Users.txt";
const string seperator = "#...#";


struct stClientsInfo {
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double Balance;
    bool   MarkForDelete = false;
};

struct stUserPermessions
{
    bool ShowClientList;
    bool AddNewClient;
    bool UpdateClient;
    bool DeleteClient;
    bool FindClinet;
    bool Transaction;
    bool ManageUsers;
};

enum enMainMenueOptions {
    ShowList = 1, AddNewClient = 2, DeleteClient = 4, UpdateClient = 8, FindClient = 16,
    Transactions = 32, ManageUsers = 64
};

struct stUserInfo
{
    string Name;
    string Password;
    short Permessions;
    stUserPermessions permessionsinBoolean;
    bool MarkForDelete = false;
};

enum enBankOptions {
    ShowClients = 1, AddClient = 2,
    DeleteClientOption = 3, UpdateClientOption = 4,
    FindClientOption = 5, TransactionsOption = 6,
    ManageUsersOption = 7, LogOut = 8
};

enum enManageUsersOptions
{
    ListUsers = 1, Adduser = 2, Deleteuser = 3, Updateuser = 4, Finduser = 5, MainMenue = 6
};

enum enTransactionsOptions
{
    Desposit = 1, Withdraw = 2, TotalBalances = 3, MainMenueOption = 4
};

stUserInfo user;

void CheckUserPermession(stUserInfo &user)
{
    if (user.Permessions == -1)
    {
            user.permessionsinBoolean.AddNewClient = true;
            user.permessionsinBoolean.ShowClientList = true;
            user.permessionsinBoolean.DeleteClient = true;
            user.permessionsinBoolean.UpdateClient = true;
            user.permessionsinBoolean.FindClinet = true;
            user.permessionsinBoolean.Transaction = true;
            user.permessionsinBoolean.ManageUsers = true;
     }

    else
    {

    user.permessionsinBoolean.ShowClientList = ((user.Permessions & enMainMenueOptions::ShowList) == enMainMenueOptions::ShowList) ? true : false;
    user.permessionsinBoolean.AddNewClient = ((user.Permessions & enMainMenueOptions::AddNewClient) == enMainMenueOptions::AddNewClient) ? true : false;
    user.permessionsinBoolean.DeleteClient = ((user.Permessions & enMainMenueOptions::DeleteClient) == enMainMenueOptions::DeleteClient) ? true : false;
    user.permessionsinBoolean.UpdateClient = ((user.Permessions & enMainMenueOptions::UpdateClient) == enMainMenueOptions::UpdateClient) ? true : false;
    user.permessionsinBoolean.FindClinet = ((user.Permessions & enMainMenueOptions::FindClient) == enMainMenueOptions::FindClient) ? true : false;
    user.permessionsinBoolean.Transaction = ((user.Permessions & enMainMenueOptions::Transactions) == enMainMenueOptions::Transactions) ? true : false;
    user.permessionsinBoolean.ManageUsers = ((user.Permessions & enMainMenueOptions::ManageUsers) == enMainMenueOptions::ManageUsers) ? true : false;
    }
    return;
}

stUserInfo ConvertLineToRecordForUsers(string line)
{
    stUserInfo user;

    vector <string> Data = str::SplitString(line, "#//#");

    user.Name = Data[0];
    user.Password = Data[1];
    user.Permessions = stoi(Data[2]);

    CheckUserPermession(user);

    return user;
}

vector <stUserInfo> LoadDataFromFileToVectorForUsers()
{
    fstream file;
    vector <stUserInfo> vUsers;
    string line;

    file.open(UserFile, ios::in); // Read Mode

    while (getline(file, line))
    {
        if (line != "")
        {
            vUsers.push_back(ConvertLineToRecordForUsers(line));
        }
    }
    file.close();
    return vUsers;
}

void Login();

void GoBackToManageUsersMenue();

void ShowMenue();

void GoBackToMainMenue();

void ReadUserNameAndPassword(string& username, string& password)
{
     cout << "Enter username: ";
    getline(cin >> ws, username);
    password = str::Readtext("Enter password: ");
}

void PrintNoAccessMessage()
{
    cout << "\n___________________________________________________\n";
    cout << "   Access Denied!\nYou don't have permessions to do this,\nPlease contact your admin\n";

    GoBackToMainMenue();

}

bool IsUserExisted( string username, string password, stUserInfo& User)
{
    vector < stUserInfo> vUsersInfo = LoadDataFromFileToVectorForUsers();

    for (stUserInfo& user : vUsersInfo)
    {
        if (user.Name == username && user.Password == password)
        {
            {
                User = user;
                return true;
            }

        }
    }
    return false;

}

bool IsUserExistedByUsername( string username, stUserInfo &User)
{
    vector < stUserInfo> vUsersInfo = LoadDataFromFileToVectorForUsers();

    for (stUserInfo& user : vUsersInfo)
    {
        if (user.Name == username)
        {
            User = user;
            return true;
        }

    }
    return false;

}

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

    file.open(filename, ios::in); // Read Mode

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

string ConvertRecordToLineForUsers(stUserInfo user)
{
    string line;
    line += user.Name + "#//#";
    line += user.Password + "#//#";
    line += to_string(user.Permessions);

    return line;
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

void LoadDataFromVectortoFileForUsers(vector <stUserInfo>& User)
{
    fstream file;

    file.open(UserFile, ios::out);

    for (stUserInfo user : User)
    {
        string line = ConvertRecordToLineForUsers(user);
        if (user.MarkForDelete == false)
        {
            file << line << endl;
        }
    }
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

bool IsClientExisteByAccountNumber(stClientsInfo& Client, string accountnumber)
{
    vector <stClientsInfo> vClientData = LoadDataFromFileToVector();

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

void PerformTransactionOptions(enTransactionsOptions option);

void PrintUserInfo(stUserInfo &User)
{
    cout << "\nThe following are the user details:\n";
    cout << "----------------------------------------\n";
    cout << "\nName            : " << User.Name;
    cout << "\nPassword        : " << User.Password;
    cout << "\nPermessions     : " << User.Permessions;
    cout << "\n----------------------------------------\n";

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

void PrintUserRecord(stUserInfo User)
{
    cout << "| " << setw(15) << left << User.Name;
    cout << "| " << setw(10) << left << User.Password;
    cout << "| " << setw(40) << left << User.Permessions;

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

void ShowAllUsersScreen()
{
    vector <stUserInfo> vUsers = LoadDataFromFileToVectorForUsers();

    cout << "\n\t\t\t\t\tUsers List (" << vUsers.size() << ") User(s).";
    cout << "\n________________________________________________________________________________________________\n";

    cout << "| " << left << setw(15) << "UserName";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(40) << "Permessions";
    cout << "\n________________________________________________________________________________________________\n" << endl;

    if (vUsers.size() > 0) // Check that file contains data and not empty
    {
        for (stUserInfo user : vUsers)
        {
            PrintUserRecord(user);
            cout << endl;
        }
    }
    cout << "\n________________________________________________________________________________________________\n" << endl;



}

void ShowAllClientsScreen()
{
    vector <stClientsInfo> vClientData = LoadDataFromFileToVector();

    if (user.permessionsinBoolean.ShowClientList)
    {
        cout << "\n\t\t\t\t\tClient List (" << vClientData.size() << ")Client(s).";
        cout << "\n________________________________________________________________________________________________\n";

        cout << "| " << left << setw(15) << "Account Number";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n________________________________________________________________________________________________\n" << endl;

        if (vClientData.size() > 0) // Check that file contains data and not empty
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
    else
    {
        PrintNoAccessMessage();
    }

}

void ShowAllClientsBalances()
{
    vector <stClientsInfo> vClientData = LoadDataFromFileToVector();

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

void ShowFindUserScreen()
{
    cout << "\n----------------------------------\n";
    cout << "         Find User  Screen";
    cout << "\n----------------------------------\n";

    string username;
    cout << ("Enter Name: ");
    getline(cin >> ws, username);  
    stUserInfo user;

    if (IsUserExistedByUsername( username, user))
    {
        PrintUserInfo(user);
    }
    else
    {
        cout << "\nUser with Username [" << username << "] is Not Found...!\n";
    }
}

short CalculatePermessionsToUser(stUserInfo& user)
{
    short permession = 0;
    if (user.permessionsinBoolean.ShowClientList)
        permession += enMainMenueOptions::ShowList;

    if (user.permessionsinBoolean.AddNewClient)
        permession += enMainMenueOptions::AddNewClient;

    if (user.permessionsinBoolean.DeleteClient)
        permession += enMainMenueOptions::DeleteClient;

    if (user.permessionsinBoolean.UpdateClient)
        permession += enMainMenueOptions::UpdateClient;

    if (user.permessionsinBoolean.FindClinet)
        permession += enMainMenueOptions::FindClient; 

    if (user.permessionsinBoolean.Transaction)
        permession += enMainMenueOptions::Transactions;

    if (user.permessionsinBoolean.ManageUsers)
        permession += enMainMenueOptions::ManageUsers;

    return permession;
}

void ReadUserPermessions(stUserInfo &user)
{

    string giveAcess = str::Readtext("\nDo you want to give full access? (y/n): ");
    if (giveAcess == "y" || giveAcess == "Y")
    {
        user.Permessions = -1;
        return;
    }

    else
    {
        cout << "\nDo you want to give access to:\n";
        giveAcess = str::Readtext("\nShow Client List? (y/n): ");
        user.permessionsinBoolean.ShowClientList = (giveAcess == "Y" || giveAcess == "y") ? true : false;

        giveAcess = str::Readtext("\nAdd New Client? (y/n): ");
        user.permessionsinBoolean.AddNewClient = (giveAcess == "Y" || giveAcess == "y") ? true : false;

        giveAcess = str::Readtext("\nDelete Client? (y/n): ");
        user.permessionsinBoolean.DeleteClient = (giveAcess == "Y" || giveAcess == "y") ? true : false;

        giveAcess = str::Readtext("\nUpdate Client? (y/n): ");
        user.permessionsinBoolean.UpdateClient = (giveAcess == "Y" || giveAcess == "y") ? true : false;

        giveAcess = str::Readtext("\nFind Client? (y/n): ");
        user.permessionsinBoolean.FindClinet = (giveAcess == "Y" || giveAcess == "y") ? true : false;

        giveAcess = str::Readtext("\nTransactions? (y/n): ");
        user.permessionsinBoolean.Transaction = (giveAcess == "Y" || giveAcess == "y") ? true : false;

        giveAcess = str::Readtext("\nManage Users? (y/n): ");
        user.permessionsinBoolean.ManageUsers = (giveAcess == "Y" || giveAcess == "y") ? true : false;

        user.Permessions = CalculatePermessionsToUser(user);
    }

}

stUserInfo ReadUserInfo(vector <stUserInfo>& Users)
{
    stUserInfo user;

    string username, password;
    ReadUserNameAndPassword(username, password);

    if (Users.size() > 0)
    {
        while (IsUserExisted( username, password, user))
        {
            cout << "\nClient with [" << username << "] already exists, ";
            ReadUserNameAndPassword(username, password);
        }
    }
    
    user.Name = username;
    user.Password = password;
    ReadUserPermessions(user);



    return user;
}

stUserInfo ReadUserInfoToUpdate(string username)
{
    vector < stUserInfo> vUsersInfo = LoadDataFromFileToVectorForUsers();

    for (stUserInfo& user : vUsersInfo)
    {
        if (user.Name == username)
        {

            cout << ("Enter Password: ");
            getline(cin >> ws, user.Password);

            ReadUserPermessions(user);
            return user;

        }
    }
}

void updateuser(vector <stUserInfo>& Users)
{
    stUserInfo user;
    
    string username;
    cout << ("Enter Name: ");
    getline(cin >> ws, username);

    if (IsUserExistedByUsername( username, user))
    {
        PrintUserInfo(user);
        char answer = Char::ReadChar("\n\nAre you sure you want to update this client? (y/n): ");

        if (toupper(answer) == 'Y')
        {
            user = ReadUserInfoToUpdate(username);

            LoadDataFromVectortoFileForUsers(Users);

            cout << "\n\nUser Updated successfully";

            return; // process has succeeded

        }

    }
    else
    {
        cout << "\nUser with Name [" << username << "] is Not Found...!\n";
    }
}

void ShowUpdatedUserScreen()
{
    vector <stUserInfo> Users = LoadDataFromFileToVectorForUsers();
    cout << "\n----------------------------------\n";
    cout << "      Update User Info Screen  ";
    cout << "\n----------------------------------\n";

    updateuser(Users);
}

void AddNewUserToFile(stUserInfo& user)
{
    fstream file;

    file.open(UserFile, ios::app);

    string line;

    line += user.Name + "#//#";
    line += user.Password + "#//#";
    line += to_string(user.Permessions);

    file  << endl << line << endl;
    file.close();
}

void AddNewUser()
{
    vector <stUserInfo> Users = LoadDataFromFileToVectorForUsers();
    stUserInfo user;
    user = ReadUserInfo(Users);

    Users.push_back(user);
    AddNewUserToFile( user);

}

void AddNewUsers()
{
    char AddMore = 'Y';
    do
    {
        cout << "\nAdding New User:\n\n";

        AddNewUser();

        cout << "\nUser Added Successfully, do you want to add more users? Y/N? ";
        cin >> AddMore;


    } while (toupper(AddMore) == 'Y');

}

void ShowAddNewUserScreen()
{
    system("cls");
    cout << "\n----------------------------------\n";
    cout << "       Add New User Screen";
    cout << "\n----------------------------------\n";

    AddNewUsers();
}

stClientsInfo ReadClientInfo(vector <stClientsInfo>& vClientData)
{
    stClientsInfo client;
    string accountnumber = ReadClientAccountNumber();

    if (vClientData.size() > 0)
    {
        while (IsClientExisteByAccountNumber( client, accountnumber))
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

void MarkUserForDelete(string username)
{
    vector <stUserInfo> User = LoadDataFromFileToVectorForUsers();
    for (stUserInfo& user : User)
    {
        if (user.Name == username)
        {
            user.MarkForDelete = true;
        }
    }
}

void DeleteUser()
{
    vector <stUserInfo> User = LoadDataFromFileToVectorForUsers();

    stUserInfo user;
    string username;
    cout << ("Enter Name: ");
    getline(cin >> ws, username);

    if (username == "Admin")
    {
        cout << "\n\nYou cannot delete this user!\n";
    }
    else if (IsUserExistedByUsername( username, user))
    {
        PrintUserInfo(user);

        char answer = Char::ReadChar("\n\nAre you sure you want to delete this user? (y/n): ");

        if (toupper(answer) == 'Y')
        {
            MarkUserForDelete( username);

            LoadDataFromVectortoFileForUsers(User);
            User = LoadDataFromFileToVectorForUsers();

            cout << "\n\nClient Deleted successfully";
            return;
        }
    }
    else
    {
        cout << "\nUser with Username [" << username << "] is Not Found...!\n";
    }
}

void ShowDeleteUserScreen()
{

    cout << "\n----------------------------------\n";
    cout << "       Delete User Screen";
    cout << "\n----------------------------------\n";

    DeleteUser();

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

void Addnewclient()
{
    vector <stClientsInfo> vClientData = LoadDataFromFileToVector();

    stClientsInfo client;
    client = ReadClientInfo(vClientData);

    vClientData.push_back(client);
    AddNewClientToFile(vClientData, client);

}

void AddNewClients()
{
    char AddMore = 'Y';
    do
    {
       
        cout << "\nAdding New Client:\n\n";

        Addnewclient();

        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> AddMore;


    } while (toupper(AddMore) == 'Y');

}

void ShowAddNewClientsScreen()
{

    if (user.permessionsinBoolean.AddNewClient)
    {
        system("cls");
        cout << "\n----------------------------------\n";
        cout << "       Add New Client Screen";
        cout << "\n----------------------------------\n";

        AddNewClients();
    }
    else
    {
        PrintNoAccessMessage();
        return;
    }

}

void MarkClientForDelete( string accountNumber)
{
    vector <stClientsInfo> vClientData = LoadDataFromFileToVector();

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

    if (IsClientExisteByAccountNumber( client, accountNumber))
    {
        PrintClientInfo(client);

        char answer = Char::ReadChar("\n\nAre you sure you want to delete this client? (y/n): ");

        if (toupper(answer) == 'Y')
        {
            MarkClientForDelete(accountNumber);

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

void ShowDeleteClientScreen()
{
    vector <stClientsInfo> vClientData = LoadDataFromFileToVector();

    if (user.permessionsinBoolean.DeleteClient)
    {
        cout << "\n----------------------------------\n";
        cout << "       Delete Client Screen";
        cout << "\n----------------------------------\n";

        DeleteClientByAccountNumber(vClientData, ReadClientAccountNumber());
    }
    else
    {
        PrintNoAccessMessage();
        return;
    }

}

stClientsInfo ReadInfoToUpdate( string accountNumber)
{
    vector <stClientsInfo> vClientData = LoadDataFromFileToVector();

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

bool UpdateClientByAccountNumber(string accountNumber)
{
    stClientsInfo client;

    vector <stClientsInfo> vClientData = LoadDataFromFileToVector();

    if (IsClientExisteByAccountNumber( client, accountNumber))
    {
        PrintClientInfo(client);
        char answer = Char::ReadChar("\n\nAre you sure you want to update this client? (y/n): ");

        if (toupper(answer) == 'Y')
        {
            client = ReadInfoToUpdate(accountNumber);

            LoadDataFromVectortoFile(vClientData);

            cout << "\n\nClient Updated successfully";

            return true; // process has succeeded

        }

    }
    else
    {
        cout << "\nClient with Account Number [" << accountNumber << "] is Not Found...!\n";
    }
}

void ShowUpdatedClientScreen()
{
    if (user.permessionsinBoolean.UpdateClient)
    {
        cout << "\n----------------------------------\n";
        cout << "      Update Client Info Screen  ";
        cout << "\n----------------------------------\n";

        UpdateClientByAccountNumber(ReadClientAccountNumber());
    }
    else
    {
       PrintNoAccessMessage();
    }
}

void ShowFindClientScreen()
{
    if (user.permessionsinBoolean.FindClinet)
    {
        cout << "\n----------------------------------\n";
        cout << "       Find Client  Screen";
        cout << "\n----------------------------------\n";

        string accountNumber = ReadClientAccountNumber();
        stClientsInfo client;

        if (IsClientExisteByAccountNumber( client, accountNumber))
        {
            PrintClientInfo(client);
        }
        else
        {
            cout << "\nClient with Account Number [" << accountNumber << "] is Not Found...!\n";
        }
    }
    else
    {
        PrintNoAccessMessage();
        return;
    }


}

double ReadAmount(string message)
{
    double amount;
    amount = double(Num::ReadAnyNumber(message));

    return amount;
}

double DepositOrWithdrawUsingAccountNumber( double amount, string accountNumber)
{
    vector <stClientsInfo> vClientData = LoadDataFromFileToVector();

    for (stClientsInfo& client : vClientData)
    {
        if (client.AccountNumber == accountNumber)
        {
            client.Balance += amount;
            return client.Balance;
        }

    }
}

void DespositBalanceByAccountNumber(string accountNumber)
{
    stClientsInfo client;
    vector <stClientsInfo> vClientData = LoadDataFromFileToVector();

    while (!IsClientExisteByAccountNumber( client, accountNumber))
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
        double NewBalance = DepositOrWithdrawUsingAccountNumber( amount, accountNumber);

        LoadDataFromVectortoFile(vClientData);

        cout << "\n\nDone successfully, New Balance is: " << NewBalance << endl;



    }


}

void ShowDespositScreen()
{
    cout << "\n----------------------------------\n";
    cout << "       Desposit Screen";
    cout << "\n----------------------------------\n";

    DespositBalanceByAccountNumber(ReadClientAccountNumber());
}

void WithDrawBalanceByAccountNumber(string accountNumber)
{
    stClientsInfo client;
    vector <stClientsInfo> vClientData = LoadDataFromFileToVector();

    while (!IsClientExisteByAccountNumber( client, accountNumber))
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
        double NewBalance = DepositOrWithdrawUsingAccountNumber((amount * -1), accountNumber);

        LoadDataFromVectortoFile(vClientData);

        cout << "\n\nDone successfully, New Balance is: " << NewBalance << endl;

        return;

    }


}

void ShowWithdrawScreen()
{

    cout << "\n----------------------------------\n";
    cout << "       WithDraw Screen";
    cout << "\n----------------------------------\n";

    WithDrawBalanceByAccountNumber( ReadClientAccountNumber());
}

void PerformManageUsersOptions(enManageUsersOptions option)
{

    system("cls");
    switch (option)
    {
    case (enManageUsersOptions::ListUsers):
    {
        ShowAllUsersScreen();
        GoBackToManageUsersMenue();
        break;
    }

    case (enManageUsersOptions::Adduser):
    {
        ShowAddNewUserScreen();
        GoBackToManageUsersMenue();

        break;
    }

    case (enManageUsersOptions::Deleteuser):
    {
        ShowDeleteUserScreen();
        GoBackToManageUsersMenue();
        break;
    }

    case (enManageUsersOptions::Updateuser):
    {
        ShowUpdatedUserScreen();
        GoBackToManageUsersMenue();
        break;
    }

    case (enManageUsersOptions::Finduser):
    {
        ShowFindUserScreen();
        GoBackToManageUsersMenue();
        break;
    }

    case (enManageUsersOptions::MainMenue):
    {
        system("cls");
        ShowMenue();
        break;
    }
    }
}

void ShowManageUsersMenueScreen()
{
    if (user.permessionsinBoolean.ManageUsers)
    {
        cout << "\n=================================================\n";
        cout << "           Manage Users Menue Screen                  \n";
        cout << "=================================================\n";
        cout << "\t [1] List Users \n";
        cout << "\t [2] Add New User.\n";
        cout << "\t [3] Delete User.\n";
        cout << "\t [4] Update User.\n";
        cout << "\t [5] Find User.\n";
        cout << "\t [6] Main Menue.\n";
        cout << "=================================================\n";
        PerformManageUsersOptions(enManageUsersOptions(Num::ReadAnyNumber("\nChoose what do you want to do ? [1 / 6] : ")));
    }
    else
    {
        PrintNoAccessMessage();
        return;
    }

}

void GoBackToManageUsersMenue()
{
    cout << "\n\nPress any key to go back to Manage users menue...";
    system("pause>0");

    system("cls");

    ShowManageUsersMenueScreen();
}

void ShowTransactionsScreen()
{
    if (user.permessionsinBoolean.Transaction)
    {
        cout << "\n=================================================\n";
        cout << "           Transactions Menu Screen                  \n";
        cout << "=================================================\n";
        cout << "\t [1] Desposit \n";
        cout << "\t [2] WithDraw\n";
        cout << "\t [3] Total Balances\n";
        cout << "\t [4] Main Menue\n";
        cout << "=================================================\n";

        PerformTransactionOptions(enTransactionsOptions(Num::ReadAnyNumber("\nChoose what do you want to do? [1 / 4]: ")));
    }
    else
    {
        PrintNoAccessMessage();
        return;
    }

}

void GoBackToTransactionsScreen()
{
    cout << "\n\nPress any key to go back to Transactions Menue...";
    system("pause>0");
    system("cls");
    ShowTransactionsScreen();
}

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");

    system("cls");

    ShowMenue();

}

void PerformTransactionOptions(enTransactionsOptions option)
{
    system("cls");
    switch (option)
    {
    case (enTransactionsOptions::Desposit):
    {
        ShowDespositScreen();
        GoBackToTransactionsScreen();
        break;
    }

    case (enTransactionsOptions::Withdraw):
    {
        ShowWithdrawScreen();
        GoBackToTransactionsScreen();
        break;
    }

    case (enTransactionsOptions::TotalBalances):
    {
        ShowAllClientsBalances();
        GoBackToTransactionsScreen();
        break;
    }

    case (enTransactionsOptions::MainMenueOption):
    {
        system("cls");
        ShowMenue();
    }
    }
}

void PerfromMainMenueOption(enBankOptions option)
{
    system("cls");
    switch (option)
    {
    case (enBankOptions::ShowClients):
    {
        ShowAllClientsScreen();
        GoBackToMainMenue();
        break;
    }

    case (enBankOptions::AddClient):
    {
        ShowAddNewClientsScreen();
        GoBackToMainMenue();
        break;
    }

    case (enBankOptions::DeleteClientOption):
    {
        ShowDeleteClientScreen();
        GoBackToMainMenue();
        break;
    }

    case (enBankOptions::UpdateClientOption):
    {
        ShowUpdatedClientScreen();
        GoBackToMainMenue();
        break;
    }

    case (enBankOptions::FindClientOption):
    {
        ShowFindClientScreen();
        GoBackToMainMenue();
        break;
    }

    case (enBankOptions::TransactionsOption):
    {
        ShowTransactionsScreen();
        GoBackToMainMenue();
        break;
    }

    case(enBankOptions::ManageUsersOption):
    {
        ShowManageUsersMenueScreen();
        GoBackToMainMenue();
        break;
    }

    case (enBankOptions::LogOut):
    {
        Login();
        break;
    }
    }
}

void ShowMenue()
{
    vector < stUserInfo> vUsersInfo = LoadDataFromFileToVectorForUsers();
    system("cls");

    cout << "\n=================================================\n";
    cout << "               Main Menu Screen                  \n";
    cout << "=================================================\n";
    cout << "\t [1] Show Client List. \n";
    cout << "\t [2] Add New Client.\n";
    cout << "\t [3] Delete Client\n";
    cout << "\t [4] Update Client Info.\n";
    cout << "\t [5] Find Client.\n";
    cout << "\t [6] Transactions.\n";
    cout << "\t [7] Manage Users.\n";
    cout << "\t [8] Logout\n";
    cout << "=================================================\n";

    // This function is responsible for perforaming functions and apply user orders
    PerfromMainMenueOption(enBankOptions(Num::ReadAnyNumber("\nChoose what do you want to do ? [1 / 8] : ")));


}

void ShowLoginScreen()
{
    cout << "----------------------------------\n";
    cout << "          Login Screen              \n";
    cout << "----------------------------------\n";

}

void Login()
{
    vector <stUserInfo> User = LoadDataFromFileToVectorForUsers();
    vector <stClientsInfo> vClientsInfo = LoadDataFromFileToVector();


    ShowLoginScreen();
    string username, password;
    ReadUserNameAndPassword(username, password);

    while (!IsUserExisted(username, password, user))
    {
        cout << "\nInvalid username/Password!\n";
        ReadUserNameAndPassword(username, password);
    }

    ShowMenue();

}



int main()
{
    Login();




    return 0;
}
