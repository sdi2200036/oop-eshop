#include "Utility.h"
#include "Admin.h"
#include "Customer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>

// Αφαιρεί τα κενά (spaces ή tabs) από την αρχή και το τέλος μιας συμβολοσειράς.
std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

// Φορτώνει τα προϊόντα από ένα αρχείο και επιστρέφει έναν vector από αντικείμενα Product.
std::vector<Product> loadProducts(const std::string& productsFile) {
    std::vector<Product> products;
    std::ifstream file(productsFile);
    if (!file) {
        std::cerr << "Error: Could not open file " << productsFile << "\n";
        return products;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string title, description, category, subcategory, unit, priceStr, quantityStr;
        double price;
        int quantity;

        // Διαχωρίζει κάθε πεδίο από το '@'.
        std::getline(ss, title, '@');
        std::getline(ss, description, '@');
        std::getline(ss, category, '@');
        std::getline(ss, subcategory, '@');
        std::getline(ss, priceStr, '@');
        std::getline(ss, unit, '@');
        std::getline(ss, quantityStr);

        // Αφαιρεί τα περιττά κενά από τα δεδομένα.
        title = trim(title);
        description = trim(description);
        category = trim(category);
        subcategory = trim(subcategory);
        unit = trim(unit);
        priceStr = trim(priceStr);
        quantityStr = trim(quantityStr);

        // Προσπαθεί να μετατρέψει την τιμή και την ποσότητα στους αντίστοιχους τύπους.
        try {
            price = std::stod(priceStr);
            quantity = std::stoi(quantityStr);
        } catch (const std::exception& e) {
            std::cerr << "Failed to parse line: " << line << "\n";
            continue;
        }

        // Προσθέτει το προϊόν στη λίστα.
        products.emplace_back(title, description, category, subcategory, price, unit, quantity);
    }

    file.close();
    return products;
}

// Φορτώνει τους χρήστες από ένα αρχείο και επιστρέφει έναν vector από shared pointers αντικειμένων User.
std::vector<std::shared_ptr<User>> loadUsers(const std::string& usersFile) {
    std::vector<std::shared_ptr<User>> users;
    std::ifstream file(usersFile);
    if (!file) {
        std::cerr << "Error: Could not open file " << usersFile << "\n";
        return users;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string username, password;
        int isAdmin;

        // Διαβάζει τα πεδία από το αρχείο και τα αποθηκεύει στις μεταβλητές.
        std::getline(ss, username, ',');
        std::getline(ss, password, ',');
        ss >> isAdmin;

        // Δημιουργεί έναν χρήστη ανάλογα με το αν είναι διαχειριστής ή πελάτης.
        if (isAdmin) {
            users.push_back(std::make_shared<Admin>(username, password));
        } else {
            users.push_back(std::make_shared<Customer>(username, password));
        }
    }

    file.close();
    return users;
}

// Φορτώνει τις κατηγορίες και τις υποκατηγορίες από ένα αρχείο.
std::map<std::string, std::vector<std::string>> loadCategories(const std::string& categoriesFile) {
    std::map<std::string, std::vector<std::string>> categories;
    std::ifstream file(categoriesFile);
    if (!file) {
        std::cerr << "Error: Could not open file " << categoriesFile << "\n";
        return categories;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string category;

        // Διαβάζει την κατηγορία (πριν από την παρένθεση).
        std::getline(ss, category, '(');
        category = trim(category);

        // Διαβάζει τις υποκατηγορίες (μέσα στην παρένθεση).
        std::string subcategories;
        std::getline(ss, subcategories, ')');

        std::stringstream subcatStream(subcategories);
        std::string subcat;

        // Διαχωρίζει τις υποκατηγορίες με βάση το '@' και τις προσθέτει στη λίστα.
        while (std::getline(subcatStream, subcat, '@')) {
            categories[category].push_back(trim(subcat));
        }
    }

    file.close();
    return categories;
}


