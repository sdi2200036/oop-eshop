#include "User.h"

// Κατασκευαστής
User::User(const std::string& uname, const std::string& pass)
    : username(uname), password(pass) {}

// Καταστροφέας
User::~User() {
    // Αν δεν χρειάζεται να διαχειριστούμε πόρους, αφήνουμε τον καταστροφέα κενό.
}

// Επιστρέφει το όνομα χρήστη
std::string User::getUsername() const {
    return username;
}

// Ελέγχει αν ο κωδικός πρόσβασης είναι σωστός
bool User::checkPassword(const std::string& pass) const {
    return password == pass;
}


