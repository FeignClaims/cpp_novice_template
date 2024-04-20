// PPPheaders.h

// NOLINTBEGIN
#include <algorithm>      // IWYU pragma: export
#include <cstdint>        // IWYU pragma: export
#include <iostream>       // IWYU pragma: export
#include <list>           // IWYU pragma: export
#include <map>            // IWYU pragma: export
#include <memory>         // IWYU pragma: export
#include <random>         // IWYU pragma: export
#include <set>            // IWYU pragma: export
#include <span>           // IWYU pragma: export
#include <sstream>        // IWYU pragma: export
#include <stdexcept>      // IWYU pragma: export
#include <string>         // IWYU pragma: export
#include <unordered_map>  // IWYU pragma: export
#include <vector>         // IWYU pragma: export

#define PPP_EXPORT
#include "PPP_support.inc"

using namespace std;
using namespace PPP;

// disgusting macro hack to get a range checking:
#define vector Checked_vector
#define string Checked_string
#define span   Checked_span
// NOLINTEND