import sys

import cairo
import clutter
from clutter import cluttercairo

def main ():
    # CREATE STAGE
    stage = clutter.stage_get_default()
    stage.set_color(clutter.Color(0xff, 0xcc, 0xcc, 0xff))
    stage.set_size(400,300)

    # CREATE CAIRO TEXTURE
    cairo_tex = cluttercairo.CairoTexture(200,200)
    cairo_tex.set_position((stage.get_width() - 200) / 2,
                           (stage.get_height() - 200) / 2)

    # DO CAIRO DRAWING
    context = cairo_tex.cairo_create()
    context.scale(200, 200)

    context.set_line_width(0.1)
    context.set_source_rgba(0, 0, 0, 1)
    context.translate(0.5, 0.5)
    context.arc(0, 0, 0.4, 0, 3.14 * 2)
    context.stroke()
    del(context) # we need to destroy the context so that the
                 # texture gets properly updated with the result

    cairo_tex.rotate_y(45.0, cairo_tex.get_width() / 2,
                             cairo_tex.get_height() / 2)

    # SHOW CAIRO TEXTURE
    stage.add(cairo_tex)
    cairo_tex.show()
    stage.show()

    clutter.main()

    return 0

if __name__ == '__main__':
    sys.exit(main())
