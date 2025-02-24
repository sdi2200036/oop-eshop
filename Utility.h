#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <map>
#include <string>
#include <memory>
#include "Product.h"
#include "User.h"

// Δηλώνει μια συνάρτηση που φορτώνει τα προϊόντα από ένα αρχείο.
// Παίρνει ως όρισμα το όνομα του αρχείου και επιστρέφει έναν vector από αντικείμενα Product.
std::vector<Product> loadProducts(const std::string& productsFile);

// Δηλώνει μια συνάρτηση που φορτώνει τους χρήστες από ένα αρχείο.
// Παίρνει ως όρισμα το όνομα του αρχείου και επιστρέφει έναν vector από shared pointers αντικειμένων User.
std::vector<std::shared_ptr<User>> loadUsers(const std::string& usersFile);

// Δηλώνει μια συνάρτηση που φορτώνει τις κατηγορίες και τις υποκατηγορίες από ένα αρχείο.
// Παίρνει ως όρισμα το όνομα του αρχείου και επιστρέφει έναν χάρτη που αντιστοιχίζει κατηγορίες (string)
// σε έναν vector από υποκατηγορίες (strings).
std::map<std::string, std::vector<std::string>> loadCategories(const std::string& categoriesFile);

#endif // UTILITY_H


