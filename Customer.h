#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include "Product.h"
#include "Cart.h"
#include <map>
#include <vector>
#include <string>

// Η κλάση Customer αναπαριστά έναν πελάτη του συστήματος
class Customer : public User {
private:
    Cart cart; // Το καλάθι αγορών του πελάτη

public:
    // Κατασκευαστής της κλάσης Customer, αρχικοποιεί το όνομα χρήστη και τον κωδικό πρόσβασης
    Customer(const std::string& uname, const std::string& pass);

    // Επιστρέφει αν ο χρήστης είναι διαχειριστής (πάντα false για πελάτες)
    bool isAdministrator() const override { return false; }

    // Μέθοδοι ειδικές για πελάτες
    void customerMenu(std::map<std::string, std::vector<Product>>& productCategories, const std::string& productsFile); 
    // Παρουσιάζει το μενού του πελάτη και χειρίζεται τις επιλογές του

    void searchProduct(const std::map<std::string, std::vector<Product>>& productCategories); 
    // Αναζήτηση προϊόντων (κατά τίτλο, κατηγορία ή όλα τα διαθέσιμα προϊόντα)

    void addToCart(std::map<std::string, std::vector<Product>>& productCategories); 
    // Προσθέτει προϊόντα στο καλάθι αγορών

    void completeOrder(std::map<std::string, std::vector<Product>>& productCategories, const std::string& productsFile); 
    // Ολοκληρώνει την παραγγελία και αποθηκεύει το ιστορικό της

    void viewOrderHistory() const; 
    // Εμφανίζει το ιστορικό παραγγελιών του πελάτη

    void updateCart(std::map<std::string, std::vector<Product>>& productCategories); 
    // Ενημερώνει την ποσότητα προϊόντων στο καλάθι (με πρόσβαση σε κατηγορίες προϊόντων)

    void removeFromCart(std::map<std::string, std::vector<Product>>& productCategories); 
    // Αφαιρεί προϊόντα από το καλάθι (με πρόσβαση σε κατηγορίες προϊόντων)
};

#endif // CUSTOMER_H



