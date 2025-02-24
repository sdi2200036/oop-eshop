#include "Cart.h"

// Κατασκευαστής καλαθιού, αρχικοποιεί το συνολικό κόστος σε 0.00
Cart::Cart() : totalCost(0.00) {}

// Προσθήκη προϊόντος στο καλάθι
void Cart::addItem(const std::string& productTitle, int quantity, double price) {
    // Προσθέτει την ποσότητα στο αντίστοιχο προϊόν
    items[productTitle] += quantity;
    // Ενημερώνει το συνολικό κόστος
    totalCost += quantity * price;
}

// Αφαίρεση προϊόντος από το καλάθι
void Cart::removeItem(const std::string& productTitle, double price) {
    // Αναζητά το προϊόν στο καλάθι
    auto it = items.find(productTitle);
    if (it != items.end()) {
        // Μειώνει το συνολικό κόστος με βάση την ποσότητα και την τιμή του προϊόντος
        totalCost -= it->second * price;
        // Αφαιρεί το προϊόν από το καλάθι
        items.erase(it);
    }
}

// Ενημέρωση ποσότητας προϊόντος στο καλάθι
void Cart::updateItem(const std::string& productTitle, int newQuantity, double price) {
    // Αναζητά το προϊόν στο καλάθι
    auto it = items.find(productTitle);
    if (it != items.end()) {
        // Αφαιρεί το προηγούμενο κόστος του προϊόντος από το συνολικό κόστος
        totalCost -= it->second * price;
        // Ενημερώνει την ποσότητα του προϊόντος
        it->second = newQuantity;
        // Προσθέτει το νέο κόστος του προϊόντος στο συνολικό κόστος
        totalCost += newQuantity * price;
    }
}

// Εμφάνιση του περιεχομένου του καλαθιού
void Cart::displayCart() const {
    std::cout << "---CART START---\n";
    // Εμφάνιση κάθε προϊόντος και της ποσότητάς του
    for (const auto& item : items) {
        std::cout << item.second << " " << item.first << "\n";
    }
    std::cout << "---CART END---\n";
    // Εμφάνιση του συνολικού κόστους
    std::cout << "Total Cost: " << totalCost << "\n";
}

// Επιστρέφει το συνολικό κόστος του καλαθιού
double Cart::getTotalCost() const {
    return totalCost;
}

// Καθαρισμός του καλαθιού (αφαίρεση όλων των προϊόντων)
void Cart::clearCart() {
    items.clear();
    totalCost = 0.00;
}

// Ελέγχει αν ένα προϊόν υπάρχει στο καλάθι
bool Cart::itemExists(const std::string& productTitle) const {
    return items.find(productTitle) != items.end();
}

// Επιστρέφει όλα τα προϊόντα του καλαθιού
const std::map<std::string, int>& Cart::getItems() const {
    return items;
}



