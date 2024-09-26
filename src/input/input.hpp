/// \copyright Distributed under the MIT software license
#ifndef INPUT_HPP
#define INPUT_HPP
#include <cstring>
#include <iostream>
#include <limits>
#include <string>

namespace input {

using end_code = std::string;

void clear_stream(std::istream &is);

/**
 \brief gets bounded number from input stream
 \param is input stream
 \param os output stream
 \param min lower bound of range
 \param max upper bound of range
 \param prompt sends message in output stream
 Function gets type T number from input stream.
 Number could be bounded with params min and max
 \throw std::runtime_error if EOF signal catched or input stream is bad
 \throw input::end_code end input, but continue program running (might be used
 to exit from loop)
*/
template <class T>
T get_num(std::istream &is, std::ostream &os,
          T min = std::numeric_limits<T>::lowest(),
          T max = std::numeric_limits<T>::max(),
          const std::string &prompt = "") {
  T number;

  while (true) {
    if (prompt != "") {
      os << prompt << std::endl;
    }

    is >> number;

    if (is.eof()) {
      throw std::runtime_error("^D");
    }

    if (is.bad()) {
      throw std::runtime_error(std::string("BAD:") + std::strerror(errno));
    }

    if (is.fail()) {
      is.clear();
      std::string message;
      is >> message;

      if (message == "end") {
        clear_stream(is);
        throw input::end_code("end");
      }

      clear_stream(is);
      os << "INP FAIL. TRY AGAIN" << std::endl;
      continue;
    }

    if (number < min || number > max) {
      clear_stream(is);
      os << "INP FAIL. TRY AGAIN" << std::endl;
      continue;
    }

    clear_stream(is);
    return number;
  }
}

inline void clear_stream(std::istream &is) {
  is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

} // namespace input

#endif
