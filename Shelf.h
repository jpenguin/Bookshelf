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
#include "Book.h"
#include <iostream>
#if (__cplusplus >= 201703L) // only if compiler is C++17 or newer
#include <filesystem>  //Need C++ >= 17
#include <cstring>
#endif


class Shelf {
 private:
  static constexpr int MAX_BOOKS = 1000;
  int inserted_at;
  int num_books; // The number of books in the unsorted array
  Book books[MAX_BOOKS];  // To store the raw book objects
  std::ofstream log_file;
  void clearBooks();
  int searchBookByTitle(const string &title);
  void loadBooks();
 public:
  Shelf();
  void saveBooks();
  void listBooks();
  void insertBook();
  void deleteBook();
 protected:
};

#endif //BOOKSHELF__SHELF_H_
