#ifndef WINDOW_GUARD
#define WINDOW_GUARD 1

#include "Graph.h"
#include "Point.h"

#include "PPPheaders.h"

namespace Graph_lib {

class Shape;  // "forward declare" Shape
struct Color;
struct Line_style;
class Font;
struct Image;

class Widget;

class PainterPrivate;
class Painter {
 public:
  Painter(std::unique_ptr<PainterPrivate>&& pp);
  ~Painter();
  Painter(Painter const&)            = delete;
  Painter& operator=(Painter const&) = delete;

  void draw_rectangle(Point const& p1, int w, int h);
  void draw_line(Point const& p1, Point const& p2);
  void draw_polygon(Shape const& s);
  Point draw_text(Point const& p1, std::string const& text);
  Point draw_centered_text(Point const& p1, std::string const& text);
  void draw_text_line(Point const& p1, Vector_ref<Text const> const& texts);
  void draw_text_column(Point const& p1, Vector_ref<Text const> const& texts);
  void draw_ellipse(Point const& p1, int r, int r2);
  void draw_arc(Point const& p1, int r, int r2, int start_angle, int end_angle);
  void draw_pie(Point const& p1, int r, int r2, int start_angle, int end_angle);
  void draw_image(Point const& p1, Image const& img);
  void draw_image(Point const& p1, Point const& p2, int w, int h, Image const& img);
  void set_line_style(Line_style style);  // set_color must be called after set_line_style
  void set_font_size(int s);
  void set_font(Font f);
  void set_color(Color color);  // set_color must be called after set_line_style
  void set_fill_color(Color color);

 private:
  void save();
  void restore();
  void setup_from_text(Text const& text);
  friend class Shape;

 private:
  std::unique_ptr<PainterPrivate> impl;
};

class ApplicationPrivate;
class Application {
 public:
  Application();
  ~Application();
  void gui_main();
  void quit();

 private:
  std::unique_ptr<ApplicationPrivate> impl;
};

struct Button;
class WindowPrivate;
class Window {
 public:
  Window(int w, int h, string const& title);            // let the system pick the location
  Window(Point xy, int w, int h, string const& title);  // top left corner in xy
  virtual ~Window();

  int x_max() const {
    return w;
  }
  int y_max() const {
    return h;
  }

  void resize(int ww, int hh);

  void set_label(string const& s);

  void attach(Shape& s);
  void attach(Widget& w);

  void detach(Shape& s);   // remove s from shapes
  void detach(Widget& w);  // remove w from window (deactivate callbacks)

  void put_on_top(Shape& s);  // put p on top of other shapes

  WindowPrivate& get_impl() const;
  void draw();
  void close();
  void wait_for_button(Button* button);
  void end_button_wait();
  void timer_wait(int milliseconds);
  void timer_wait(int milliseconds, std::function<void()> cb);

 private:
  Point p;
  int w, h;  // window size
  unique_ptr<WindowPrivate> impl;
  void init();
};

int gui_main();  // invoke GUI library's main event loop

inline int x_max() {
  return 1024;
}  // width of screen in pixels
inline int y_max() {
  return 768;
}  // height of screen in pixels

}  // namespace Graph_lib
#endif
