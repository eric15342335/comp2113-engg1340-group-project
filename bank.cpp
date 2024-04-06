/**
 * @file bank.cpp
 * @brief Implementation of the Bank mechanics
 */
#include "bank.h"
// #include "random_price.h" // generate_interest_rate()

void Bank::init(void) {
    /** Initialize initial bank state */
    double balance = 0;
    // double interest_rate = generate_interest_rate();
}

bool Bank::deposit(double & wallet, double amount) {
    /**
     * Accept two parameters: current wallet balance (pass-by-reference)
     * and the amount to deposit. If the wallet has enough money, deposit
     * the amount to the bank account and return true. Otherwise, return false.
     */
    if (wallet >= amount) {
        wallet -= amount;
        balance += amount;
        return true;
    }
    /** else */ return false;
}

bool Bank::withdraw(double & wallet, double amount) {
    /*
    Accept two parameters: current wallet balance (pass-by-reference)
    and the amount to withdraw. If the bank account has enough money,
    withdraw the amount from the bank account and return true. Otherwise,
    return false.
    */
    if (balance >= amount) {
        wallet += amount;
        balance -= amount;
        return true;
    }
    /** else */ return false;
}

void Bank::next_round(void) {
    /**
     * Simply multiply the balance with the interest rate
     * Should be called when proceed to next round
     */
    balance *= (1 + interest_rate);
    return;
}
