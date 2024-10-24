
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Simple_window.h"

#include "GUI_private.h"

#include <QEventLoop>
#include <QTimer>
//------------------------------------------------------------------------------

Simple_window::Simple_window(Point xy, int w, int h, string const& title)
    : Window(xy, w, h, title), next_button(Point{w - 70, 0}, 70, 20, "Next", [] {}) {
  attach(next_button);
}

Simple_window::~Simple_window() {}

//------------------------------------------------------------------------------

void Simple_window::wait_for_button()
// modified event loop:
// handle all events (as per default), quit when button_pushed becomes true
// this allows graphics without control inversion
{
  get_impl().wait_for_button(&next_button);
}

//------------------------------------------------------------------------------
