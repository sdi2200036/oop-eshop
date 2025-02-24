#ifndef CART_H
#define CART_H

#include <string>
#include <map>
#include <iostream>

// Κλάση που αναπαριστά το καλάθι αγορών
class Cart {
private:
    std::map<std::string, int> items; // Αντιστοιχία τίτλου προϊόντος -> Ποσότητα
    double totalCost; // Συνολικό κόστος των προϊόντων στο καλάθι

public:
    // Κατασκευαστής που αρχικοποιεί το καλάθι
    Cart();

    // Προσθέτει προϊόν στο καλάθι
    void addItem(const std::string& productTitle, int quantity, double price);

    // Αφαιρεί προϊόν από το καλάθι
    void removeItem(const std::string& productTitle, double price);

    // Ενημερώνει την ποσότητα ενός προϊόντος στο καλάθι
    void updateItem(const std::string& productTitle, int newQuantity, double price);

    // Εμφανίζει το περιεχόμενο του καλαθιού (τίτλους προϊόντων, ποσότητες, συνολικό κόστος)
    void displayCart() const;

    // Επιστρέφει το συνολικό κόστος των προϊόντων στο καλάθι
    double getTotalCost() const;

    // Καθαρίζει το καλάθι (αφαιρεί όλα τα προϊόντα)
    void clearCart();

    // Ελέγχει αν ένα συγκεκριμένο προϊόν υπάρχει στο καλάθι
    bool itemExists(const std::string& productTitle) const;

    // Επιστρέφει όλα τα προϊόντα που υπάρχουν στο καλάθι
    const std::map<std::string, int>& getItems() const;
};

#endif


