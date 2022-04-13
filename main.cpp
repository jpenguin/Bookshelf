/*******************************************************************************
 * program name: cis65 programming assignment 4
 * created date: Apr 06 2022
 * created by: josh m dye
 * purpose: Write a program that maintains a list of books for a library.
 * The program must accept commands to make insertions and deletions in this
 * list, while simultaneously maintaining the list in alphabetical order for
 * three string type keys: Subject, Author, and Title.
 * copyright 2022 Josh M Dye licensed under the educational community license,
 * version 2.0 (the "license"); you may not use this file except in compliance
 * with the license.you may obtain a copy of the license at
 * http://www.osedu.org/licenses/ecl-2.0 unless required by applicable law or
 * agreed to in writing, software distributed under the license is distributed
 * on an "as is" basis, without warranties or conditions of any kind, either
 * express or implied. see the license for the specific language governing
 * permissions and limitations under the license.
 *******************************************************************************/


#include <iostream>
#include "Shelf.h"

using std::cin;
using std::cout;

int main() {
  char option;
  Shelf shelf;
  do {
    cout << "Option (1-Insert, 2-Delete, 3-List, Q-Quit): ";
    cin >> option;
    cin.clear();  // Clear out the cin buffer
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // Ignore any extra characters
    switch (option) {
      case 49: // 1
        shelf.insertBook();
        break;
      case 50: // 2
        shelf.deleteBook();
        break;
      case 51: // 3
        shelf.listBooks();
        break;
    }
  } while (option != 'Q' && option != 'q');

  shelf.saveBooks();// Save books to file
  return 0;
}

