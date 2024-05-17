/// @file names.h
/// Declaration of the name generating function.
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
#ifndef NAMES_H
#define NAMES_H

#include <string>
#include <vector>

/**
 * @brief The size of the category list.
 *
 * This constant represents the size of the category list used in the program.
 * It is used to determine the number of categories in the list.
 */
const int category_list_size = 17;

/**
 * @brief List of stock categories.
 * The array category_list is declared as extern since it will be defined in names.cpp.
 * It is not defined in names.h to avoid multiple definition errors,
 * and to follow good programming practices.
 */
extern const std::string category_list[category_list_size];

std::vector<std::string> generate_name(unsigned int category, unsigned int num);

#endif
