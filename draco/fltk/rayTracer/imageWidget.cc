#include "imageWidget.h"

#include <FL/fl_draw.H>

void ImageBox::draw() {
  // Ensure that the full window is redrawn 
    fl_push_no_clip();

    // Redraw the whole image 
    fl_draw_image(data, x(), y(), w(), h(), 3, 0);

    fl_pop_clip();
}
