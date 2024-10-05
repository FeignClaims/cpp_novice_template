/*
std_lib_facilities.h
*/

/*
simple "Programming: Principles and Practice using C++ (second edition)" course header to
be used for the first few weeks.
It provides the most common standard headers (in the global namespace)
and minimal exception/error support.

Students: please don't try to understand the details of headers just yet.
All will be explained. This header is primarily used so that you don't have
to understand every concept all at once.

By Chapter 10, you don't need this file and after Chapter 21, you'll understand it

Revised April 25, 2010: simple_error() added

Revised November 25 2013: remove support for pre-C++11 compilers, use C++11: <chrono>
Revised November 28 2013: add a few container algorithms
Revised June 8 2014: added #ifndef to workaround Microsoft C++11 weakness
Revised Febrary 2 2015: randint() can now be seeded (see exercise 5.13).
Revised August 3, 2020: a cleanup removing support for ancient compilers
*/

#ifndef H112
#define H112 080315L

#include <algorithm>      // IWYU pragma: export
#include <array>          // IWYU pragma: export
#include <cmath>          // IWYU pragma: export
#include <cstdint>        // IWYU pragma: export
#include <cstdlib>        // IWYU pragma: export
#include <forward_list>   // IWYU pragma: export
#include <fstream>        // IWYU pragma: export
#include <iomanip>        // IWYU pragma: export
#include <ios>            // IWYU prgama: export
#include <iostream>       // IWYU pragma: export
#include <limits>         // IWYU pragma: export
#include <list>           // IWYU pragma: export
#include <memory>         // IWYU pragma: export
#include <random>         // IWYU pragma: export
#include <regex>          // IWYU pragma: export
#include <sstream>        // IWYU pragma: export
#include <stdexcept>      // IWYU pragma: export
#include <string>         // IWYU pragma: export
#include <type_traits>    // IWYU pragma: export
#include <unordered_map>  // IWYU pragma: export
#include <vector>         // IWYU pragma: export

//------------------------------------------------------------------------------

using Unicode = std::int64_t;

//------------------------------------------------------------------------------

using namespace std;

template <typename T>
string to_string(T const& t) {
  ostringstream ostream;
  ostream << t;
  return ostream.str();
}

struct Range_error : out_of_range {  // enhanced vector range error reporting
  int index;
  Range_error(int i) : out_of_range("Range error: " + to_string(i)), index(i) {}
};

/*
  NOTE from the author of https://github.com/FeignClaims/cpp_novice_template:

  Vector and String are removed because this C++ project template enables range checking with sanitizers by default.

  You could view the original code through https://www.stroustrup.com/Programming/std_lib_facilities.h.
*/
template <typename Value, typename Allocator = std::allocator<Value>>
using Vector = std::vector<Value>;

using String = std::string;

struct Exit : runtime_error {
  Exit() : runtime_error("Exit") {}
};

// error() simply disguises throws:
[[noreturn]] inline void error(string const& message) {
  throw runtime_error(message);
}

[[noreturn]] inline void error(string const& message_1, string const& message_2) {
  error(message_1 + message_2);
}

[[noreturn]] inline void error(string const& message, int i) {
  ostringstream ostream;
  ostream << message << ": " << i;
  error(ostream.str());
}

template <class T>
char* as_bytes(T& i)  // needed for binary I/O
{
  void* addr = &i;                  // get the address of the first byte of memory used to store the object
  return static_cast<char*>(addr);  // treat that memory as bytes
}

inline void keep_window_open() {
  cin.clear();
  cout << "Please enter a character to exit\n";
  char ch{};
  cin >> ch;
}

inline void keep_window_open(string const& message) {
  if (message == "") {
    return;
  }
  cin.clear();
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  for (;;) {
    cout << "Please enter " << message << " to exit\n";
    string input;
    while (cin >> input && input != message) {
      cout << "Please enter " << message << " to exit\n";
    }
    return;
  }
}

// error function to be used (only) until error() is introduced in Chapter 5:
[[noreturn]] inline void simple_error(string const& message)  // write ``error: s and exit program
{
  cerr << "error: " << message << '\n';
  keep_window_open();  // for some Windows environments
  exit(1);
}

// run-time checked narrowing cast (type conversion). See ???.
template <typename T, typename U>
T narrow_cast(U const& u) {
  constexpr bool is_different_signedness{std::is_signed<T>::value != std::is_signed<U>::value};

  T const t{static_cast<T>(u)};

  if (static_cast<U>(t) != u || (is_different_signedness && ((t < T{}) != (u < U{})))) {
    error(string("info loss"));
  }
  return t;
}

// random number generators. See 24.7.

inline default_random_engine& get_rand() {
  static default_random_engine generator;  // note: not thread_local
  return generator;
}

inline void seed_randint(int seed) {
  get_rand().seed(static_cast<unsigned int>(seed));
}

inline int randint(int min, int max) {
  return uniform_int_distribution<>{min, max}(get_rand());
}

inline int randint(int max) {
  return randint(0, max);
}

//inline double sqrt(int x) { return sqrt(double(x)); }	// to match C++0x

// container algorithms. See 21.9.   // C++ has better versions of this:

template <typename Container>
using Value_type = typename Container::value_type;

template <typename Container>
using Iterator = typename Container::iterator;

template <typename Container>
// requires Container<Container>()
void sort(Container& container) {
  std::sort(container.begin(), container.end());
}

template <typename Container, typename Pred>
// requires Container<Container>() && Binary_Predicate<Value_type<Container>>()
void sort(Container& container, Pred pred) {
  std::sort(container.begin(), container.end(), pred);
}

template <typename Container, typename Value>
// requires Container<Container>() && Equality_comparable<Container,Val>()
Iterator<Container> find(Container& container, Value value) {
  return std::find(container.begin(), container.end(), value);
}

template <typename Container, typename Pred>
// requires Container<Container>() && Predicate<Pred,Value_type<Container>>()
Iterator<Container> find_if(Container& container, Pred pred) {
  return std::find_if(container.begin(), container.end(), pred);
}
// NOLINTEND

#endif  //H112