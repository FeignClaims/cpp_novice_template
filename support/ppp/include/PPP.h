// PPP.h

#ifndef PPP_SUPPORT_MODULE
#  error The configuration dosen't support `#include "PPP.h"`. Please use `#include "PPPheaders.h"` instead or update the configuration according to README.pdf. \
(当前配置不支持 `#include "PPP.h"`, 请使用 `#include "PPPheaders.h"` 或阅读 请读我.pdf 更新配置.)
#endif

// NOLINTBEGIN
import PPP;
using namespace PPP;
using namespace std;

// disgusting macro hack to guarantee range checking for []:
#define vector Checked_vector
#define string Checked_string
#define span   Checked_span
// NOLINTEND