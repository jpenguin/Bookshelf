// https://forums.devx.com/showthread.php?175218-streambuf
// Created by vijayan on 11/25/10.
//

#ifndef GROCERY__TEEBUFF_H_
#define GROCERY__TEEBUFF_H_

#include <iostream>

template<typename CHAR_TYPE,
    typename TRAITS_TYPE = std::char_traits<CHAR_TYPE> >

struct basic_teebuf : public std::basic_streambuf<CHAR_TYPE, TRAITS_TYPE> {
  typedef std::basic_streambuf<CHAR_TYPE, TRAITS_TYPE> streambuf_type;
  typedef typename TRAITS_TYPE::int_type int_type;

  basic_teebuf(streambuf_type *buff_a, streambuf_type *buff_b)
      : first(buff_a), second(buff_b) {}

 protected:
  virtual int_type overflow(int_type c) {
    const int_type eof = TRAITS_TYPE::eof();
    if (TRAITS_TYPE::eq_int_type(c, eof))
      return TRAITS_TYPE::not_eof(c);
    else {
      const CHAR_TYPE ch = TRAITS_TYPE::to_char_type(c);
      if (TRAITS_TYPE::eq_int_type(first->sputc(ch), eof) ||
          TRAITS_TYPE::eq_int_type(second->sputc(ch), eof))
        return eof;
      else
        return c;
    }
  }

  virtual int sync() {
    return !first->pubsync() && !second->pubsync() ? 0 : -1;
  }

 private:
  streambuf_type *first;
  streambuf_type *second;
};

template<typename CHAR_TYPE,
    typename TRAITS_TYPE = std::char_traits<CHAR_TYPE> >
struct basic_teestream : public std::basic_ostream<CHAR_TYPE, TRAITS_TYPE> {
  typedef std::basic_ostream<CHAR_TYPE, TRAITS_TYPE> stream_type;
  typedef basic_teebuf<CHAR_TYPE, TRAITS_TYPE> streambuff_type;

  basic_teestream(stream_type &first, stream_type &second)
      : stream_type(&stmbuf), stmbuf(first.rdbuf(), second.rdbuf()) {}

  ~basic_teestream() { stmbuf.pubsync(); }

 private:
  streambuff_type stmbuf;
};

typedef basic_teebuf<char> teebuf;
typedef basic_teestream<char> teestream;

#endif  // GROCERY__TEEBUFF_H_
