import sys
import clutter
import gtk
import math

class SuperOh (clutter.Group) :
    def __init__ (self, nhands=6):
        clutter.Group.__init__(self)

        self.n_hands = nhands
        self.timeline = clutter.Timeline(360, 60)

        self.timeline.set_loop(True)
        self.timeline.connect('new-frame', self.on_new_frame)

        self.stage = clutter.stage_get_default()
        self.stage.set_size(1024, 768)
        self.stage.connect('button-press-event', self.on_button_press)

        self.create_hands()

    def create_hands (self):
        try:
            pixbuf = gtk.gdk.pixbuf_new_from_file("redhand.png")
        except Exception:
            print "Unable to find redhand.png"
            sys.exit(1)

        redhand = clutter.Texture(pixbuf)
        (w, h) = redhand.get_size()

        for i in range(self.n_hands):
            hand = clutter.CloneTexture(redhand);
            radius = self.get_radius()
            x = self.stage.get_width() / 2 + radius * math.cos(i * math.pi / (self.n_hands / 2)) - w / 2

            y = self.stage.get_height() / 2 + radius * math.sin (i * math.pi / (self.n_hands / 2)) - h / 2

            hand.set_position (int(x), int(y))
      
            hand.show()
            self.add(hand);

    def spin (self): 
        self.timeline.start()

    def get_radius (self):
        return (self.stage.get_width () + self.stage.get_height ()) / self.n_hands

    def on_new_frame (self, tl, frame_num):
        self.set_rotation (clutter.Z_AXIS,
                           frame_num,
                           self.stage.get_width() / 2,
                           self.stage.get_height () / 2,
                           0)
      
        angle = frame_num * -2

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

        hand = stage.get_actor_at_pos(event.x, event.y)
        if (hand):
            hand.hide()

def main (args):
    stage = clutter.stage_get_default()

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
