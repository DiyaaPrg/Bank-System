# Bank-System
# 🏦 C++ Bank Management System

This is a console-based Bank Management System written in C++.
It allows administrators and users to manage clients, handle financial transactions, and control access through a permission-based system.

All data (clients & users) is stored in text files for persistence across sessions.

---

✨ Features
👥 User Management

Add new users with custom permissions

Update existing users

Delete users (except Admin)

Search for users

Admin user has full access by default

🧾 Client Management

Add new clients

Update client details

Delete clients

Search for clients

Display all clients with formatted table

Show total balances

💳 Transactions

Deposit money

Withdraw money (with balance checks)

Show total balances across all clients

🔐 Permissions System

Implemented using bitmasks and boolean flags

Permissions include:

Show client list

Add client

Delete client

Update client

Find client

Transactions

Manage users

Full access (-1) can be granted to any user

## 🗂 Project Structure
📁 MyBankApp/
.
├── Bank.txt       # Stores all client records
├── Users.txt      # Stores all user accounts with permissions
├── String.h       # Helper functions for string operations
├── Number.h       # Helper functions for numeric input
├── Char.h         # Helper functions for character input
├── main.cpp       # Main project file (your posted code)

