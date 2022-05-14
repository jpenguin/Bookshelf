//Copyright 2022 Joshua M Dye Licensed under the Educational
//Community License, Version 2.0 (the "License"); you may not use this file
//except in compliance with the License. You may obtain a copy of the License at
//
//http://opensource.org/licenses/ECL-2.0
//
// Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
//WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
//License for the specific language governing permissions and limitations under
//the License.

#ifndef BOOKSHELF__SHELF_H_
#define BOOKSHELF__SHELF_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <cstring>
#include "Book.h"
#include <iostream>
#if (__cplusplus >= 201703L)  // only if compiler is C++17 or newer
#if __has_include(<filesystem>)
#include <filesystem>  //Need C++ >= 17
#endif
#endif


class Shelf {
 private:
  static constexpr int MAX_BOOKS = 1000;
  int inserted_at;
  int num_books; // The number of books in the unsorted array
  Book books[MAX_BOOKS];  // To store the raw book objects
  std::ofstream log_file;
  /*******************************************************************************
* Function Name: clearBooks()
* Parameters:
* Return Value: void
* Purpose: Clear all sorted lists
*******************************************************************************/
  void clearBooks();
  /*******************************************************************************
 * Function Name: searchBookByTitle()
 * Parameters: string of title to be searched for
 * Return Value: int
 * Purpose: Look for the index of a book with a given title
 *******************************************************************************/
  int searchBookByTitle(const string &title);
/*******************************************************************************
 * Function Name: loadBooks()
 * Parameters: None
 * Return Value: void
 * Purpose: Load books from file into unsorted array
 *******************************************************************************/
  void loadBooks();
 public:
/*******************************************************************************
 * Function Name: Shelf()
 * Parameters: None
 * Return Value:
 * Purpose: Constructor; set up log file, call load function
 *******************************************************************************/
  Shelf();
/*******************************************************************************
 * function name: savebooks()
 * parameters: none
 * return value: void
 * purpose: Save updated list by title to file
 *******************************************************************************/
  void saveBooks();
/*******************************************************************************
 * Function Name: listBooks()
 * Parameters: None
 * Return Value: void
 * Purpose: Asks for sort type and prints correct list
 *******************************************************************************/
  void listBooks();
/*******************************************************************************
 * Function Name: main()
 * Parameters:
 * Return Value: int
 * Purpose: Inserts book into array, and pointer in sorted lists
 *******************************************************************************/
  void insertBook();
/*******************************************************************************
 * Function Name: deleteBook()
 * Parameters: None
 * Return Value: void
 * Purpose: Asks for title to be deleted, deletes index from search function
 *******************************************************************************/
  void deleteBook();
 protected:
};

#endif //BOOKSHELF__SHELF_H_
