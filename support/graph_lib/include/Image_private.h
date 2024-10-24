#ifndef IMAGE_PRIVATE_GUARD
#define IMAGE_PRIVATE_GUARD 1

#include <QColor>
#include <QImage>

namespace Graph_lib {

class ImagePrivate {
 public:
  QImage image;
  void load(std::string const& s);
  void scale(int w, int h, bool keep_aspect_ratio = true);
};

QColor mapPaletteColor(int rawColor);

}  // namespace Graph_lib
#endif