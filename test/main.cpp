//----------------------------------------------------------------------------------------------------------------------
// The following code is deliberately unformatted.
// Please search online to learn how to apply formatting in the software you are using
//   (some software can even be set to "auto-format on save").
// However, please note that some outdated software may not support formatting.
//
// 以下代码故意没有格式化.
// 请查询你所使用的软件如何进行格式化. (有些软件甚至可以设置 "保存时自动格式化").
// 但请注意, 有的过旧软件并不支持格式化.
//----------------------------------------------------------------------------------------------------------------------
#include "PPPheaders.h"

int
 x;

int
 main() 
      {int x{};
  std::cout
<< std::boolalpha << (std::compare_strong_order_fallback(1, 2) < 0) << '\n';
}