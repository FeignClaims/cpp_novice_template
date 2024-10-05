#define PPP_EXPORT

// PPP_support-inl.h

/*
	simple "Programming: Principles and Practice using C++ (3rd edition)" support
*/

// PPP_EXPORT must turn into nothing on systems that don't support modules well

// NOLINTBEGIN
namespace PPP {
using Unicode = std::int64_t;

// ------- first range checking -----
// primitive but most helpful to learners and portable

template <typename T>
concept Element = true;

/*
  NOTE from the author of https://github.com/FeignClaims/cpp_novice_template:

  Checked_vector, Checked_string and Checked_span are removed because this C++ project template enables range checking
    with sanitizers by default.

  You could view the original code through https://www.stroustrup.com/PPP_support.h. However, there're bugs in the
    implementation.
*/
template <typename Value, typename Allocator = std::allocator<Value>>
using Checked_vector = std::vector<Value, Allocator>;

using Checked_string = std::string;

template <typename T, std::size_t Extent = std::dynamic_extent>
using Checked_span = std::span<T, Extent>;

//------- error handling ------

PPP_EXPORT struct Exit : std::runtime_error {
  Exit() : std::runtime_error("Exit") {}
};

// error() simply disguises throws
PPP_EXPORT [[noreturn]] inline void error(std::string const& message) {
  throw std::runtime_error(message);
}

PPP_EXPORT [[noreturn]] inline void error(std::string const& message_1, std::string const& message_2) {
  error(message_1 + message_2);
}

PPP_EXPORT [[noreturn]] inline void error(std::string const& message, int i) {
  std::ostringstream ostream;
  ostream << message << ": " << i;
  error(ostream.str());
}

PPP_EXPORT enum class Error_action { ignore, throwing, terminating, logging, error };
struct Expect_error : std::runtime_error {
  using runtime_error::runtime_error;
};

// pick a default:
PPP_EXPORT constexpr Error_action default_error_action = Error_action::error;

// take an action if an expected condition doesn't hold:
PPP_EXPORT template <Error_action Action = default_error_action, typename Condition>
constexpr void expect(Condition condition, std::string const& message) {
  if (!condition()) {
    if constexpr (Action == Error_action::logging) {
      std::cerr << "expect() error: " << message << '\n';
    } else if constexpr (Action == Error_action::throwing) {
      throw Expect_error(message);
    } else if constexpr (Action == Error_action::terminating) {
      std::terminate();
    } else if constexpr (Action == Error_action::error) {
      PPP::error(message);
    } else {
      static_assert(false, "unkown error_action");
    }
  }
}

//-------- narrowing --------

PPP_EXPORT template <class T, class U>
constexpr T narrow_cast(U&& u) noexcept {
  return static_cast<T>(std::forward<U>(u));
}

PPP_EXPORT struct narrowing_error : public std::exception {
  [[nodiscard]] char const* what() const noexcept override {
    return "narrowing_error";
  }
};

PPP_EXPORT template <class T, class U>
constexpr T narrow(U u) {
  T const t = narrow_cast<T>(u);
  if (static_cast<U>(t) != u) {
    throw narrowing_error{};
  }
  return t;
}

//------- random numbers ------

PPP_EXPORT inline std::default_random_engine& get_rand() {
  static std::default_random_engine engine;
  return engine;
}

PPP_EXPORT inline void seed(int seed) {
  get_rand().seed(static_cast<unsigned int>(seed));
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
// NOLINTEND