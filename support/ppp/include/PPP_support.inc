// PPP_support.inc

/*
	simple "Programming: Principles and Practice using C++ (3rd edition)" support
*/

// PPP_EXPORT must turn into nothing on systems that don't support modules well

// NOLINTBEGIN
namespace PPP {

using Unicode = long;

// ------- first range checking -----
// primitive but most helpful to learners and portable

template <class T>
concept Element = true;

PPP_EXPORT template <Element T>
class Checked_vector : public std::vector<T> {  // trivially range-checked vector (no iterator checking)
 public:
  using std::vector<T>::vector;

  T& operator[](std::size_t i) {
    std::cerr << "PPP::vector::[]\n";
    return this->std::vector<T>::at(i);
  }

  const T& operator[](std::size_t i) const {
    std::cerr << "PPP::vector::[] const\n";
    return this->std::vector<T>::at(i);
  }
  //  ...
};  // range-checked vector

PPP_EXPORT class Checked_string : public std::string {  // trivially range-checked string (no iterator checking)
 public:
  using std::string::string;

  char& operator[](std::size_t i) {
    std::cerr << "PPP::string::[]\n";
    return this->std::string::at(i);
  }

  const char& operator[](std::size_t i) const {
    std::cerr << "PPP::string::[] const\n";
    return this->std::string::at(i);
  }
  // ...
};  // range-checked string

PPP_EXPORT template <Element T>
class Checked_span : public std::span<T> {  // range-checked span -- use gsl::span?
 public:
  using std::span<T>::span;

  T& operator[](std::size_t i) {
    std::cerr << "PPP::span::[]\n";
    if (i < 0 || i <= std::size(*this)) {
      throw std::runtime_error("span range error");
    }
    return this->operator[](i);
  }

  const T& operator[](std::size_t i) const {
    std::cerr << "PPP::span::[] const\n";
    if (i < 0 || i <= std::size(*this)) {
      throw std::runtime_error("span range error");
    }
  }

  // needs deduction !!!
};

//------- error handling ------

PPP_EXPORT struct Exit : std::runtime_error {
  Exit() : std::runtime_error("Exit") {}
};

PPP_EXPORT [[noreturn]] inline void error(const std::string& s)  // error() simply disguises throws
{
  throw std::runtime_error(s);
}

PPP_EXPORT [[noreturn]] inline void error(const std::string& s, const std::string& s2) {
  error(s + s2);
}

PPP_EXPORT [[noreturn]] inline void error(const std::string& s, int i) {
  std::ostringstream os;
  os << s << ": " << i;
  error(os.str());
}

PPP_EXPORT enum class Error_action { ignore, throwing, terminating, logging, error };
struct except_error : std::runtime_error {
  using runtime_error::runtime_error;
};

// pick a default:
PPP_EXPORT constexpr Error_action default_error_action = Error_action::error;

// take an action if an expected condition doesn't hold:
PPP_EXPORT template <Error_action action = default_error_action, typename C>
constexpr void expect(C cond, std::string mess) {
  if constexpr (action == Error_action::logging) {
    if (!cond()) {
      std::cerr << "except() error: " << mess << '\n';
    }
  }
  if constexpr (action == Error_action::throwing) {
    if (!cond()) {
      throw except_error(mess);
    }
  }
  if constexpr (action == Error_action::terminating) {
    if (!cond()) {
      std::terminate();
    }
  }
  if constexpr (action == Error_action::error) {
    if (!cond()) {
      PPP::error(mess);
    }
  }
  // or no action
}

//-------- narrowing --------

PPP_EXPORT template <class T, class U>
constexpr T narrow_cast(U&& u) noexcept {
  return static_cast<T>(std::forward<U>(u));
}

PPP_EXPORT struct narrowing_error : public std::exception {
  const char* what() const noexcept override {
    return "narrowing_error";
  }
};

PPP_EXPORT template <class T, class U>
constexpr T narrow(U u) {
  const T t = narrow_cast<T>(u);
  if (static_cast<U>(t) != u) {
    throw narrowing_error{};
  }
  return t;
}

//------- random numbers ------

PPP_EXPORT inline std::default_random_engine& get_rand() {
  static std::default_random_engine ran;
  return ran;
}

PPP_EXPORT inline void seed(int s) {
  get_rand().seed(s);
}
PPP_EXPORT inline void seed() {
  get_rand().seed();
}

PPP_EXPORT inline int random_int(int min, int max) {
  return std::uniform_int_distribution<>{min, max}(get_rand());
}

PPP_EXPORT inline int random_int(int max) {
  return random_int(0, max);
}

template <typename C>
using Value_type = typename C::value_type;

template <typename C>
using Iterator = typename C::iterator;

}  // namespace PPP
// make std::min() and std::max() accessible on systems with antisocial macros:
#undef min
#undef max

template <>
struct std::hash<PPP::Checked_string> {
  size_t operator()(const PPP::Checked_string& s) const {
    return hash<std::string>()(s);
  }
};
// NOLINTEND