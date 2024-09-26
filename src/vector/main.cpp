#include "input/input.hpp"
#include "vector/vector.hpp"
#include <cstring> //to use errno
#include <iostream>
#include <string>

namespace inp = input;
namespace vec = vector;

using switch_func = void (*)(void);
using process_func = vec::Vector *(*)(const std::string &line,
                                      const std::string &arr_name,
                                      const std::string &elem_name);

int V_TO_S = 0, S_TO_V = 1;

std::string main_indent = "\t\t\t\t";
std::string main_menu =
    main_indent + "0.VECTOR TO XML\n" + main_indent + "1.XML TO VECTOR\n";

void dialog();

void v_to_str_dialog();

void str_to_v_dialog();

vec::Vector *c_str_to_v(const std::string &line, const std::string &arr_name,
                        const std::string &elem_name);

vec::Vector *cpp_str_to_v(const std::string &line, const std::string &arr_name,
                          const std::string &elem_name);

vec::Vector *char_arr_to_v(const std::string &line, const std::string &arr_name,
                           const std::string &elem_name);

char *get_char_arr(std::size_t &len, const std::string &str);

void throw_exceptions(std::istream &stream, vec::Vector *vector);

int main() {
  dialog();
  return 0;
}

void dialog() {
  switch_func funcs[2] = {v_to_str_dialog, str_to_v_dialog};

  while (true) {
    try {
      int direction = inp::get_num<int>(std::cin, std::cout, V_TO_S, S_TO_V, main_menu);
      funcs[direction]();
    }

    catch (std::runtime_error &re) {
      std::cerr << re.what() << std::endl;
      return;
    }

    catch (std::bad_alloc &ba) {
      std::cerr << "MEM ALLOC ERR" << std::endl;
      return;
    } catch (std::exception &ex) {
      std::cerr << ex.what() << std::endl;
      return;
    }

    catch (...) {
      std::cerr << "WARNING: UNDEF EXCEPTIONED CATCHED" << std::endl;
      return;
    }
  }
}

void v_to_str_dialog() {
  vec::Vector *vector = vec::create(0);
  vec::Vector &_vector = *vector;
  try {
    vec::input(std::cin, std::cout, _vector);
  } catch (std::runtime_error &ra) {
    vec::erase(vector);
    throw ra;
  }

  std::string arr_name, elem_name;

  std::cout << "INPUT ARRAY NAME" << std::endl;
  std::getline(std::cin, arr_name, '\n');

  throw_exceptions(std::cin, vector);

  std::cout << "INPUT ELEMENT NAME" << std::endl;
  std::getline(std::cin, elem_name, '\n');

  throw_exceptions(std::cin, vector);

  auto xml_line = vec::v_to_str(_vector, arr_name, elem_name);
  std::cout << "YOUR LINE:\n" << xml_line << std::endl;

  vec::erase(vector);
}

void str_to_v_dialog() { // TODO
  std::string xml_line;
  std::string prompt = "0.STD STRING\n1.C STRING\n2.CHAR ARRAY\n";
  process_func funcs[] = {cpp_str_to_v, c_str_to_v, char_arr_to_v};
  int type = inp::get_num<int>(std::cin, std::cout, 0, 2, prompt);

  std::cout << "INPUT XML LINE" << std::endl;
  std::getline(std::cin, xml_line, '\n');

  throw_exceptions(std::cin, nullptr);

  std::string arr_name, elem_name;
  std::cout << "INPUT ARRAY NAME" << std::endl;
  std::getline(std::cin, arr_name, '\n');

  throw_exceptions(std::cin, nullptr);

  std::cout << "INPUT ELEMENT NAME" << std::endl;
  std::getline(std::cin, elem_name, '\n');

  throw_exceptions(std::cin, nullptr);

  vec::Vector *vector = nullptr;
  
  try {
    vector = funcs[type](xml_line, arr_name, elem_name);
  } catch (std::invalid_argument &ia) {
    std::cerr << ia.what() << std::endl;
  }

  if (vector) {
    vec::Vector &_vector = *vector;
    vec::print(std::cout, _vector);
  }

  vec::erase(vector);
}

void throw_exceptions(std::istream &stream, vec::Vector *vector) {
  if (stream.eof()) {
    vec::erase(vector);
    throw std::runtime_error("^D");
  }

  if (stream.bad()) {
    vec::erase(vector);
    throw std::runtime_error(std::string("BAD:") + std::strerror(errno));
  }
}

vec::Vector *c_str_to_v(const std::string &line, const std::string &arr_name,
                        const std::string &elem_name) {
  if (!line.size()) {
    throw std::invalid_argument("EMPTY LINE");
  }

  const char *xml_line = line.c_str(); // FREE?? TODO
  vec::Vector *vector = vec::str_to_v(xml_line, arr_name, elem_name);

  return vector;
}

vec::Vector *cpp_str_to_v(const std::string &line, const std::string &arr_name,
                        const std::string &elem_name) {
  if (!line.size()) {
    throw std::invalid_argument("EMPTY LINE");
  }

  vec::Vector *vector = vec::str_to_v(line, arr_name, elem_name);

  return vector;
}

vec::Vector *char_arr_to_v(const std::string &line, const std::string &arr_name,
                        const std::string &elem_name) {
  if (!line.size()) {
    throw std::invalid_argument("EMPTY LINE");
  }

  std::size_t len = 0;
  std::size_t &_len = len;

  char *char_arr = get_char_arr(_len, line);

  if (!char_arr) {
    throw std::bad_alloc();
  }
  
  
  vec::Vector *vector = vec::str_to_v(char_arr, len, arr_name, elem_name);
  free(char_arr);

  return vector;
}

char *get_char_arr(std::size_t &len, const std::string &line) {
  char *arr = NULL;

  for (std::size_t i = 0; i < line.size(); ++i) {
    arr = (char *)std::realloc(arr, sizeof(char) * (++len));
    arr[len - 1] = line[i];
  }

  return arr;
}
