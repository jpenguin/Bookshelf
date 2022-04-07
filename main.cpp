//
// Created by jpenguin on 4/6/22.
//
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

