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

// The prefix of the save folder
const std::string SAVE_FOLDER_PREFIX = "saves/";

/**
 * @brief returns the game logo, which is hardcoded inside the function.
 */
std::vector<std::string> parseLogo();

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
std::vector<std::string> get_saves();

/**
 * @brief Print the vector of saves aka player folders.
 */
void printvector(std::vector<std::string> avector);
#endif
