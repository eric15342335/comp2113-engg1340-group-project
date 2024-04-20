/**
 * @file names.h
 * @brief This file contains the definition of the names that will be used in the program.
 * @author MaxChungsh
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
const int sizeofCategoryList = 17;
/**
 * The array CategoryList is declared as extern since it will be defined in names.cpp.
 * It is not defined in names.h to avoid multiple definition errors,
 * and to follow good programming practices.
 */
extern const std::string CategoryList[sizeofCategoryList];

std::vector<std::string> generateName(unsigned int category, unsigned int num);

#endif
