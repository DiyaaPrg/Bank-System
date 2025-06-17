# Bank-System
# 🏦 C++ Bank Management System

A command-line bank management system written in C++ that allows users to manage client data using file storage. This system is designed with modularity and clarity, featuring custom header files and a clean CLI interface.

---

## 🚀 Features

- ✅ Add, update, and delete bank clients
- 🔍 Search for clients by account number
- 💾 Save and load data from a file (`Bank.txt`)
- 🔐 Pin code and balance per client
- 📄 File format uses custom delimiters (`#...#`)
- 🧩 Modular architecture using custom header files:
  - `String.h`
  - `Number.h`
  - `Char.h`

---

## 🗂 Project Structure
📁 MyBankApp/
├── main.cpp # Main application logic
├── String.h # Custom string utilities (Split, Join, Readtext, etc.)
├── Number.h # Numeric input reader (e.g., ReadFloat)
├── Char.h # Character input helper
├── Bank.txt # Flat-file client database
└── README.md # Project documentation (this file)

