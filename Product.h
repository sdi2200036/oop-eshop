#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>

// Η κλάση Product αναπαριστά ένα προϊόν με βασικές λεπτομέρειες όπως τίτλος, περιγραφή, κατηγορία κ.λπ.
class Product {
private:
    std::string title; // Τίτλος του προϊόντος
    std::string description; // Περιγραφή του προϊόντος
    std::string category; // Κατηγορία του προϊόντος
    std::string subcategory; // Υποκατηγορία του προϊόντος
    double price; // Τιμή του προϊόντος
    std::string unit; // Μονάδα μέτρησης (π.χ. "Kg" ή "Unit")
    int quantity; // Διαθέσιμη ποσότητα του προϊόντος

public:
    // Κατασκευαστής για την αρχικοποίηση ενός προϊόντος
    Product(const std::string& t, const std::string& desc, const std::string& cat, const std::string& subcat, double pr, const std::string& u, int quantity);

    // Επιστρέφει τον τίτλο του προϊόντος
    std::string getTitle() const;

    // Επιστρέφει την περιγραφή του προϊόντος
    std::string getDescription() const;

    // Επιστρέφει την κατηγορία του προϊόντος
    std::string getCategory() const;

    // Επιστρέφει την υποκατηγορία του προϊόντος
    std::string getSubcategory() const;

    // Επιστρέφει την τιμή του προϊόντος
    double getPrice() const;

    // Επιστρέφει τη μονάδα μέτρησης του προϊόντος
    std::string getUnit() const;

    // Επιστρέφει την ποσότητα του προϊόντος
    int getQuantity() const;

    // Ενημερώνει τον τίτλο του προϊόντος
    void setTitle(const std::string& title);

    // Ενημερώνει την περιγραφή του προϊόντος
    void setDescription(const std::string& description);

    // Ενημερώνει την κατηγορία του προϊόντος
    void setCategory(const std::string& category);

    // Ενημερώνει την υποκατηγορία του προϊόντος
    void setSubcategory(const std::string& subcategory);

    // Ενημερώνει την τιμή του προϊόντος
    void setPrice(double newPrice);

    // Ενημερώνει την ποσότητα του προϊόντος
    void setQuantity(int quantity);

    // Ενημερώνει πολλαπλά χαρακτηριστικά του προϊόντος ταυτόχρονα
    void update(const std::string& desc, const std::string& subcat, double pr, const std::string& u, int quantity);

    // Εμφανίζει τις λεπτομέρειες του προϊόντος
    void display() const;
};

#endif


