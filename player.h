/**
 * @headerfile player.h
 * @brief Player class
 */

#ifndef PLAYER_H
#define PLAYER_H

/**
 * A class that stores player information, e.g. balance, stocks owned, rounds played etc.
 * To allow functions from other files to access the player's data for their own purposes.
 * E.g. Lift limits (of something) when the player reaches a certain round.
 * @class Player
 */
class Player {
    private:
        float balance;
        unsigned int rounds_played;

    public:
        void start_game(void) {
            balance = 1000;
            rounds_played = 0;
        }
        /** Designed in this way for Stock::purchase(get_balance_ptr(), ...)
         * and Stock::sell(get_balance_ptr(), ...) function
         * @return a pointer to the balance variable,
         */
        float * get_balance_ptr(void) {
            return &balance;
        }
        /** Return player balance using function with shorter name*/
        float bal(void) {
            return balance;
        }
        unsigned int get_rounds_played(void) {
            return rounds_played;
        }
        void next_round(void) {
            rounds_played++;
        }
};

#endif
