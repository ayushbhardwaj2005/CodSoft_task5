#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool is_borrowed;

    Book(int id, string title, string author)
        : id(id), title(title), author(author), is_borrowed(false) {}
};

class Borrower {
public:
    int id;
    string name;

    Borrower(int id, string name)
        : id(id), name(name) {}
};

class Transaction {
public:
    int transaction_id;
    int book_id;
    int borrower_id;
    string type; // "borrow" or "return"

    Transaction(int transaction_id, int book_id, int borrower_id, string type)
        : transaction_id(transaction_id), book_id(book_id), borrower_id(borrower_id), type(type) {}
};

class Library {
private:
    vector<Book> books;
    vector<Borrower> borrowers;
    vector<Transaction> transactions;
    int next_book_id = 1;
    int next_borrower_id = 1;
    int next_transaction_id = 1;

public:
    void addBook(const string& title, const string& author) {
        books.emplace_back(next_book_id++, title, author);
        cout << "Book added successfully.\n";
    }

    void registerBorrower(const string& name) {
        borrowers.emplace_back(next_borrower_id++, name);
        cout << "Borrower registered successfully.\n";
    }

    void borrowBook(int borrower_id, int book_id) {
        for (auto& book : books) {
            if (book.id == book_id && !book.is_borrowed) {
                book.is_borrowed = true;
                transactions.emplace_back(next_transaction_id++, book_id, borrower_id, "borrow");
                cout << "Book borrowed successfully.\n";
                return;
            }
        }
        cout << "Book is not available for borrowing.\n";
    }

    void returnBook(int borrower_id, int book_id) {
        for (auto& book : books) {
            if (book.id == book_id && book.is_borrowed) {
                book.is_borrowed = false;
                transactions.emplace_back(next_transaction_id++, book_id, borrower_id, "return");
                cout << "Book returned successfully.\n";
                return;
            }
        }
        cout << "Book was not borrowed.\n";
    }

    void showBooks() const {
        for (const auto& book : books) {
            cout << "ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author << ", Borrowed: " << (book.is_borrowed ? "Yes" : "No") << "\n";
        }
    }

    void showBorrowers() const {
        for (const auto& borrower : borrowers) {
            cout << "ID: " << borrower.id << ", Name: " << borrower.name << "\n";
        }
    }

    void showTransactions() const {
        for (const auto& transaction : transactions) {
            cout << "Transaction ID: " << transaction.transaction_id << ", Book ID: " << transaction.book_id << ", Borrower ID: " << transaction.borrower_id << ", Type: " << transaction.type << "\n";
        }
    }
};

int main() {
    Library library;
    int choice;

    while (true) {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Register Borrower\n";
        cout << "3. Borrow Book\n";
        cout << "4. Return Book\n";
        cout << "5. Show Books\n";
        cout << "6. Show Borrowers\n";
        cout << "7. Show Transactions\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 8) break;

        switch (choice) {
            case 1: {
                string title, author;
                cout << "Enter book title: ";
                cin.ignore(); // To clear the newline character from the buffer
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                library.addBook(title, author);
                break;
            }
            case 2: {
                string name;
                cout << "Enter borrower name: ";
                cin.ignore();
                getline(cin, name);
                library.registerBorrower(name);
                break;
            }
            case 3: {
                int borrower_id, book_id;
                cout << "Enter borrower ID: ";
                cin >> borrower_id;
                cout << "Enter book ID: ";
                cin >> book_id;
                library.borrowBook(borrower_id, book_id);
                break;
            }
            case 4: {
                int borrower_id, book_id;
                cout << "Enter borrower ID: ";
                cin >> borrower_id;
                cout << "Enter book ID: ";
                cin >> book_id;
                library.returnBook(borrower_id, book_id);
                break;
            }
            case 5:
                library.showBooks();
                break;
            case 6:
                library.showBorrowers();
                break;
            case 7:
                library.showTransactions();
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
