#ifndef FLTK_GUARD
#define FLTK_GUARD

// NOLINTBEGIN
#ifndef CPP_NOVICE_FLTK_FOUND
#  error You haven't install fltk. Please install fltk and reconfigure the project according to README.pdf. (你没有安装 fltk, 请阅读 请读我.pdf 安装 fltk 并重新配置项目.)
#endif

#include "FL/Enumerations.H"   // IWYU pragma: export
#include "FL/Fl.H"             // IWYU pragma: export
#include "FL/Fl_Button.H"      // IWYU pragma: export
#include "FL/Fl_Input.H"       // IWYU pragma: export
#include "FL/Fl_Output.H"      // IWYU pragma: export
#include "FL/Fl_Window.H"      // IWYU pragma: export
#include "FL/fl_draw.H"        // IWYU pragma: export
#include "Fl/Fl_GIF_Image.H"   // IWYU pragma: export
#include "Fl/Fl_JPEG_Image.H"  // IWYU pragma: export

#include <cstdlib>  // for exit(0)
// NOLINTEND

#endif