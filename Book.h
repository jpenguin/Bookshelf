//
// Define the book struct & comparison functions
// Created by jpenguin on 4/7/22.
//

#ifndef BOOKSHELF__BOOK_H_
#define BOOKSHELF__BOOK_H_

#include <set>
#include <string>


using std::string;

struct Book {
  string title;
  string author;
  string subject;
};

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

#endif //BOOKSHELF__BOOK_H_
