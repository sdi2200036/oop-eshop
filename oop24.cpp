#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <memory>
#include "Utility.h"
#include "Admin.h"
#include "Customer.h"
#include "Product.h"
#include "Cart.h" 

// Ελέγχει αν το όνομα χρήστη υπάρχει ήδη στη λίστα χρηστών
bool usernameExists(const std::vector<std::shared_ptr<User>>& users, const std::string& username) {
    for (const auto& user : users) {
        if (user->getUsername() == username) { // Ελέγχει αν το όνομα χρήστη είναι ίδιο
            return true; // Επιστρέφει true αν υπάρχει
        }
    }
    return false; // Επιστρέφει false αν δεν υπάρχει
}

// Εγγραφή νέου χρήστη
void registerUser(std::vector<std::shared_ptr<User>>& users, const std::string& usersFile,
                  std::map<std::string, std::vector<Product>>& productCategories,
                  const std::map<std::string, std::vector<std::string>>& categories,
                  const std::string& productsFile) {
    std::string username, password;
    char isAdminchar;

    // Ζητάει όνομα χρήστη
    std::cout << "Enter a new username: ";
    std::cin >> username;

    if (usernameExists(users, username)) { // Ελέγχει αν υπάρχει ήδη το όνομα χρήστη
        std::cout << "Username already exists. Please try again.\n";
        return;
    }

    // Ζητάει κωδικό πρόσβασης
    std::cout << "Enter a password: ";
    std::cin >> password;
    std::cout << "Is this an admin account? (y for Yes, n for No): ";
    std::cin >> isAdminchar;

    // Ελέγχει την έγκυρη εισαγωγή για το admin status
    while (isAdminchar != 'y' && isAdminchar != 'n') {
        std::cout << "Invalid input. Please enter 'y' for Yes or 'n' for No: ";
        std::cin >> isAdminchar;
    }

    bool isAdmin = (isAdminchar == 'y');

    // Ανοίγει το αρχείο χρηστών για προσθήκη
    std::ofstream file(usersFile, std::ios::app);
    if (!file) {
        std::cerr << "Error: Could not open file for writing.\n";
        return;
    }

    // Γράφει τα δεδομένα του νέου χρήστη στο αρχείο
    file << username << "," << password << "," << (isAdmin ? 1 : 0) << "\n";
    file.close();

    if (isAdmin) { // Αν είναι admin, τον οδηγεί στο μενού admin
        auto newAdmin = std::make_shared<Admin>(username, password);
        users.push_back(newAdmin);
        std::cout << "User registered successfully! Logging in as an admin...\n";
        newAdmin->adminMenu(productCategories, categories, productsFile);
    } else { // Αν είναι πελάτης, τον οδηγεί στο μενού πελάτη
        auto newCustomer = std::make_shared<Customer>(username, password);
        users.push_back(newCustomer);
        std::cout << "User registered successfully! Logging in as a customer...\n";
        newCustomer->customerMenu(productCategories, productsFile);
    }

    std::cout << "User registered successfully!\n";
}

// Σύνδεση χρήστη
void loginMenu(const std::vector<std::shared_ptr<User>>& users, 
               std::map<std::string, std::vector<Product>>& productCategories,
               const std::map<std::string, std::vector<std::string>>& categories,
               const std::string& productsFile) {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    for (const auto& user : users) {
        if (user->getUsername() == username && user->checkPassword(password)) { // Ελέγχει τα στοιχεία σύνδεσης
            if (user->isAdministrator()) { // Αν είναι admin
                std::cout << "Welcome, Admin!\n";
                auto admin = std::dynamic_pointer_cast<Admin>(user);
                admin->adminMenu(productCategories, categories, productsFile);
            } else { // Αν είναι πελάτης
                std::cout << "Welcome, Customer!\n";
                auto customer = std::dynamic_pointer_cast<Customer>(user);
                customer->customerMenu(productCategories, productsFile);
            }
            return; // Επιστρέφει αφού γίνει η σύνδεση
        }
    }

    std::cout << "Invalid username or password.\n";
}

int main(int argc, char* argv[]) {
    if (argc != 4) { // Ελέγχει αν τα σωστά αρχεία δόθηκαν ως παραμέτρους
        std::cerr << "Usage: ./main <categories_file> <products_file> <users_file>\n";
        return 1;
    }

    // Αποθηκεύει τα ονόματα των αρχείων
    const std::string categoriesFile = argv[1];
    const std::string productsFile = argv[2];
    const std::string usersFile = argv[3];

    // Φορτώνει τις κατηγορίες από το αρχείο
    std::map<std::string, std::vector<std::string>> categories = loadCategories(categoriesFile);
    if (categories.empty()) {
        std::cerr << "Failed to load categories. Exiting.\n";
        return 1;
    }

    // Φορτώνει τα προϊόντα και τους χρήστες από τα αρχεία
    std::vector<Product> products = loadProducts(productsFile);
    std::vector<std::shared_ptr<User>> users = loadUsers(usersFile);

    // Ταξινομεί τα προϊόντα ανά κατηγορία
    std::map<std::string, std::vector<Product>> productCategories;
    for (const auto& product : products) {
        productCategories[product.getCategory()].push_back(product);
    }

    // Εμφανίζει το αρχικό μενού σύνδεσης ή εγγραφής
    std::string choice;
    std::cout << "\n--- Welcome to the e-shop ---\n";
    std::cout << "1. Login\n";
    std::cout << "2. Register\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    if (choice == "1" || choice == "login") {
        loginMenu(users, productCategories, categories, productsFile);
    } else if (choice == "2" || choice == "register") {
        registerUser(users, usersFile, productCategories, categories, productsFile);
    } else {
        std::cout << "Invalid choice. Please try again.\n";
    }

    return 0;
}




