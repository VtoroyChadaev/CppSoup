#include "../src/input/input.hpp"
#include "../src/vector/vector.hpp"
#include <algorithm> // to use std::all_of
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <ios>
#include <sstream>
#include <string>
#include <vector>

void user_input(const char *input, std::streamsize size,
                vector::Vector &_t_vector_) {
  std::stringbuf inp_buf;
  std::stringbuf out_buf;
  std::istream inp_stream(&inp_buf);
  std::ostream out_stream(&out_buf);

  inp_buf.sputn(input, size);
  vector::input(inp_stream, out_stream, _t_vector_);
}

TEST(get_num, eof_test) { // OTHER get_num functionality tests via vector funcs
  std::stringbuf inp_buf;
  std::istream inp_stream(&inp_buf);
  inp_stream.setstate(std::ios_base::eofbit);

  std::stringbuf out_buf;
  std::ostream out_stream(&out_buf);

  EXPECT_THROW(input::get_num<int>(inp_stream, out_stream), std::runtime_error);
}

TEST(inp_vector, basic_test) {
  vector::Vector *t_vector = vector::create(0);
  auto &_t_vector_ = (*t_vector);

  user_input("1\n2\n3\n4\nend\n", 100, _t_vector_);
  std::vector<int> expected = {1, 2, 3, 4};

  std::size_t i = 0;
  EXPECT_TRUE(
      std::all_of(expected.begin(), expected.end(), [&t_vector, &i](int ex) {
        return ex == t_vector->elems[i++];
      }));

  vector::erase(t_vector);
}

TEST(inp_vector, empty_test) {
  vector::Vector *t_vector = vector::create(0);
  auto &_t_vector_ = (*t_vector);

  user_input("end\n", 100, _t_vector_);

  EXPECT_TRUE(t_vector->elems == nullptr);
  vector::erase(t_vector);
}

TEST(vector_append, basic_test) {
  vector::Vector *t_vector = vector::create(0);
  auto &_t_vector_ = (*t_vector);

  user_input("1\n2\n3\n4\n\nend\n", 100, _t_vector_);

  vector::append(_t_vector_, 5);
  std::vector<int> expected = {1, 2, 3, 4, 5};

  size_t i = 0;
  EXPECT_TRUE(
      std::all_of(expected.begin(), expected.end(), [&t_vector, &i](int ex) {
        return ex == t_vector->elems[i++];
      }));
  EXPECT_TRUE(_t_vector_.len == 5);
  vector::erase(t_vector);
}

TEST(vector_append, empty_test) {
  vector::Vector *t_vector = vector::create(0);
  auto &_t_vector_ = (*t_vector);

  vector::append(_t_vector_, 5);
  std::vector<int> expected = {5};

  size_t i = 0;
  EXPECT_TRUE(
      std::all_of(expected.begin(), expected.end(), [&t_vector, &i](int ex) {
        return ex == t_vector->elems[i++];
      }));
  vector::erase(t_vector);
}

TEST(vec_erase, empty_test) { EXPECT_NO_THROW(vector::erase(nullptr)); }

TEST(out_vector, basic_test) {
  vector::Vector *t_vector = vector::create(0);
  auto &_t_vector_ = (*t_vector);

  user_input("1\n2\n3\n4\nend\n", 100, _t_vector_);

  std::stringbuf out_buf;
  std::ostream out_stream(&out_buf);

  vector::print(out_stream, _t_vector_);
  std::string expected = "[1, 2, 3, 4]\n";
  std::string returned = out_buf.str();
  EXPECT_TRUE(std::equal(returned.begin(), returned.end(), expected.begin()));
  vector::erase(t_vector);
}

TEST(out_vector, empty_test) {
  vector::Vector *t_vector = vector::create(0);
  auto &_t_vector_ = (*t_vector);
  std::stringbuf out_buf;
  std::ostream out_stream(&out_buf);

  EXPECT_NO_THROW(vector::print(out_stream, _t_vector_));
}

TEST(s_to_v, cpp_str) {
  std::string xml_line(
      "<array><value>1</value><value>2</value><value>3</value></array>");

  vector::Vector *vector = vector::str_to_v(xml_line, "array", "value");
  std::vector<int> expected = {1, 2, 3};
  std::size_t i = 0;
  EXPECT_TRUE(
      std::all_of(expected.begin(), expected.end(),
                  [&vector, &i](int ex) { return ex == vector->elems[i++]; }));

  vector::erase(vector);
}

TEST(s_to_v, c_str) {
  const char *xml_line =
      "<array><value>1</value><value>2</value><value>3</value></array>";

  vector::Vector *vector = vector::str_to_v(xml_line, "array", "value");
  std::vector<int> expected = {1, 2, 3};
  std::size_t i = 0;
  EXPECT_TRUE(
      std::all_of(expected.begin(), expected.end(),
                  [&vector, &i](int ex) { return ex == vector->elems[i++]; }));

  vector::erase(vector);
}

TEST(s_to_v, char_arr) {
  std::string line(
      "<array><value>1</value><value>2</value><value>3</value></array>");
  const char *xml_line = line.c_str();

  vector::Vector *vector =
      vector::str_to_v(xml_line, line.size(), "array", "value");
  std::vector<int> expected = {1, 2, 3};
  std::size_t i = 0;
  EXPECT_TRUE(
      std::all_of(expected.begin(), expected.end(),
                  [&vector, &i](int ex) { return ex == vector->elems[i++]; }));

  vector::erase(vector);
}

TEST(s_to_v, empty_line) {
  std::string line = "\n";
  vector::Vector *vector = vector::str_to_v(line, "arr", "val");

  EXPECT_TRUE(vector == nullptr);
}

TEST(s_to_v, broken_line) {
  std::string line = "jkfldasjfkl<><>><<<</>";
  vector::Vector *vector = vector::str_to_v(line, "", "");

  EXPECT_TRUE(vector == nullptr);
}

TEST(v_to_s, basic_test) {
  vector::Vector *t_vector = vector::create(0);
  auto &_t_vector_ = (*t_vector);

  user_input("1\n2\n3\n4\nend\n", 100, _t_vector_);

  std::string expected_line =
      "<arr><val>1</val><val>2</val><val>3</val><val>4</val></arr>";
  std::string returned_line = vector::v_to_str(_t_vector_, "arr", "val");

  EXPECT_TRUE(std::equal(expected_line.begin(), expected_line.end(),
                         returned_line.begin()));
  vector::erase(t_vector);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
