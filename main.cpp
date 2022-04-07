//
// Created by jpenguin on 4/6/22.
//
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <limits>
#include <string>
#include "teebuff.h"
#if (__cplusplus >= 201703L) // only if compiler is C++17 or newer
#include <filesystem>  //Need C++ >= 17
#include <cstring>
#endif

using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::string;

struct Book {
  string title;
  string author;
  string subject;
};
const int MAX_BOOKS = 1000;
int inserted_at;
int num_books; // The number of books in the unsorted array
Book books[MAX_BOOKS];  // To store the raw book objects
ofstream log_file("log.txt");
teestream teeout(log_file, cout);  // output to LOG and receipt
//  file simultaneously

// The function to sort the 3 linked lists by Title, Author & Subject
auto compareTitles = [](Book *lhs, Book *rhs) {
  return lhs->title < rhs->title;
};
auto compareAuthors = [](Book *lhs, Book *rhs) {
  return lhs->author < rhs->author;
};
auto compareSubject = [](Book *lhs, Book *rhs) {
  return lhs->subject < rhs->subject;
};

// The std::set linked lists for Title, Author & Subject
std::set<Book *, decltype(compareTitles)> ByTitle(compareTitles);
std::set<Book *, decltype(compareAuthors)> ByAuthor(compareAuthors);
std::set<Book *, decltype(compareSubject)> BySubject(compareSubject);

void clearBooks() { // Empty the sorted lists
  ByTitle.clear();
  ByAuthor.clear();
  BySubject.clear();
}

void saveBooks() { // Save the list with all deletions and insertions
  ofstream outfile("books.txt");

  /*for (int i = 0; i < num_books; i++) {
    outfile << books[i].title << "\n";
    outfile << books[i].author << "\n";
    outfile << books[i].subject << "\n";
  }*/
  for (auto const &bi : ByTitle) {
    outfile << bi->title << "\n";
    outfile << bi->author << "\n";
    outfile << bi->subject << "\n";
  }

  outfile.close();
}

// find the index of a book
int searchBookByTitle(const string &title) {
  for (int i = 0; i < num_books; i++)
    if (books[i].title == title) return i;

  return -1;
}
// delete a book
void deleteBook() {
  cout << "enter book title: ";
  string title;
  getline(cin, title);

  int index = searchBookByTitle(title);

  if (index == -1) {
    cout << "error: the book does not exist.\n";
    return;
  }

  // delete the book from the list
  for (int i = index; i < num_books - 1; ++i) books[i] = books[i + 1];

  --num_books;
  clearBooks();
  for (int i = 0; i < num_books; i++) {
    ByTitle.insert(&books[i]);
    ByAuthor.insert(&books[i]);
    BySubject.insert(&books[i]);
  }

  teeout << "book with the title '" << title << "' has been deleted."
         << "\n";
}
void insertBook() {
  // stop if max books reached
  if (num_books >= MAX_BOOKS) {
    cout << "error: maximum number of books has been reached."
         << "\n";
    return;
  }

  // gather book info
  Book book;

  cout << "enter title: ";
  getline(cin, book.title);

  cout << "enter author: ";
  getline(cin, book.author);

  cout << "enter subject: ";
  getline(cin, book.subject);

  // validate the book
  if (book.title.empty() || book.author.empty() || book.subject.empty()) {
    cout << "error: all fields are required."
         << "\n";
    return;
  }

  if (searchBookByTitle(book.title) >= 0) {
    cout << "error: book title already exists."
         << "\n";
    return;
  }

  // add the book to the list
  books[num_books] = book;
  // Add the reference to the sorted lists
  ByTitle.insert(&books[num_books]);
  ByAuthor.insert(&books[num_books]);
  BySubject.insert(&books[num_books]);
  teeout << book.title << " has been added.";
  // Find where book was inserted
  inserted_at = 0;
  for (auto const &bi : ByTitle) {
    if (bi->title == book.title)
      break;
    ++inserted_at;
  }
  teeout << "\n\tInserted in title array at location " << inserted_at;
  inserted_at = 0;
  for (auto const &bi : ByAuthor) {
    if (bi->title == book.title)
      break;
    ++inserted_at;
  }
  teeout << "\n\tInserted in author array at location " << inserted_at;
  inserted_at = 0;
  for (auto const &bi : BySubject) {
    if (bi->title == book.title)
      break;
    ++inserted_at;
  }
  teeout << "\n\tInserted in subject array at location " << inserted_at
         << "\n\n";

  ++num_books; // Increment total books
}
// print all the books to the console
void listBooks() {
  if (num_books == 0) {
    cout << "error: there are no books."
         << "\n";
    return;
  }
  cout << "select order key (1-title, 2-author, 3-subject): ";
  char option;
  cin >> option;
  cin.clear();  // Clear out the cin buffer
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  // Ignore any extra characters

  switch (option) {
    // print out the books
    case 49: // 1
      teeout << "\nPrinting by title\n\n";
      for (auto const &bi : ByTitle) {
        teeout << "\t" << bi->title << "\n";
        teeout << "\t" << bi->author << "\n";
        teeout << "\t" << bi->subject << "\n\n";
      }
      break;
    case 50: // 2
      teeout << "\nPrinting by author\n\n";
      for (auto const &bi : ByAuthor) {
        teeout << "\t" << bi->title << "\n";
        teeout << "\t" << bi->author << "\n";
        teeout << "\t" << bi->subject << "\n\n";
      }
      break;
    case 51: // 3
      teeout << "\nPrinting by subject\n\n";
      for (auto const &bi : BySubject) {
        teeout << "\t" << bi->title << "\n";
        teeout << "\t" << bi->author << "\n";
        teeout << "\t" << bi->subject << "\n\n";
      }
      break;
    default:cout << "error: invalid option.\n";
  }
}
void loadBooks() { //Load the previous book list
  num_books = 0;
  ifstream in_file;
  in_file.open("books.txt");

  clearBooks(); // Make sure lists are clear
#if (__cplusplus >= 201703L)  // only if compiler is C++17 or newer
  if (!std::filesystem::exists("books.txt")) {
    cout << "\nList not found....\n";
    in_file.close();
    insertBook();  //if no existing book list, call insertBook()
    return;
  }
#endif
  if (!in_file.is_open()) {
    cout << "error: failed to open books.txt"
         << "\n";
    exit(0);
  }

  // load the books
  Book book;

  while (getline(in_file, book.title)) {
    getline(in_file, book.author);
    getline(in_file, book.subject);

    books[num_books] = book;
    ByTitle.insert(&books[num_books]);
    ByAuthor.insert(&books[num_books]);
    BySubject.insert(&books[num_books]);

    teeout << books[num_books].title;
    ++num_books;
  }
  in_file.close();
}
int main() {
  char option;
  loadBooks();
  do {
    cout << "Option (1-Insert, 2-Delete, 3-List, Q-Quit): ";
    cin >> option;
    cin.clear();  // Clear out the cin buffer
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // Ignore any extra characters
    switch (option) {
      case 49: // 1
        insertBook();
        break;
      case 50: // 2
        deleteBook();
        break;
      case 51: // 3
        listBooks();
        break;
    }
  } while (option != 'Q' && option != 'q');

  saveBooks();// Save books to file
  return 0;
}

