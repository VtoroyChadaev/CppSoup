#include "vector.hpp"
#include "../input/input.hpp"
#include <cstddef>
#include <cstdlib>
#include <cstring> // to use memcpy
#include <iostream>
#include <new>
#include <string>

namespace inp = input;

namespace vector {

template <class T>
std::string_view get_xml_content(const std::string &open_tag,
                                 const std::string &close_tag, const T &line);

Vector *get_all_xml_content(const std::string &open_tag,
                            const std::string &close_tag,
                            std::string_view &line);

Vector *create(const size_t len) {
  Vector *vector = new Vector;

  Vector &_vector = *vector;

  if (!len) {
    return vector;
  }

  _vector.elems = new int[len];
  _vector.len = len;
  return vector;
}

void input(std::istream &is, std::ostream &os, Vector &vector) {
  os << "INPUT VECTOR ELEMENTS" << std::endl;

  while (true) {
    try {
      int value = inp::get_num<int>(is, os);
      append(vector, value);
    } catch (inp::end_code &ec) {
      return;
    } catch (std::bad_alloc &ba) {
      std::cerr << "MEM ALLOC ERR" << std::endl;
      return;
    }
  }
}

void append(Vector &vector, const int value) {
  if (!vector.elems) {
    vector.elems = new int[++(vector.len)];
    vector.elems[0] = value;
    return;
  }

  int *new_arr = new int[vector.len + 1];

  for (std::size_t i = 0; i < vector.len; ++i) {
    new_arr[i] = vector.elems[i];
  }

  delete[] vector.elems;
  vector.elems = new_arr;
  vector.elems[vector.len++] = value;
}

void print(std::ostream &os, const Vector &vector) {
  os << "[";

  for (size_t i = 0; i < vector.len; ++i) {
    if (i != vector.len - 1) {
      os << vector.elems[i] << ", ";
      continue;
    }

    os << vector.elems[i];
  }

  os << "]" << std::endl;
}

void erase(Vector *vector) {
  if (vector == nullptr) {
    return;
  }

  if (!vector->elems) {
    delete vector;
    return;
  }

  delete[] vector->elems;
  delete vector;
}

Vector *str_to_v(const char *line, const std::string &arr_name,
                 const std::string &elem_name) {
  const std::string cpp_line(line);

  Vector *vector = str_to_v(cpp_line, arr_name, elem_name);

  return vector;
}

Vector *str_to_v(const std::string &line, const std::string &arr_name,
                 const std::string &elem_name) {
  auto arr_open_tag = "<" + arr_name + ">";
  auto arr_close_tag = "</" + arr_name + ">";

  auto val_open_tag = "<" + elem_name + ">";
  auto val_close_tag = "</" + elem_name + ">";

  std::string_view arr_line;
  try {
    arr_line = get_xml_content(arr_open_tag, arr_close_tag, line);
  } catch (std::out_of_range &oor) {
    std::cerr << "BROKEN XML LINE" << std::endl;
    std::cerr << "Function: " << oor.what() << std::endl;
    return nullptr;
  }

  auto values_vector =
      get_all_xml_content(val_open_tag, val_close_tag, arr_line);

  return values_vector;
}

template <class T>
std::string_view get_xml_content(const std::string &open_tag,
                                 const std::string &close_tag, const T &line) {
  auto first = line.find(open_tag);
  first += open_tag.size();

  auto last = line.find(close_tag);

  auto content = std::string_view(line);
  content = content.substr(first, last - first);

  return content;
}

Vector *get_all_xml_content(const std::string &open_tag,
                            const std::string &close_tag,
                            std::string_view &line) {
  std::size_t start_index = 0;
  Vector *values = create(0);
  Vector &_values = *values;

  while (line.size()) {
    std::string_view content;
    try {
      content = get_xml_content(open_tag, close_tag, line);
    } catch (std::out_of_range &oor) {
      std::cerr << "BROKEN XML LINE" << std::endl;
      std::cerr << "Function: " << oor.what() << std::endl;
      return values;
    }
    std::string s_content = {content.begin(), content.end()};

    int number(0);
    try {
      number = std::stoi(s_content);
    } catch (std::invalid_argument &ia) {
      std::cerr << "Can't convert data. Details:" << std::endl;
      std::cerr << ia.what() << std::endl;
      vector::erase(values); // ??????
      return nullptr;
    } catch (std::out_of_range &oor) {
      std::cerr << "TOO BIG NUMBER. Details:" << std::endl;
      std::cerr << oor.what() << std::endl;
      vector::erase(values);
      return nullptr;
    }

    append(_values, number);

    start_index = line.find(close_tag) + close_tag.size();
    if (start_index > line.size()) {
      break;
    }

    line = line.substr(start_index);
  }

  return values;
}

Vector *str_to_v(const char *line, const size_t len,
                 const std::string &arr_name, const std::string &elem_name) {
  char *c_line = (char *)std::calloc(len + 1, sizeof(char));

  if (!c_line) {
    return NULL;
  }

  std::memcpy(c_line, line, len);

  Vector *vector = str_to_v(c_line, arr_name, elem_name);
  std::free(c_line);

  return vector;
}

std::string v_to_str(const Vector &vector, const std::string &arr_name,
                     const std::string &elem_name) {
  std::string xml_line = "<" + arr_name + ">";

  for (std::size_t i = 0; i < vector.len; ++i) {
    xml_line += "<" + elem_name + ">";
    xml_line += std::to_string(vector.elems[i]);
    xml_line += "</" + elem_name + ">";
  }

  xml_line += "</" + arr_name + ">";
  return xml_line;
}

} // namespace vector
