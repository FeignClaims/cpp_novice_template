#include "Graph.h"          // get access to our graphics library facilities
#include "Simple_window.h"  // get access to our window library

int main() {
  Graph_lib::Point tl(100, 100);  // to become top left  corner of window

  Graph_lib::Simple_window win(tl, 600, 400, "Canvas");  // make a simple window

  Graph_lib::Polygon poly;  // make a shape (a polygon)

  poly.add(Graph_lib::Point(300, 200));  // add a point
  poly.add(Graph_lib::Point(350, 100));  // add another point
  poly.add(Graph_lib::Point(400, 200));  // add a third point

  poly.set_color(Graph_lib::Color::red);  // adjust properties of poly

  win.attach(poly);  // connect poly to the window

  win.wait_for_button();  // give control to the display engine
}