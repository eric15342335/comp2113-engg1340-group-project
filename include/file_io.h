/// @file file_io.h
/// Header files for file operation functions related to the game.
/*
This program is free software: you can redistribute it and/or modify it under the
terms of the GNU Lesser General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this
program. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef FILE_IO_H
#define FILE_IO_H
#include "stock.h"

/// @brief The user save options
class USER_SAVE_OPTION {
    public:
        static const std::string NEW_GAME;
        static const std::string LOAD_GAME;
        static const std::string DELETE_GAME;
        static const std::string EXIT_GAME;
};

extern const std::string USER_SAVE_OPTION_PROMPT;

/**
 * @brief Check if the input is valid. The input is valid if it is one of the options
 * in the USER_SAVE_OPTION class.
 * @param input The input string
 * @return true if the input is valid, false otherwise
 */
inline bool checkValidInput(const std::string & input) {
    return input.compare(USER_SAVE_OPTION::NEW_GAME) == 0 ||
           input.compare(USER_SAVE_OPTION::LOAD_GAME) == 0 ||
           input.compare(USER_SAVE_OPTION::DELETE_GAME) == 0 ||
           input.compare(USER_SAVE_OPTION::EXIT_GAME) == 0;
}

// The prefix of the save folder
const std::string SAVE_FOLDER_PREFIX = "saves/";

// The extension of the save file, in plain text format
const std::string SAVE_FILE_EXTENSION_TXT = ".save";

/**
 * @brief returns the game logo, which is hardcoded inside the function.
 * @return a vector of strings, each string is a line of the logo
 */
std::vector<std::string> parseLogo(void);

/**
 * @brief Create a player folder.
 * @param playerName Pass the playerName by reference.
 */
void createplayer(std::string & playerName);

/**
 * @brief Save the game status into *.save files.
 * @param rounds_played The number of rounds played
 * @param stocks_list A vector of stocks
 * @param balance The balance of the player
 * @param playerName The name of the player also the folder name
 */
void savestatus(unsigned int rounds_played, std::vector<Stock> stocks_list,
    float balance, const std::string & playerName);

/**
 * @brief Load an existing game status from .save files. Paramenters should be empty and
 * values are returned by reference.
 * @param rounds_played The number of rounds played
 * @param stocks_list A vector of stocks
 * @param balance The balance of the player
 * @param playerName The name of the player also the folder name
 * @param hsi_history A vector of HSI history
 */
void loadstatus(unsigned int & rounds_played, std::vector<Stock> & stocks_list,
    float & balance, std::string & playerName, std::vector<float> & hsi_history);

/**
 * @brief Delete a save
 * @param mode Return the mode choice (0,1,2,3) by reference for further control after
 * deleting
 */
void delsave(std::string & mode);

/**
 * @brief Get the list of saves aka player folders.
 * @return a vector containing the name all the player folders
 */
std::vector<std::string> get_saves(void);

/**
 * @brief Print the vector of saves aka player folders.
 */
void printvector(const std::vector<std::string> & avector);

#endif
