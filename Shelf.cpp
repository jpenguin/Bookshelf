//
// Created by jpenguin on 4/7/22.
//

#include "Shelf.h"

using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;

void Shelf::clearBooks() { // Empty the sorted lists
  ByTitle.clear();
  ByAuthor.clear();
  BySubject.clear();
}
int Shelf::searchBookByTitle(const string &title) {  // find the index of a book
  for (int i = 0; i < num_books; i++)
    if (books[i].title == title) return i;

  return -1;
}
void Shelf::loadBooks() { //Load the previous book list
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

    log_file << books[num_books].title;
    ++num_books;
  }
  in_file.close();
}
Shelf::Shelf() {
  log_file.open("Log.txt");
  loadBooks();
}
void Shelf::saveBooks() { // Save the list with all deletions and insertions
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
void Shelf::listBooks() {
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
      cout << "\nPrinting by title\n\n";
      for (auto const &bi : ByTitle) {
        cout << "\t" << bi->title << "\n";
        cout << "\t" << bi->author << "\n";
        cout << "\t" << bi->subject << "\n\n";
      }
      break;
    case 50: // 2
      cout << "\nPrinting by author\n\n";
      for (auto const &bi : ByAuthor) {
        cout << "\t" << bi->title << "\n";
        cout << "\t" << bi->author << "\n";
        cout << "\t" << bi->subject << "\n\n";
      }
      break;
    case 51: // 3
      cout << "\nPrinting by subject\n\n";
      for (auto const &bi : BySubject) {
        cout << "\t" << bi->title << "\n";
        cout << "\t" << bi->author << "\n";
        cout << "\t" << bi->subject << "\n\n";
      }
      break;
    default:cout << "error: invalid option.\n";
  }
}
void Shelf::insertBook() {
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
  cout << book.title << " has been added.";
  log_file << book.title << " has been added.";
  // Find where book was inserted
  inserted_at = 0;
  for (auto const &bi : ByTitle) {
    if (bi->title == book.title)
      break;
    ++inserted_at;
  }
  log_file << "\n\tInserted in title array at location " << inserted_at;
  inserted_at = 0;
  for (auto const &bi : ByAuthor) {
    if (bi->title == book.title)
      break;
    ++inserted_at;
  }
  log_file << "\n\tInserted in author array at location " << inserted_at;
  inserted_at = 0;
  for (auto const &bi : BySubject) {
    if (bi->title == book.title)
      break;
    ++inserted_at;
  }
  log_file << "\n\tInserted in subject array at location " << inserted_at
         << "\n\n";

  ++num_books; // Increment total books
}
void Shelf::deleteBook() {  // delete a book
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

  cout << "book with the title '" << title << "' has been deleted.\n";
  log_file << "book with the title '" << title << "' has been deleted.\n";
}