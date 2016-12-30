/* The MIT License (MIT)
 *
 * Copyright (c) 2014-2016 David Medina and Tim Warburton
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 */

#ifndef OCCA_TOOLS_STRING_HEADER
#define OCCA_TOOLS_STRING_HEADER

#include <iostream>
#include <iomanip>
#include <sstream>

#include "occa/defines.hpp"
#include "occa/types.hpp"

namespace occa {
  std::string strip(const std::string &str);

  std::string escape(const std::string &str, const char c, const char excapeChar = '\\');
  std::string unescape(const std::string &str, const char c, const char excapeChar = '\\');

  strVector_t split(const std::string &s, const char delimeter, const char escapeChar = 0);

  template <class TM>
  inline std::string toString(const TM &t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
  }

  template <class TM>
  inline std::string toString(const std::vector<TM> &v) {
    const int size = (int) v.size();
    std::stringstream ss;
    ss << '[';
    for (int i = 0; i < size; ++i) {
      const std::string istr = occa::toString(v[i]);
      ss << escape(istr, ',');
      if (i < (size - 1)) {
        ss << ',';
      }
    }
    ss << ']';
    return ss.str();
  }

  template <>
  inline std::string toString<std::string>(const std::string &t) {
    return t;
  }

  template <>
  inline std::string toString<float>(const float &t) {
    std::stringstream ss;
    ss << std::scientific << std::setprecision(8) << t << 'f';
    return ss.str();
  }

  template <>
  inline std::string toString<double>(const double &t) {
    std::stringstream ss;
    ss << std::scientific << std::setprecision(16) << t;
    return ss.str();
  }

  template <class TM>
  inline TM fromString(const std::string &s) {
    std::stringstream ss;
    TM t;
    ss << s;
    ss >> t;
    return t;
  }

  template <class TM>
  inline std::vector<TM> listFromString(const std::string &s) {
    std::string str = strip(s);
    const int chars = (int) str.size();
    if (chars && str[chars - 1] == ']') {
      str = str.substr(0, chars - 1);
    }
    if (chars && str[0] == '[') {
      str = str.substr(1);
    }

    strVector_t parts = split(str, ',', '\\');
    const int partCount = (int) parts.size();

    std::vector<TM> ret;
    ret.reserve(partCount);
    for (int i = 0; i < partCount; ++i) {
      ret.push_back(occa::fromString<TM>(unescape(parts[i], '\\')));
    }
    return ret;
  }

  template <>
  inline std::string fromString(const std::string &s) {
    return s;
  }

  inline char uppercase(const char c) {
    if (('a' <= c) && (c <= 'z')) {
      return ((c + 'A') - 'a');
    }
    return c;
  }

  inline char lowercase(const char c) {
    if (('A' <= c) && (c <= 'Z')) {
      return ((c + 'a') - 'A');
    }
    return c;
  }

  std::string uppercase(const char *c, const int chars);
  inline std::string uppercase(const std::string &s) {
    return uppercase(s.c_str(), s.size());
  }

  std::string lowercase(const char *c, const int chars);
  inline std::string lowercase(const std::string &s) {
    return uppercase(s.c_str(), s.size());
  }

  udim_t atoi(const char *c);
  udim_t atoiBase2(const char *c);
  udim_t atoi(const std::string &str);

  double atof(const char *c);
  double atof(const std::string &str);

  double atod(const char *c);
  double atod(const std::string &str);

  std::string stringifyBytes(udim_t bytes);
}

#endif
