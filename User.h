#ifndef USER_H
#define USER_H

#include <string>

// Κλάση User
// Βασική κλάση που αναπαριστά έναν χρήστη του συστήματος.
// Παρέχει βασικές λειτουργίες όπως η επαλήθευση του κωδικού πρόσβασης.
class User {
protected:
    std::string username; // Το όνομα χρήστη
    std::string password; // Ο κωδικός πρόσβασης

public:
    // Κατασκευαστής
    // Αρχικοποιεί το όνομα χρήστη και τον κωδικό πρόσβασης.
    User(const std::string& uname, const std::string& pass);

    // Καταστροφέας
    // Χρησιμοποιείται για τον καθαρισμό των πόρων (αν υπάρχουν).
    virtual ~User();

    // Επιστρέφει το όνομα χρήστη.
    std::string getUsername() const;

    // Ελέγχει αν ο παρεχόμενος κωδικός πρόσβασης είναι σωστός.
    bool checkPassword(const std::string& pass) const;

    // Καθαρά εικονική μέθοδος (pure virtual).
    // Επιστρέφει αν ο χρήστης είναι διαχειριστής.
    virtual bool isAdministrator() const = 0;
};

#endif // USER_H

