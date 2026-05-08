#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <limits>

#include "User.h"
#include "Resource.h"
#include "Book.h"
#include "UserManager.h"
#include "borrowmanager.h"
#include "resourcemanager.h"
#include "validator.h"

using namespace std;

// ============================================================
//  LibrarySystem  –  the ONE class that runs everything.
//
//  It owns the three managers:
//    - UserManager    : accounts, login, logout
//    - ResourceManager: books (add, remove, update)
//    - BorrowManager  : borrow, return, fines
//
//  Public interface is just two functions:
//    run()   – call this from main, program loops here
//    stop()  – called automatically when user picks Exit
// ============================================================
class LibrarySystem
{
private:
    // The three managers (composition – LibrarySystem owns them)
    UserManager     users;
    ResourceManager books;
    BorrowManager   borrows;

    // File names for persistence
    const string USERS_FILE   = "users.csv";
    const string BOOKS_FILE   = "books.txt";
    const string BORROWS_FILE = "borrows.csv";

    bool running; // controls the main loop

    // ── helpers ──────────────────────────────────────────────
    void    showTitle(const string& t);
    void    printLine();
    void    pause();
    string  readLine(const string& prompt);
    int     readChoice(int lo, int hi);

    // ── menus ────────────────────────────────────────────────
    void mainMenu();
    void loginScreen();
    void registerScreen();
    void adminPanel();
    void memberPanel();

    // ── admin operations ─────────────────────────────────────
    void adminAddBook();
    void adminRemoveBook();
    void adminUpdateBook();
    void adminViewAllBooks();
    void adminViewAllUsers();
    void adminViewAllBorrows();

    // ── member operations ────────────────────────────────────
    void memberViewBooks();
    void memberBorrow();
    void memberReturn();
    void memberHistory();
    void memberProfile();
    void memberPayFine();

    // ── file I/O ─────────────────────────────────────────────
    void saveAll();
    void loadAll();

public:
    LibrarySystem();
    void run();   // call from main()
};

#endif