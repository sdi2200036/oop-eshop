#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <string>
#include <filesystem>
#include "Product.h"
#include "Admin.h"

void showTop5ProductsFromHistory(const std::string& historyDirectory) {
    std::map<std::string, int> productFrequency;

    // Διατρέχουμε όλα τα αρχεία ιστορικού στον κατάλογο
    for (const auto& entry : std::filesystem::directory_iterator(historyDirectory)) {
        std::ifstream file(entry.path());
        if (!file) {
            std::cerr << "Error: Could not open history file " << entry.path() << "\n";
            continue;
        }

        std::string line;
        bool inCart = false;
        while (std::getline(file, line)) {
            // Ελέγχουμε αν ξεκινάει νέο καλάθι
            if (line.find("---CART") != std::string::npos) {
                inCart = line.find("START") != std::string::npos;
                continue;
            }

            // Αν είμαστε μέσα σε καλάθι, διαβάζουμε τα προϊόντα
            if (inCart && !line.empty()) {
                size_t spacePos = line.find(' ');
                if (spacePos != std::string::npos) {
                    std::string productTitle = line.substr(spacePos + 1); // Παίρνουμε τον τίτλο του προϊόντος
                    productFrequency[productTitle]++; // Αυξάνουμε τη συχνότητα
                }
            }
        }
        file.close();
    }

    // Μετατροπή map σε vector για ταξινόμηση
    std::vector<std::pair<std::string, int>> productsVector(productFrequency.begin(), productFrequency.end());

    // Ταξινόμηση κατά φθίνουσα σειρά συχνότητας
    std::sort(productsVector.begin(), productsVector.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    // Εμφάνιση των κορυφαίων 5 προϊόντων
    std::cout << "--- Top 5 Products ---\n";
    int count = 0;
    for (const auto& [title, freq] : productsVector) {
        if (count++ == 5) break;
        std::cout << title << " - Appeared in " << freq << " orders\n";
    }
}

Admin::Admin(const std::string& uname, const std::string& pass)
    : User(uname, pass) {}

void Admin::adminMenu(std::map<std::string, std::vector<Product>>& productCategories, const std::map<std::string, std::vector<std::string>>& categories, const std::string& productsFile) {
    int choice;
    do {
        // Εμφάνιση του μενού διαχειριστή
        std::cout << "\n--- Admin Menu ---\n";
        std::cout << "1. Add Product\n"; // Προσθήκη νέου προϊόντος
        std::cout << "2. Edit Product\n"; // Επεξεργασία υπάρχοντος προϊόντος
        std::cout << "3. Remove Product\n"; // Αφαίρεση προϊόντος
        std::cout << "4. Search Product\n"; // Αναζήτηση προϊόντος
        std::cout << "5. Show Unavailable Products\n"; // Εμφάνιση μη διαθέσιμων προϊόντων
        std::cout << "6. Show Top 5 Products\n"; // Εμφάνιση των 5 δημοφιλέστερων προϊόντων
        std::cout << "7. Exit\n"; // Έξοδος από το μενού
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Επεξεργασία επιλογής χρήστη
        switch (choice) {
        case 1:
            // Κλήση της συνάρτησης για προσθήκη προϊόντος
            addProduct(productCategories, categories, productsFile);
            break;
        case 2:
            // Κλήση της συνάρτησης για επεξεργασία προϊόντος
            editProduct(productCategories, categories, productsFile);
            break;
        case 3:
            // Κλήση της συνάρτησης για αφαίρεση προϊόντος
            removeProduct(productCategories, productsFile);
            break;
        case 4:
            // Κλήση της συνάρτησης για αναζήτηση προϊόντος
            searchProduct(productCategories);
            break;
        case 5:
            // Κλήση της συνάρτησης για εμφάνιση μη διαθέσιμων προϊόντων
            showUnavailableProducts(productCategories);
            break;
        case 6:
            // Κλήση της συνάρτησης για εμφάνιση των 5 δημοφιλέστερων προϊόντων
            showTop5ProductsFromHistory("files/order_history");
            break;
        case 7:
            // Αποθήκευση προϊόντων στο αρχείο και έξοδος
            //saveProductsToFile(productCategories, productsFile);
            std::cout << "Exiting admin menu.\n";
            break;
        default:
            // Μήνυμα για μη έγκυρη επιλογή
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7); // Επανάληψη μέχρι να επιλεχθεί η έξοδος
}


void Admin::addProduct(std::map<std::string, std::vector<Product>>& productCategories, const std::map<std::string, std::vector<std::string>>& categories, const std::string& productsFile) {
    // Δήλωση μεταβλητών για το νέο προϊόν
    std::string title, description, category, subcategory, unit;
    double price;
    int quantity;

    // Ζήτηση τίτλου προϊόντος από τον διαχειριστή
    std::cout << "Give product title: ";
    std::cin.ignore(); // Απαραίτητο για να αγνοηθεί ο χαρακτήρας '\n' από προηγούμενη είσοδο
    std::getline(std::cin, title);

    // Ζήτηση περιγραφής προϊόντος
    std::cout << "Give product description: ";
    std::getline(std::cin, description);

    // Ζήτηση κατηγορίας προϊόντος
    std::cout << "Choose a category: \n";
    for (const auto& [cat, subcats] : categories) {
        std::cout << "- " << cat << "\n"; // Εμφάνιση όλων των διαθέσιμων κατηγοριών
    }
    std::getline(std::cin, category);

    // Έλεγχος αν η κατηγορία είναι έγκυρη
    if (categories.find(category) == categories.end()) {
        std::cout << "Invalid category. Product not added.\n";
        return;
    }

    // Ζήτηση υποκατηγορίας προϊόντος
    std::cout << "Choose a subcategory: \n";
    for (const auto& subcat : categories.at(category)) {
        std::cout << "- " << subcat << "\n"; // Εμφάνιση όλων των διαθέσιμων υποκατηγοριών
    }
    std::getline(std::cin, subcategory);

    // Έλεγχος αν η υποκατηγορία είναι έγκυρη
    if (std::find(categories.at(category).begin(), categories.at(category).end(), subcategory) == categories.at(category).end()) {
        std::cout << "Invalid subcategory. Product not added.\n";
        return;
    }

    // Ζήτηση τιμής προϊόντος
    std::cout << "Give product price: ";
    std::cin >> price;

    // Ζήτηση τύπου μέτρησης (π.χ., Kg ή Unit)
    std::cout << "Give measurement type[Kg/Unit]: ";
    std::cin >> unit;

    // Ζήτηση ποσότητας για τον τύπο μέτρησης
    std::cout << "Give amount of " << unit << ": ";
    std::cin >> quantity;

    // Δημιουργία του νέου προϊόντος με τις παραπάνω πληροφορίες
    Product newProduct(title, description, category, subcategory, price, unit, quantity);

    // Προσθήκη του προϊόντος στην αντίστοιχη κατηγορία
    productCategories[category].push_back(newProduct);
    std::cout << "Product added successfully!\n";

    // Αποθήκευση των προϊόντων στο αρχείο
    saveProductsToFile(productCategories, productsFile);
}


void Admin::editProduct(std::map<std::string, std::vector<Product>>& productCategories, const std::map<std::string, std::vector<std::string>>& categories, const std::string& productsFile) {
    // Ζήτηση του τίτλου του προϊόντος που ο διαχειριστής επιθυμεί να επεξεργαστεί
    std::string title;
    std::cout << "Enter product title you wish to edit: ";
    std::cin.ignore(); // Απαραίτητο για την αφαίρεση του '\n' από προηγούμενη είσοδο
    std::getline(std::cin, title);

    // Εύρεση του προϊόντος στη λίστα των προϊόντων
    for (auto& [category, products] : productCategories) {
        for (auto& product : products) {
            if (product.getTitle() == title) { // Έλεγχος αν ο τίτλος ταιριάζει
                int fieldChoice;

                // Εμφάνιση επιλογών για την επεξεργασία του προϊόντος
                std::cout << "Enter number of field you want to edit: 1.Title 2.Description 3.Category and Subcategory 4.Price 5.Available Kg 6.Nothing\n";
                std::cin >> fieldChoice;

                if (fieldChoice == 1) {
                    // Επεξεργασία τίτλου
                    std::string newTitle;
                    std::cout << "Enter new title: ";
                    std::cin.ignore();
                    std::getline(std::cin, newTitle);
                    product.setTitle(newTitle);
                    std::cout << "Title updated successfully!\n";

                } else if (fieldChoice == 2) {
                    // Επεξεργασία περιγραφής
                    std::string newDescription;
                    std::cout << "Enter new description: ";
                    std::cin.ignore();
                    std::getline(std::cin, newDescription);
                    product.setDescription(newDescription);
                    std::cout << "Description updated successfully!\n";

                } else if (fieldChoice == 3) {
                    // Επεξεργασία κατηγορίας και υποκατηγορίας
                    std::string newCategory, newSubcategory;
                    std::cout << "Enter new category: ";
                    std::cin.ignore();
                    std::getline(std::cin, newCategory);

                    // Έλεγχος εγκυρότητας νέας κατηγορίας
                    if (categories.find(newCategory) == categories.end()) {
                        std::cout << "Invalid category. Changes not saved.\n";
                        continue;
                    }

                    std::cout << "Enter new subcategory: ";
                    std::getline(std::cin, newSubcategory);

                    // Έλεγχος εγκυρότητας νέας υποκατηγορίας
                    if (std::find(categories.at(newCategory).begin(), categories.at(newCategory).end(), newSubcategory) == categories.at(newCategory).end()) {
                        std::cout << "Invalid subcategory. Changes not saved.\n";
                        continue;
                    }

                    product.setCategory(newCategory);
                    product.setSubcategory(newSubcategory);
                    std::cout << "Category and subcategory updated successfully!\n";

                } else if (fieldChoice == 4) {
                    // Επεξεργασία τιμής
                    double newPrice;
                    std::cout << "Enter new price: ";
                    std::cin >> newPrice;
                    product.setPrice(newPrice);
                    std::cout << "Price updated successfully!\n";

                } else if (fieldChoice == 5) {
                    // Επεξεργασία ποσότητας
                    int newQuantity;
                    std::cout << "Enter new available quantity: ";
                    std::cin >> newQuantity;
                    product.setQuantity(newQuantity);
                    std::cout << "Quantity updated successfully!\n";

                } else if (fieldChoice == 6) {
                    // Έξοδος από το μενού επεξεργασίας
                    std::cout << "Exiting edit menu.\n";

                } else {
                    // Μη έγκυρη επιλογή
                    std::cout << "Invalid choice. Please try again.\n";
                }

                // Αποθήκευση αλλαγών στο αρχείο
                saveProductsToFile(productCategories, productsFile);
                return; // Έξοδος από τη συνάρτηση αφού γίνει η επεξεργασία
            }
        }
    }

    // Εμφάνιση μηνύματος αν το προϊόν δεν βρέθηκε
    std::cout << "Product not found.\n";
}



void Admin::removeProduct(std::map<std::string, std::vector<Product>>& productCategories, const std::string& productsFile) {
    // Ζήτηση τίτλου του προϊόντος που θα αφαιρεθεί
    std::string title;
    std::cout << "Enter product title to remove: ";
    std::cin.ignore(); // Απαραίτητο για την αφαίρεση του '\n' από προηγούμενη είσοδο
    std::getline(std::cin, title);

    // Αναζήτηση του προϊόντος στη λίστα προϊόντων
    for (auto& [category, products] : productCategories) {
        // Διάσχιση των προϊόντων της κατηγορίας
        for (auto it = products.begin(); it != products.end(); ++it) {
            if (it->getTitle() == title) { // Έλεγχος αν ο τίτλος ταιριάζει
                products.erase(it); // Διαγραφή του προϊόντος από τη λίστα
                std::cout << "Product removed successfully!\n";

                // Αποθήκευση αλλαγών στο αρχείο
                saveProductsToFile(productCategories, productsFile);
                return; // Έξοδος από τη συνάρτηση αφού βρεθεί και αφαιρεθεί το προϊόν
            }
        }
    }

    // Μήνυμα εάν το προϊόν δεν βρέθηκε
    std::cout << "Product not found.\n";
}


void Admin::searchProduct(const std::map<std::string, std::vector<Product>>& productCategories) {
    // Προβολή επιλογών αναζήτησης προϊόντων
    int searchOption;
    std::cout << "\nProduct Search Options:\n";
    std::cout << "1. Search for a specific product (by title).\n"; // Αναζήτηση προϊόντος με βάση τον τίτλο
    std::cout << "2. View the products of a specific category.\n"; // Προβολή προϊόντων συγκεκριμένης κατηγορίας
    std::cout << "3. Show all the available products.\n"; // Προβολή όλων των διαθέσιμων προϊόντων
    std::cout << "4. Show unavailable products.\n"; // Προβολή μη διαθέσιμων προϊόντων
    std::cout << "Enter your choice: ";
    std::cin >> searchOption;
    std::cin.ignore(); // Καθαρισμός εισόδου

    std::vector<Product> results; // Αποθήκευση αποτελεσμάτων αναζήτησης

    switch (searchOption) {
    case 1: { // Αναζήτηση κατά τίτλο
        std::string query;
        std::cout << "Enter product title to search: ";
        std::getline(std::cin, query);

        // Αναζήτηση προϊόντων που περιέχουν τον τίτλο αναζήτησης
        for (const auto& [category, products] : productCategories) {
            for (const auto& product : products) {
                if (product.getTitle().find(query) != std::string::npos) {
                    results.push_back(product);
                }
            }
        }
        break;
    }
    case 2: { // Προβολή προϊόντων συγκεκριμένης κατηγορίας
        std::string category;
        std::cout << "Enter category: ";
        std::getline(std::cin, category);

        // Έλεγχος αν η κατηγορία υπάρχει
        if (productCategories.find(category) != productCategories.end()) {
            results = productCategories.at(category);
        } else {
            std::cout << "Category not found.\n";
            return;
        }
        break;
    }
    case 3: { // Προβολή όλων των διαθέσιμων προϊόντων
        for (const auto& [category, products] : productCategories) {
            results.insert(results.end(), products.begin(), products.end());
        }
        break;
    }
    case 4: { // Προβολή προϊόντων που είναι απόθεμα 0
        for (const auto& [category, products] : productCategories) {
            for (const auto& product : products) {
                if (product.getQuantity() == 0) {
                    results.push_back(product);
                }
            }
        }
        break;
    }
    default:
        std::cout << "Invalid choice. Returning to the main menu.\n";
        return;
    }

    // Έλεγχος αν υπάρχουν αποτελέσματα
    if (results.empty()) {
        std::cout << "No products found.\n";
        return;
    }

    // Προβολή αποτελεσμάτων
    std::cout << "Results: ";
    for (const auto& product : results) {
        std::cout << "\"" << product.getTitle() << "\" ";
    }
    std::cout << "\n";

    // Επιλογή προϊόντος για προβολή λεπτομερειών
    std::string selectedProductTitle;
    std::cout << "Select a product title to view details: ";
    std::getline(std::cin, selectedProductTitle);

    // Εύρεση και προβολή λεπτομερειών του επιλεγμένου προϊόντος
    for (const auto& product : results) {
        if (product.getTitle() == selectedProductTitle) {
            std::cout << "-----" << product.getTitle() << "-----\n";
            std::cout << "Description: " << product.getDescription() << "\n";
            std::cout << "Category: " << product.getCategory() << "\n";
            std::cout << "Subcategory: " << product.getSubcategory() << "\n";
            std::cout << "Price per unit: " << product.getPrice() << "\n";
            std::cout << "Total units available: " << product.getQuantity() << "\n";
            return;
        }
    }

    // Μήνυμα αν το επιλεγμένο προϊόν δεν βρέθηκε
    std::cout << "Product not found in the results.\n";
}



void Admin::showUnavailableProducts(const std::map<std::string, std::vector<Product>>& productCategories) {
    // Εμφάνιση τίτλου για τα μη διαθέσιμα προϊόντα
    std::cout << "--- Unavailable Products ---\n";

    // Διάσχιση όλων των κατηγοριών και των προϊόντων τους
    for (const auto& [category, products] : productCategories) {
        for (const auto& product : products) {
            // Έλεγχος αν η ποσότητα του προϊόντος είναι 0 (μη διαθέσιμο)
            if (product.getQuantity() == 0) {
                // Εμφάνιση των λεπτομερειών του προϊόντος
                product.display();
                std::cout << "--------------------------\n"; // Διαχωριστική γραμμή για εμφάνιση
            }
        }
    }
}


void Admin::saveProductsToFile(const std::map<std::string, std::vector<Product>>& productCategories, const std::string& productsFile) {
    // Άνοιγμα του αρχείου για αποθήκευση των προϊόντων
    std::ofstream file(productsFile);
    if (!file) {
        // Μήνυμα σφάλματος αν δεν είναι δυνατή η πρόσβαση στο αρχείο
        std::cerr << "Error: Could not open file " << productsFile << " for saving products." << std::endl;
        return;
    }

    // Διάσχιση όλων των κατηγοριών και των προϊόντων τους
    for (const auto& [category, products] : productCategories) {
        for (const auto& product : products) {
            // Γράψιμο των λεπτομερειών κάθε προϊόντος στο αρχείο
            file << product.getTitle() << " @ "  // Τίτλος προϊόντος
                 << product.getDescription() << " @ " // Περιγραφή προϊόντος
                 << product.getCategory() << " @ " // Κατηγορία προϊόντος
                 << product.getSubcategory() << " @ "; // Υποκατηγορία προϊόντος

            // Γράψιμο τιμής προϊόντος με δύο δεκαδικά ψηφία
            file << std::fixed << std::setprecision(2) << product.getPrice() << " @ ";

            // Γράψιμο μονάδας μέτρησης και ποσότητας
            file << product.getUnit() << " @ " 
                 << product.getQuantity() << "\n"; // Νέα γραμμή για το επόμενο προϊόν
        }
    }

    // Κλείσιμο του αρχείου
    file.close();

    // Μήνυμα επιτυχίας
    std::cout << "All products saved to " << productsFile << " successfully!\n";
}





