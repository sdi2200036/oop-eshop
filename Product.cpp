#include "Product.h"

// Κατασκευαστής της κλάσης Product
Product::Product(const std::string& t, const std::string& desc, const std::string& cat, const std::string& subcat, double pr, const std::string& u, int quantity)
    : title(t), description(desc), category(cat), subcategory(subcat), price(pr), unit(u), quantity(quantity) {}

// Επιστρέφει τον τίτλο του προϊόντος
std::string Product::getTitle() const {
    return title;
}

// Επιστρέφει την περιγραφή του προϊόντος
std::string Product::getDescription() const {
    return description;
}

// Επιστρέφει την κατηγορία του προϊόντος
std::string Product::getCategory() const {
    return category;
}

// Επιστρέφει την υποκατηγορία του προϊόντος
std::string Product::getSubcategory() const {
    return subcategory;
}

// Επιστρέφει την τιμή του προϊόντος
double Product::getPrice() const {
    return price;
}

// Επιστρέφει το είδος μέτρησης του προϊόντος (π.χ. Kg ή Unit)
std::string Product::getUnit() const {
    return unit;
}

// Επιστρέφει την ποσότητα του προϊόντος
int Product::getQuantity() const {
    return quantity;
}

// Ενημερώνει την περιγραφή του προϊόντος
void Product::setDescription(const std::string& description) {
    this->description = description;
}

// Ενημερώνει την κατηγορία του προϊόντος
void Product::setCategory(const std::string& category) {
    this->category = category;
}

// Ενημερώνει την υποκατηγορία του προϊόντος
void Product::setSubcategory(const std::string& subcategory) {
    this->subcategory = subcategory;
}

// Ενημερώνει την τιμή του προϊόντος
void Product::setPrice(double newPrice) {
    price = newPrice;
}

// Ενημερώνει την ποσότητα του προϊόντος
void Product::setQuantity(int quantity) {
    this->quantity = quantity;
}

// Ενημερώνει τον τίτλο του προϊόντος
void Product::setTitle(const std::string& title) {
    this->title = title;
}

// Ενημερώνει πολλά χαρακτηριστικά του προϊόντος ταυτόχρονα
void Product::update(const std::string& desc, const std::string& subcat, double pr, const std::string& u, int qty) {
    description = desc;
    subcategory = subcat;
    price = pr;
    unit = u;
    quantity = qty;
}

// Εμφανίζει τις λεπτομέρειες του προϊόντος
void Product::display() const {
    std::cout << "Title: " << title << "\n"
              << "Description: " << description << "\n"
              << "Category: " << category << "\n"
              << "Subcategory: " << subcategory << "\n"
              << "Price: " << price << "\n"
              << "Unit: " << unit << "\n"
              << "Quantity: " << quantity << "\n";
}

