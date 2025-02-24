#include "Customer.h"
#include "Cart.h"
#include "Product.h"
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

Customer::Customer(const std::string& uname, const std::string& pass)
    : User(uname, pass) {}

void Customer::customerMenu(std::map<std::string, std::vector<Product>>& productCategories, const std::string& productsFile) {
    int choice; // Επιλογή χρήστη από το μενού
    do {
        // Εμφάνιση του μενού επιλογών για τον πελάτη
        std::cout << "\n--- Customer Menu ---\n";
        std::cout << "1. Search for Products\n"; // Αναζήτηση προϊόντων
        std::cout << "2. Add Product to Cart\n"; // Προσθήκη προϊόντος στο καλάθι
        std::cout << "3. Update Cart\n"; // Ενημέρωση προϊόντος στο καλάθι
        std::cout << "4. Remove Product from Cart\n"; // Αφαίρεση προϊόντος από το καλάθι
        std::cout << "5. Complete Order\n"; // Ολοκλήρωση παραγγελίας
        std::cout << "6. View Order History\n"; // Προβολή ιστορικού παραγγελιών
        std::cout << "7. View Cart\n"; // Προβολή περιεχομένου καλαθιού
        std::cout << "8. Exit\n"; // Έξοδος από το μενού
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Διαχείριση της επιλογής του χρήστη
        switch (choice) {
        case 1:
            // Αναζήτηση προϊόντων
            searchProduct(productCategories);
            break;
        case 2:
            // Προσθήκη προϊόντος στο καλάθι
            addToCart(productCategories);
            break;
        case 3:
            // Ενημέρωση προϊόντος στο καλάθι
            updateCart(productCategories);
            break;
        case 4:
            // Αφαίρεση προϊόντος από το καλάθι
            removeFromCart(productCategories);
            break;
        case 5:
            // Ολοκλήρωση παραγγελίας και αποθήκευση
            completeOrder(productCategories, productsFile);
            break;
        case 6:
            // Προβολή ιστορικού παραγγελιών
            viewOrderHistory();
            break;
        case 7:
            // Προβολή περιεχομένου καλαθιού
            cart.displayCart();
            break;
        case 8:
            // Έξοδος από το μενού
            std::cout << "Exiting customer menu.\n";
            break;
        default:
            // Διαχείριση μη έγκυρης επιλογής
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8); // Επανάληψη μέχρι ο χρήστης να επιλέξει την έξοδο
}


void Customer::searchProduct(const std::map<std::string, std::vector<Product>>& productCategories) {
    int searchOption; // Επιλογή του χρήστη για τον τύπο αναζήτησης
    std::cout << "\nProduct Search Options:\n";
    std::cout << "1. Search for a specific product (by title).\n"; // Αναζήτηση προϊόντος με βάση τον τίτλο
    std::cout << "2. View the products of a specific category.\n"; // Προβολή προϊόντων μιας συγκεκριμένης κατηγορίας
    std::cout << "3. Show all the available products.\n"; // Προβολή όλων των διαθέσιμων προϊόντων
    std::cout << "Enter your choice: ";
    std::cin >> searchOption;
    std::cin.ignore(); // Καθαρισμός του buffer εισόδου

    std::vector<Product> results; // Αποθήκευση των αποτελεσμάτων αναζήτησης

    switch (searchOption) {
    case 1: { // Αναζήτηση προϊόντος με βάση τον τίτλο
        std::string query;
        std::cout << "Enter product title to search: ";
        std::getline(std::cin, query);

        // Εύρεση προϊόντων που περιέχουν τον τίτλο
        for (const auto& [category, products] : productCategories) {
            for (const auto& product : products) {
                if (product.getTitle().find(query) != std::string::npos) {
                    results.push_back(product);
                }
            }
        }
        break;
    }
    case 2: { // Προβολή προϊόντων μιας συγκεκριμένης κατηγορίας
        std::string category;
        std::cout << "Enter category: ";
        std::getline(std::cin, category);

        // Έλεγχος αν υπάρχει η κατηγορία και προσθήκη προϊόντων στα αποτελέσματα
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
    default: // Διαχείριση μη έγκυρης επιλογής
        std::cout << "Invalid choice. Returning to the main menu.\n";
        return;
    }

    // Έλεγχος αν δεν βρέθηκαν προϊόντα
    if (results.empty()) {
        std::cout << "No products found.\n";
        return;
    }

    // Εμφάνιση των αποτελεσμάτων της αναζήτησης
    std::cout << "Results: ";
    for (const auto& product : results) {
        std::cout << "\"" << product.getTitle() << "\" ";
    }
    std::cout << "\n";

    // Επιλογή προϊόντος από τα αποτελέσματα για προβολή λεπτομερειών
    std::string selectedProductTitle;
    std::cout << "Select a product title: ";
    std::getline(std::cin, selectedProductTitle);

    // Προβολή λεπτομερειών για το επιλεγμένο προϊόν
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

    // Ενημέρωση αν το προϊόν δεν βρέθηκε στα αποτελέσματα
    std::cout << "Product not found in the results.\n";
}



void Customer::addToCart(std::map<std::string, std::vector<Product>>& productCategories) {
    // Εισαγωγή του τίτλου του προϊόντος που θέλει ο χρήστης να προσθέσει στο καλάθι
    std::string title;
    int quantity;
    std::cout << "Enter the title of the product to add: ";
    std::cin.ignore(); // Καθαρισμός του buffer εισόδου
    std::getline(std::cin, title);
    std::cout << "Enter the quantity: ";
    std::cin >> quantity;

    // Αναζήτηση του προϊόντος στις κατηγορίες
    for (auto& [category, products] : productCategories) {
        for (auto& product : products) {
            if (product.getTitle() == title) { // Αν βρεθεί προϊόν με τον επιθυμητό τίτλο
                if (product.getQuantity() >= quantity) { // Ελέγχεται αν υπάρχει επαρκές απόθεμα
                    // Προσθήκη του προϊόντος στο καλάθι
                    cart.addItem(title, quantity, product.getPrice());
                    // Μείωση του διαθέσιμου αποθέματος του προϊόντος
                    product.setQuantity(product.getQuantity() - quantity);
                    std::cout << "Product added to cart!\n";
                } else {
                    // Αν το διαθέσιμο απόθεμα είναι μικρότερο από την επιθυμητή ποσότητα
                    std::cout << "Insufficient stock. Adding available quantity.\n";
                    cart.addItem(title, product.getQuantity(), product.getPrice());
                    product.setQuantity(0); // Ορισμός αποθέματος προϊόντος σε μηδέν
                }
                return; // Τέλος της συνάρτησης αφού ολοκληρωθεί η προσθήκη
            }
        }
    }

    // Αν το προϊόν δεν βρεθεί σε καμία κατηγορία
    std::cout << "Product not found.\n";
}


void Customer::updateCart(std::map<std::string, std::vector<Product>>& productCategories) {
    // Ζητά από τον χρήστη τον τίτλο του προϊόντος που θέλει να ενημερώσει στο καλάθι
    std::string title;
    std::cout << "Enter the title of the product to update: ";
    std::cin.ignore(); // Καθαρισμός του buffer εισόδου
    std::getline(std::cin, title);

    // Ελέγχει αν το προϊόν υπάρχει στο καλάθι
    if (!cart.itemExists(title)) {
        std::cout << "Product not found in the cart.\n";
        return; // Αν δεν βρεθεί, επιστρέφει χωρίς να κάνει αλλαγές
    }

    // Εύρεση της τιμής του προϊόντος από τη λίστα προϊόντων
    double price = 0.00;
    for (const auto& [category, products] : productCategories) {
        for (const auto& product : products) {
            if (product.getTitle() == title) { // Αν βρεθεί το προϊόν
                price = product.getPrice(); // Αποθηκεύει την τιμή του
                break;
            }
        }
    }

    // Αν η τιμή του προϊόντος δεν βρεθεί, επιστρέφει μήνυμα σφάλματος
    if (price == 0.0) {
        std::cout << "Error: Product price not found.\n";
        return;
    }

    // Ζητά από τον χρήστη την νέα ποσότητα
    int newQuantity;
    std::cout << "Enter the new quantity: ";
    std::cin >> newQuantity;

    // Αν η ποσότητα είναι μηδενική ή αρνητική, αφαιρεί το προϊόν από το καλάθι
    if (newQuantity <= 0) {
        std::cout << "Invalid quantity. Removing product from cart.\n";
        cart.removeItem(title, price);
    } else {
        // Διαφορετικά, ενημερώνει την ποσότητα του προϊόντος στο καλάθι
        cart.updateItem(title, newQuantity, price);
    }
}


void Customer::removeFromCart(std::map<std::string, std::vector<Product>>& productCategories) {
    // Ζητά από τον χρήστη να εισαγάγει τον τίτλο του προϊόντος που θέλει να αφαιρέσει από το καλάθι
    std::string title;
    std::cout << "Enter the title of the product to remove: ";
    std::cin.ignore(); // Καθαρισμός του buffer εισόδου
    std::getline(std::cin, title);

    // Ελέγχει αν το προϊόν υπάρχει στο καλάθι
    if (!cart.itemExists(title)) {
        std::cout << "Product not found in the cart.\n";
        return; // Αν δεν βρεθεί, επιστρέφει χωρίς να κάνει αλλαγές
    }

    // Εύρεση της τιμής του προϊόντος από τη λίστα προϊόντων
    double price = 0.00;
    for (const auto& [category, products] : productCategories) {
        for (const auto& product : products) {
            if (product.getTitle() == title) { // Αν βρεθεί το προϊόν
                price = product.getPrice(); // Αποθηκεύει την τιμή του
                break;
            }
        }
    }

    // Αν η τιμή του προϊόντος δεν βρεθεί, εμφανίζει μήνυμα σφάλματος
    if (price == 0.0) {
        std::cout << "Error: Product price not found.\n";
        return;
    }

    // Αφαιρεί το προϊόν από το καλάθι και εμφανίζει μήνυμα επιτυχίας
    cart.removeItem(title, price);
    std::cout << "Product removed from the cart.\n";
}



void Customer::completeOrder(std::map<std::string, std::vector<Product>>& productCategories, const std::string& productsFile) {
    // Στατικός μετρητής για τον αριθμό των καλαθιών
    static int cartCounter = 1;

    // Δημιουργία μιας ροής εξόδου για την αποθήκευση της παραγγελίας
    std::ostringstream order;
    order << "---CART " << cartCounter << " START---\n";

    // Εμφάνιση του περιεχομένου του καλαθιού
    cart.displayCart();

    // Καταγραφή κάθε προϊόντος και της ποσότητάς του στη ροή εξόδου
    for (const auto& [productTitle, quantity] : cart.getItems()) {
        order << quantity << " " << productTitle << "\n";
    }

    // Κλείσιμο της παραγγελίας με το συνολικό κόστος
    order << "---CART " << cartCounter << " END---\n";
    order << "Total Cost: " << cart.getTotalCost() << "\n";

    // Αποθήκευση της παραγγελίας στο αρχείο ιστορικού παραγγελιών
    std::string fileName = username + "_history.txt";
    std::ofstream outFile("files/order_history/" + fileName, std::ios::app);
    if (!outFile) {
        std::cerr << "Error: Could not open file for order history." << std::endl;
        return;
    }

    // Αύξηση του μετρητή καλαθιών και εγγραφή της παραγγελίας στο αρχείο
    cartCounter++;
    outFile << order.str();
    outFile.close();

    // Ενημέρωση του αρχείου προϊόντων με τις αλλαγές στην ποσότητα
    std::ofstream file(productsFile);
    if (!file) {
        std::cerr << "Error: Could not open file " << productsFile << " for saving products." << std::endl;
        return;
    }

    // Εγγραφή όλων των προϊόντων στο αρχείο, περιλαμβάνοντας τις νέες ποσότητες
    for (const auto& [category, products] : productCategories) {
        for (const auto& product : products) {
            file << product.getTitle() << " @ " 
                 << product.getDescription() << " @ "
                 << product.getCategory() << " @ " 
                 << product.getSubcategory() << " @ ";
            file << std::fixed << std::setprecision(2) << product.getPrice() << " @ ";
            file << product.getUnit() << " @ "
                 << product.getQuantity() << "\n";
        }
    }

    // Κλείσιμο του αρχείου προϊόντων
    file.close();

    // Μήνυμα επιτυχούς ολοκλήρωσης παραγγελίας
    std::cout << "Order completed and added to history!\n";

    // Καθαρισμός του καλαθιού
    cart.clearCart();
}


void Customer::viewOrderHistory() const {
    // Δημιουργία ονόματος αρχείου για το ιστορικό παραγγελιών του πελάτη
    std::string fileName = username + "_history.txt";

    // Άνοιγμα του αρχείου ιστορικού παραγγελιών
    std::ifstream inFile("files/order_history/" + fileName);
    if (!inFile) {
        // Εμφάνιση μηνύματος σφάλματος αν δεν μπορεί να ανοίξει το αρχείο
        std::cerr << "Error: Could not open order history file." << std::endl;
        return;
    }

    // Εμφάνιση επικεφαλίδας για το ιστορικό παραγγελιών
    std::cout << "--- Order History ---\n";

    // Ανάγνωση και εμφάνιση κάθε γραμμής από το αρχείο
    std::string line;
    while (std::getline(inFile, line)) {
        std::cout << line << std::endl;
    }

    // Κλείσιμο του αρχείου μετά την ολοκλήρωση της ανάγνωσης
    inFile.close();
}



