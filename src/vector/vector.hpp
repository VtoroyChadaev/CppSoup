/// \copyright Distributed under the MIT software license
#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <cstddef>
#include <string>

namespace vector {

struct Vector {
  std::size_t len = 0;
  int *elems = nullptr;
};

/** \brief creates struct Vector
 \param len size of vector
 \return ptr to struct Vector
 \throw std::bad_alloc memory allocation error

 Creates struct Vector.
 If len == 0, field elems won't be created
*/
Vector *create(const size_t len);

/** \brief fills vector with data
 \param is input stream
 \param os output stream
 \param vector vector to fill
 \throw std::bad_alloc memory allocation error

 Reads numbers from input stream and append them to vector. Separator is '\\n'.
 Input ends with keyword "end"
 \sa get_num(), append()
*/
void input(std::istream &is, std::ostream &os, Vector &vector);

/** \brief pushes value to the end of vector
 \param vector vector to expand
 \param value value to push
 \throw std::bad_alloc memory allocation error

 Pushes value to the end of vector.
 Strong exception safety.
*/
void append(Vector &vector, const int value);

void print(std::ostream &os, const Vector &vector);

/** \brief erases struct Vector

 Erases struct Vector.
 Works properly if vector == nullptr.
 No-throw guarantee.
*/
void erase(Vector *vector);

/// overloading of str_to_v for const char *
Vector *str_to_v(const char *line, const std::string &arr_name,
                 const std::string &elem_name);

/** \brief parses std::string line to struct Vector
 \param line line to parse
 \param arr_name html tag of arr (without <>)
 \param elem_name html tag of elem (without <>)
 \return ptr to struct Vector
 \throw std::bad_alloc memory allocation error
 \throw std::bad_alloc memory allocation error

 Parses xml line to struct Vector.
*/
Vector *str_to_v(const std::string &line, const std::string &arr_name,
                 const std::string &elem_name);

/// overloading of str_to_v for char array
Vector *str_to_v(const char *line, const size_t len, const std::string &arr_name,
                 const std::string &elem_name);

/** \brief forms xml line from Vector
 \param vector vector to form from
 \param arr_name html_tag of vector (without <>)
 \param elem_name html_tag of element (without <>)
 \return xml_line
*/
std::string v_to_str(const Vector &vector, const std::string &arr_name,
                     const std::string &elem_name);

} // namespace vector

#endif
