import sys
from math import pi

import cairo
import clutter
from clutter import cluttercairo

def on_button_press_event (stage, event):
    clutter.main_quit()

def main ():
    stage = clutter.stage_get_default()
    stage.set_color(clutter.Color(0xff, 0xcc, 0xcc, 0xff))
    stage.set_size(400,300)
    stage.connect('button-press-event', on_button_press_event)

    cairo_tex = cluttercairo.CairoTexture(200,200)
    cairo_tex.set_position((stage.get_width() - 200) / 2,
                           (stage.get_height() - 200) / 2)

    # we obtain a cairo context from the cluttercairo.Texture
    # and then we can use it with the cairo primitives to draw
    # on it.
    context = cairo_tex.cairo_create()

    # we scale the context to the size of the surface
    context.scale(200, 200)
    context.set_line_width(0.1)
    context.set_source_rgba(0, 0, 0, 1)
    context.translate(0.5, 0.5)
    context.arc(0, 0, 0.4, 0, pi * 2)
    context.stroke()

    del(context) # we need to destroy the context so that the
                 # texture gets properly updated with the result
                 # of our operations

    # cluttercairo.Texture is a clutter.Actor, so we can
    # manipulate it as any other actor
    cairo_tex.rotate_y(45.0,
                       cairo_tex.get_width() / 2,
                       cairo_tex.get_height() / 2)

    stage.add(cairo_tex)
    cairo_tex.show()
    stage.show()

    clutter.main()

    return 0

if __name__ == '__main__':
    sys.exit(main())
