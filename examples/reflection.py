import sys
import gobject
import clutter

from clutter import cogl

class TextureReflection (clutter.CloneTexture):
    """
    TextureReflection (clutter.CloneTexture)

    An actor that paints a reflection of a texture. The
    height of the reflection can be set in pixels. If set
    to a negative value, the same size of the parent texture
    will be used.

    The size of the TextureReflection actor is by default
    the same size of the parent texture.
    """
    __gtype_name__ = 'TextureReflection'

    def __init__ (self, parent):
        clutter.CloneTexture.__init__(self, parent)
        self._reflection_height = -1

    def set_reflection_height (self, height):
        self._reflection_height = height
        self.queue_redraw()

    def get_reflection_height (self):
        return self._reflection_height

    def do_paint (self):
        parent = self.get_parent_texture()
        if (parent is None):
            return

        # get the cogl handle for the parent texture
        cogl_tex = parent.get_cogl_texture()
        if (cogl_tex is None):
            return

        (width, height) = self.get_size()

        # clamp the reflection height if needed
        r_height = self._reflection_height
        if (r_height < 0 or r_height > height):
            r_height = height

        rty = float(r_height / height)

        opacity = self.get_paint_opacity()

        # the vertices are a 6-tuple composed of:
        #  x, y, z: coordinates inside Clutter modelview
        #  tx, ty: texture coordinates
        #  color: a clutter.Color for the vertex
        #
        # to paint the reflection of the parent texture we paint
        # the texture using four vertices in clockwise order, with
        # the upper left and the upper right at full opacity and
        # the lower right and lower left and 0 opacity; OpenGL will
        # do the gradient for us
        vertices = ( \
            (    0,        0, 0, 0.0, rty,   (255, 255, 255, opacity)), \
            (width,        0, 0, 1.0, rty,   (255, 255, 255, opacity)), \
            (width, r_height, 0, 1.0,   0.0, (255, 255, 255,       0)), \
            (    0, r_height, 0, 0.0,   0.0, (255, 255, 255,       0)), \
        )

        cogl.push_matrix()

        cogl_tex.texture_polygon(vertices=vertices, use_color=True)

        cogl.pop_matrix()

def main (args):
    stage = clutter.Stage()
    stage.set_color(clutter.Color(0, 0, 0, 255))
    stage.set_title('TextureReflection')
    stage.connect('button-press-event', clutter.main_quit)
    stage.connect('destroy', clutter.main_quit)

    group = clutter.Group()
    stage.add(group)

    try:
        tex = clutter.Texture(args[0])
    except Exception:
        print "Unable to load the texture file"
        return 1

    reflect = TextureReflection(tex)
    reflect.set_opacity(100)

    x_pos = float((stage.get_width() - tex.get_width()) / 2)

    group.add(tex, reflect)
    group.set_positionu(x_pos, 20.0)
    reflect.set_positionu(0.0, (tex.get_heightu() + 20))

    timeline = clutter.Timeline(duration=3000)
    timeline.set_loop(True)
    alpha = clutter.Alpha(timeline, clutter.ramp_inc_func)
    behaviour = clutter.BehaviourRotate(clutter.Y_AXIS, 0.0, 360.0, alpha, clutter.ROTATE_CW)
    behaviour.set_center(group.get_width()/2, 0, 0)
    behaviour.apply(group)

    stage.show()

    timeline.start()

    clutter.main()

    return 0

if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
