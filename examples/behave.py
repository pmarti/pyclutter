import sys
import clutter

class BehaviourRotate (clutter.Behaviour):
        __gtype_name__ = 'BehaviourRotate'
        def __init__ (self, alpha=None):
                clutter.Behaviour.__init__(self)
                self.set_alpha(alpha)
                self.angle_start = 0.0
                self.angle_end = 359.0

        def do_alpha_notify (self, alpha_value):
                angle = alpha_value \
                      * (self.angle_end - self.angle_start) \
                      / clutter.MAX_ALPHA

                for actor in self.get_actors():
                        actor.rotate_z(angle,
                                       actor.get_x() - 100,
                                       actor.get_y() - 100)


def main (args):
    stage = clutter.stage_get_default()
    stage.set_size(800, 600)
    stage.set_color(clutter.Color(0xcc, 0xcc, 0xcc, 0xff))
    stage.connect('key-press-event', clutter.main_quit)

    rect = clutter.Rectangle()
    rect.set_position(0, 0)
    rect.set_size(150, 150)
    rect.set_color(clutter.Color(0x33, 0x22, 0x22, 0xff))
    rect.set_border_color(clutter.color_parse('white'))
    rect.set_border_width(15)
    rect.show()

    knots = ( \
            (   0,   0 ),   \
            ( 300,   0 ),   \
            ( 300, 300 ),   \
            (   0, 300 ),   \
    )

    timeline = clutter.Timeline(100, 26)
    timeline.set_loop(True)
    alpha = clutter.Alpha(timeline, clutter.sine_func)

    o_behaviour = clutter.BehaviourOpacity(alpha, 0x33, 0xff)
    o_behaviour.apply(rect)

    p_behaviour = clutter.BehaviourPath(alpha, knots)
    p_behaviour.append_knots((0, 0))
    p_behaviour.apply(rect)

    r_behaviour = BehaviourRotate(alpha)
    r_behaviour.apply(rect)

    stage.add(rect)
    stage.show()

    timeline.start()

    clutter.main()
    
    return 0

if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
