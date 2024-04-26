/**
 * @file file_io.h
 * @brief This file contains the process of loading, saving and deleting saves
 * status.
 * @author comet13579, eric15432235
 */

#ifndef FILE_IO_H
#define FILE_IO_H
#include "stock.h"

// linker command failed with exit code 1 (use -v to see invocation)
// https://stackoverflow.com/questions/12573816/linker-command-failed-with-exit-code-1-use-v-to-see-invocation

/**
 * @brief Loads the logo from "logo.txt" and returns a vector of string containing the
 * logo.
 */
std::vector<std::string> parseLogo();

/**
 * @brief Create a player folder.
 * create a folder while returning playerName by reference
 */
void createplayer(std::string & playerName);

/**
 * @brief Save the game status into .save files.
 * @param rounds_played The number of rounds played
 * @param stocks_list A vector of stocks
 * @param balance The balance of the player
 * @param playerName The name of the player also the folder name
 */
void savestatus(unsigned int rounds_played, std::vector<Stock> stocks_list,
    float balance, std::string playerName);

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
