#ifndef BANK_H
#define BANK_H

class Bank {
    public:
        /** Initialize initial bank state */
        void init(void);

        /**
         * Deposit money to the bank account.
         * @param wallet current wallet balance (pass-by-reference)
         * @param amount amount to deposit
         * @return true if the deposit is successful, false otherwise
         */

        bool deposit(double & wallet, double amount);

        /**
         * Withdraw money from the bank account.
         * @param wallet current wallet balance (pass-by-reference)
         * @param amount amount to withdraw
         * @return true if the withdrawal is successful, false otherwise
         */
        bool withdraw(double & wallet, double amount);

        /**
         * Proceed to the next round, calculate the new balance based on the interest rate.
         */
        void next_round(void);

        /**
         * Get the current bank balance.
         * @return the current bank balance
         */
        double get_balance(void) {
            return balance;
        }

        /**
         * Get the current interest rate.
         * @return the current interest rate
         */
        double get_interest_rate(void) {
            return interest_rate;
        }

        /**
         * Set the interest rate.
         * @param rate the new interest rate
         */
        void set_interest_rate(double rate) {
            interest_rate = rate;
        }

    private:
        double balance;
        double interest_rate;
};

#endif
