#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Product.h"
#include <map>
#include <vector>
#include <string>

// Η κλάση Admin επεκτείνει την κλάση User και προσθέτει λειτουργίες διαχειριστή
class Admin : public User {
public:
    // Κατασκευαστής για τον διαχειριστή
    Admin(const std::string& uname, const std::string& pass);

    // Μέθοδος για τον έλεγχο αν ο χρήστης είναι διαχειριστής
    bool isAdministrator() const override { return true; }

    // Μέθοδοι που αφορούν αποκλειστικά τον διαχειριστή

    // Εμφάνιση του μενού διαχειριστή
    void adminMenu(std::map<std::string, std::vector<Product>>& productCategories,
                   const std::map<std::string, std::vector<std::string>>& categories,
                   const std::string& productsFile);

    // Προσθήκη νέου προϊόντος
    void addProduct(std::map<std::string, std::vector<Product>>& productCategories,
                    const std::map<std::string, std::vector<std::string>>& categories,
                    const std::string& productsFile);

    // Επεξεργασία υπάρχοντος προϊόντος
    void editProduct(std::map<std::string, std::vector<Product>>& productCategories,
                     const std::map<std::string, std::vector<std::string>>& categories,
                     const std::string& productsFile);

    // Αφαίρεση προϊόντος από τη λίστα
    void removeProduct(std::map<std::string, std::vector<Product>>& productCategories,
                       const std::string& productsFile);

    // Αναζήτηση προϊόντων (με βάση τίτλο, κατηγορία, ή κατάσταση διαθεσιμότητας)
    void searchProduct(const std::map<std::string, std::vector<Product>>& productCategories);

    // Εμφάνιση μη διαθέσιμων προϊόντων
    void showUnavailableProducts(const std::map<std::string, std::vector<Product>>& productCategories);

    // Αποθήκευση όλων των προϊόντων σε αρχείο
    void saveProductsToFile(const std::map<std::string, std::vector<Product>>& productCategories,
                            const std::string& productsFile);
};

#endif // ADMIN_H




