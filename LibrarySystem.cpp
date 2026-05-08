/*
 * LibrarySystem.cpp
 * -----------------
 * This file contains ALL the menu logic for the Library
 * Management System. main.cpp just creates one LibrarySystem
 * object and calls run(). Everything else happens here.
 *
 * OOP concepts used here:
 *   Composition       – LibrarySystem owns UserManager,
 *                       ResourceManager, BorrowManager
 *   Exception Handling – every user-input block uses try/catch
 *   Method Overriding  – book->display() calls Book::display()
 *                        not Resource::display()
 */

#include "LibrarySystem.h"

// ============================================================
//  CONSTRUCTOR  –  just set running flag to false
// ============================================================
LibrarySystem::LibrarySystem() : running(false) {}

// ============================================================
//  PUBLIC: run()  –  load data, show menu, save on exit
// ============================================================
void LibrarySystem::run()
{
    loadAll();

    cout << "\n  ==========================================\n";
    cout << "     LIBRARY MANAGEMENT SYSTEM\n";
    cout << "  ==========================================\n";

    running = true;
    while (running)
        mainMenu();

    saveAll();
    cout << "\n  Data saved. Goodbye!\n\n";
}

// ============================================================
//  HELPERS
// ============================================================

void LibrarySystem::showTitle(const string& t)
{
    cout << "\n  +------------------------------------------+\n";
    cout << "  |  " << left << setw(40) << t << "|\n";
    cout << "  +------------------------------------------+\n\n";
}

void LibrarySystem::printLine()
{
    cout << "  ------------------------------------------\n";
}

// Wait for Enter before going back to menu
void LibrarySystem::pause()
{
    cout << "\n  Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Read a full line safely (handles leftover newlines)
string LibrarySystem::readLine(const string& prompt)
{
    string input;
    cout << "  " << prompt;
    getline(cin >> ws, input);
    return trim(input);
}

// Keep asking until a valid number is entered
int LibrarySystem::readChoice(int lo, int hi)
{
    int ch;
    while (true)
    {
        cout << "\n  Choice: ";
        if (cin >> ch && ch >= lo && ch <= hi)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return ch;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Enter a number " << lo << " to " << hi << ": ";
    }
}

// ============================================================
//  FILE I/O
// ============================================================

void LibrarySystem::loadAll()
{
    users.load_from_file(USERS_FILE);
    books.Load_File(BOOKS_FILE);
    // borrows need users + resources already loaded
    // BorrowManager::loadFromFile matches by username & resource ID
}

void LibrarySystem::saveAll()
{
    users.save_in_file(USERS_FILE);
    books.Store_file(BOOKS_FILE);
    borrows.saveToFile(BORROWS_FILE);
}

// ============================================================
//  MAIN MENU
// ============================================================
void LibrarySystem::mainMenu()
{
    showTitle("MAIN MENU");
    cout << "  1. Login\n";
    cout << "  2. Register\n";
    cout << "  0. Exit\n";

    switch (readChoice(0, 2))
    {
        case 1: loginScreen();    break;
        case 2: registerScreen(); break;
        case 0: running = false;  break;
    }
}

// ============================================================
//  LOGIN
// ============================================================
void LibrarySystem::loginScreen()
{
    showTitle("LOGIN");

    string uname = readLine("Username : ");
    string pass  = readLine("Password : ");

    User* u = users.login(uname, pass);

    if (!u)
    {
        cout << "\n  Wrong username or password.\n";
        pause();
        return;
    }

    cout << "\n  Welcome, " << u->get_firstname() << "!\n";

    // Admin IDs start with 'A', member IDs start with 'U'
    if (u->get_ID()[0] == 'A')
        adminPanel();
    else
        memberPanel();

    users.logout();
}

// ============================================================
//  REGISTER  –  each field is validated instantly as user types
// ============================================================
void LibrarySystem::registerScreen()
{
    showTitle("REGISTER");

    // validatestring() keeps asking the SAME field until input is correct.
    // It never moves to the next field until this one passes.
    // This is why we use it instead of readLine() here.

    // Each lambda below asks the field, validates it instantly,
    // and keeps re-asking until the user gives a correct value.
    auto ask = [](const string& prompt, void(*validate)(const string&)) -> string
    {
        while (true)
        {
            string input;
            cout << prompt;
            getline(cin >> ws, input);
            try   { validate(input); return input; }
            catch (const exception& e)
            { cout << "  Error: " << e.what() << " Try again.\n"; }
        }
    };

    string uname = ask("  Username             : ", Validator::validateNotEmpty);
    string pass  = ask("  Password             : ", Validator::validatePassword);
    string fname = ask("  First Name           : ", Validator::validateName);
    string lname = ask("  Last Name            : ", Validator::validateName);
    string email = ask("  Email                : ", Validator::validateEmail);
    string cnic  = ask("  CNIC (13 digits)     : ", Validator::validateCNIC);
    string addr  = ask("  Address              : ", Validator::validateNotEmpty);
    string phone = ask("  Phone (03XX-XXXXXXX) : ", Validator::validatephone);

    cout << "\n  Role:  1. Member   2. Admin\n";
    int r = readChoice(1, 2);
    UserManager::Role role = (r == 2) ? UserManager::ADMIN : UserManager::USER;

    User* u = users.registerUser(uname, pass, fname, lname,
                                 email, cnic, addr, phone, role);
    if (!u)
        cout << "\n  Username already taken.\n";
    else
        cout << "\n  Account created! Your ID: " << u->get_ID() << "\n";

    pause();
}

// ============================================================
//  ADMIN PANEL
// ============================================================
void LibrarySystem::adminPanel()
{
    while (true)
    {
        showTitle("ADMIN PANEL");
        cout << "  1. Add Book\n";
        cout << "  2. Remove Book\n";
        cout << "  3. Update Book\n";
        cout << "  4. View All Books\n";
        printLine();
        cout << "  5. View All Members\n";
        cout << "  6. View All Borrow Records\n";
        printLine();
        cout << "  7. Save Data\n";
        cout << "  0. Logout\n";

        switch (readChoice(0, 7))
        {
            case 1: adminAddBook();        break;
            case 2: adminRemoveBook();     break;
            case 3: adminUpdateBook();     break;
            case 4: adminViewAllBooks();   break;
            case 5: adminViewAllUsers();   break;
            case 6: adminViewAllBorrows(); break;
            case 7:
                saveAll();
                cout << "\n  Saved.\n";
                pause();
                break;
            case 0: return;
        }
    }
}

// ============================================================
//  MEMBER PANEL
// ============================================================
void LibrarySystem::memberPanel()
{
    while (true)
    {
        showTitle("MEMBER PANEL");
        cout << "  1. View Available Books\n";
        cout << "  2. Borrow a Book\n";
        cout << "  3. Return a Book\n";
        cout << "  4. My Borrow History\n";
        printLine();
        cout << "  5. My Profile\n";
        cout << "  6. Pay Fine\n";
        printLine();
        cout << "  0. Logout\n";

        switch (readChoice(0, 6))
        {
            case 1: memberViewBooks();  break;
            case 2: memberBorrow();     break;
            case 3: memberReturn();     break;
            case 4: memberHistory();    break;
            case 5: memberProfile();    break;
            case 6: memberPayFine();    break;
            case 0: return;
        }
    }
}

// ============================================================
//  ADMIN OPERATIONS
// ============================================================

void LibrarySystem::adminAddBook()
{
    showTitle("ADD BOOK");
    try
    {
        string title = readLine("Title     : ");
        string auth  = readLine("Author    : ");
        string cat   = readLine("Category  : ");
        string pub   = readLine("Publisher : ");
        string isbn  = readLine("ISBN      : ");

        // Book inherits from Resource  ← Inheritance (OOP concept)
        Book* b = new Book(pub, isbn, "", title, auth, cat);
        b->set_ID();            // auto-generate unique ID
        books.Add_Resource(b);  // ResourceManager takes ownership

        cout << "\n  Book added. ID: " << b->get_ID() << "\n";
    }
    catch (const exception& e)
    {
        cout << "\n  Error: " << e.what() << "\n";
    }
    pause();
}

void LibrarySystem::adminRemoveBook()
{
    showTitle("REMOVE BOOK");
    string id = readLine("Book ID to remove: ");

    if (books.Remove_Resource(id))
        cout << "\n  Book removed.\n";
    else
        cout << "\n  ID not found.\n";

    pause();
}

void LibrarySystem::adminUpdateBook()
{
    showTitle("UPDATE BOOK");
    string id = readLine("Book ID to update: ");

    Resource* b = nullptr;
    try { b = books.search_by_id(id); }
    catch (const exception& e)
    {
        cout << "\n  " << e.what() << "\n";
        pause();
        return;
    }

    // display() is a virtual function overridden in Book  ← Method Overriding
    cout << "\n  Current details:\n";
    b->display();

    cout << "\n  Change:  1.Title  2.Author  3.Category  4.Publisher  5.ISBN  0.Cancel\n";
    int ch = readChoice(0, 5);
    if (ch == 0) return;

    string val = readLine("New value: ");

    // Map number to enum (enum is now in resourcemanager.h so main can see it too)
    resourcefield f;
    switch (ch)
    {
        case 1: f = resourcefield::TITLE;     break;
        case 2: f = resourcefield::AUTHOR;    break;
        case 3: f = resourcefield::CATEGORY;  break;
        case 4: f = resourcefield::PUBLISHER; break;
        default:f = resourcefield::ISBN;      break;
    }

    try { books.Update_Resource(b, val, f); }
    catch (const exception& e) { cout << "\n  " << e.what() << "\n"; }

    pause();
}

void LibrarySystem::adminViewAllBooks()
{
    showTitle("ALL BOOKS");
    books.display_All();
    pause();
}

void LibrarySystem::adminViewAllUsers()
{
    showTitle("ALL MEMBERS");

    const vector<User*>& all = users.getAllUsers();
    if (all.empty()) { cout << "  No members yet.\n"; pause(); return; }

    cout << "  " << left
         << setw(8)  << "ID"
         << setw(15) << "Username"
         << setw(20) << "Name"
         << setw(9)  << "Borrowed"
         << "Fine\n";
    printLine();

    for (User* u : all)
    {
        cout << "  " << left
             << setw(8)  << u->get_ID()
             << setw(15) << u->get_Username()
             << setw(20) << (u->get_firstname() + " " + u->get_lastname())
             << setw(9)  << u->getBorrowedCount()
             << "Rs " << u->getFine() << "\n";
    }
    pause();
}

void LibrarySystem::adminViewAllBorrows()
{
    showTitle("ALL BORROW RECORDS");
    borrows.showAllRecords();
    pause();
}

// ============================================================
//  MEMBER OPERATIONS
// ============================================================

void LibrarySystem::memberViewBooks()
{
    showTitle("AVAILABLE BOOKS");
    books.display_All();   // display() shows availability status per book
    pause();
}

void LibrarySystem::memberBorrow()
{
    showTitle("BORROW A BOOK");
    User* me = users.getCurrentUser();

    // Check borrow limit
    if (!me->canBorrow())
    {
        cout << "  Limit reached (" << me->getMaxLimit() << " books max).\n";
        pause(); return;
    }
    // Check unpaid fine
    if (me->getFine() > 0)
    {
        cout << "  You have an unpaid fine of Rs "
             << me->getFine() << ". Pay it first.\n";
        pause(); return;
    }

    books.display_All();
    string id = readLine("\nEnter Book ID to borrow: ");

    Resource* b = nullptr;
    try { b = books.search_by_id(id); }
    catch (const exception& e)
    {
        cout << "\n  " << e.what() << "\n";
        pause(); return;
    }

    borrows.issueBook(me, b);

    // issueBook sets availability to false on success
    if (!b->get_availability())
        me->borrowBook();

    pause();
}

void LibrarySystem::memberReturn()
{
    showTitle("RETURN A BOOK");
    User* me = users.getCurrentUser();

    cout << "  Your current borrows:\n";
    borrows.showUserRecords(me);

    string id = readLine("\nEnter Book ID to return: ");
    borrows.returnBook(me, id);
    me->returnBook();

    pause();
}

void LibrarySystem::memberHistory()
{
    showTitle("MY BORROW HISTORY");
    borrows.showUserRecords(users.getCurrentUser());
    pause();
}

void LibrarySystem::memberProfile()
{
    showTitle("MY PROFILE");
    User* me = users.getCurrentUser();

    cout << "  ID       : " << me->get_ID()        << "\n";
    cout << "  Username : " << me->get_Username()  << "\n";
    cout << "  Name     : " << me->get_firstname()
                            << " " << me->get_lastname() << "\n";
    cout << "  Email    : " << me->get_Email()     << "\n";
    cout << "  Phone    : " << me->get_phone()     << "\n";
    cout << "  Balance  : Rs " << me->get_balance()<< "\n";
    cout << "  Borrowed : " << me->getBorrowedCount()
         << " / " << me->getMaxLimit() << "\n";
    cout << "  Fine     : Rs " << me->getFine()    << "\n";

    pause();
}

void LibrarySystem::memberPayFine()
{
    showTitle("PAY FINE");
    User* me = users.getCurrentUser();

    cout << "  Current fine: Rs " << me->getFine() << "\n\n";

    if (me->getFine() <= 0)
    {
        cout << "  No fines. All clear!\n";
        pause(); return;
    }

    try
    {
        double amt = stod(readLine("Amount to pay (Rs): "));
        if (amt <= 0) throw invalid_argument("Amount must be positive.");
        me->payFine(amt);
        cout << "\n  Done. Remaining fine: Rs " << me->getFine() << "\n";
    }
    catch (const exception& e)
    {
        cout << "\n  Error: " << e.what() << "\n";
    }

    pause();
}