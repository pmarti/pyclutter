import sys
import clutter
import gtk
import math

class SuperOh (clutter.Group) :
    def __init__ (self, nhands=6):
        clutter.Group.__init__(self)

        self.n_hands = nhands
        self.timeline = clutter.Timeline(5000)

        self.timeline.set_loop(True)
        self.timeline.connect('new-frame', self.on_new_frame)

        self.stage = clutter.Stage(default=True)
        self.stage.set_size(1024, 768)
        self.stage.connect('button-press-event', self.on_button_press)

        self.create_hands()

    def create_hands (self):
        try:
            redhand = clutter.Texture(filename="redhand.png")
        except Exception:
            print "Unable to load redhand.png"
            sys.exit(1)

        (w, h) = redhand.get_size()

        for i in range(self.n_hands):
            hand = clutter.Clone(redhand);
            radius = self.get_radius()
            x = self.stage.get_width() / 2 + radius * math.cos(i * math.pi / (self.n_hands / 2)) - w / 2

            y = self.stage.get_height() / 2 + radius * math.sin (i * math.pi / (self.n_hands / 2)) - h / 2

            hand.set_position (int(x), int(y))
      
            hand.show()
            self.add(hand);
        self.add(redhand)
        redhand.hide()

    def spin (self):
        self.timeline.start()

    def get_radius (self):
        return (self.stage.get_width () + self.stage.get_height ()) / self.n_hands

    def on_new_frame (self, tl, msecs):
        progress = tl.get_progress()
        self.set_rotation (clutter.Z_AXIS,
                           progress * 360,
                           self.stage.get_width() / 2,
                           self.stage.get_height () / 2,
                           0)
      
        angle = progress * -360

        for i in range(self.n_hands):
            hand = self.get_nth_child(i)
            hand.set_rotation(clutter.Z_AXIS,
                              angle,
                              hand.get_width() / 2,
                              hand.get_height() / 2,
                              0)

    def on_button_press (self, stage, event):
        if (event.button != 1):
            return

        hand = stage.get_actor_at_pos(clutter.PICK_ALL, event.x, event.y)
        if (hand):
            hand.hide()

def main (args):
    stage = clutter.Stage(default=True)

    stage.set_color(clutter.Color(0xcc, 0xcc, 0xcc, 0xff))
    stage.connect('key-press-event', clutter.main_quit)

    hands = SuperOh(8)
    hands.spin()
    stage.add(hands)

    stage.show_all()
    clutter.main()

    return 0
    
if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
