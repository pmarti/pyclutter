import clutter

stage = clutter.stage_get_default()
stage.set_size(800, 600)
stage.set_color(0xcc, 0xcc, 0xcc, 0xff)
stage.connect('key-press-event', clutter.main_quit)

rect = clutter.Rectangle()
rect.set_position(0, 0)
rect.set_size(100, 100)
rect.set_color(0x33, 0x22, 0x22, 0xff)
rect.show()

knots = ( \
        (   0,   0 ),   \
        ( 300,   0 ),   \
        ( 300, 300 ),   \
        (   0, 300 ),   \
        (   0,   0 ),   \
)

timeline = clutter.Timeline(100, 26)
timeline.set_loop(True)
alpha = clutter.Alpha(timeline, clutter.sine_func)
p_behaviour = clutter.BehaviourPath(alpha, knots)
p_behaviour.apply(rect)

stage.add(rect)
stage.show()

timeline.start()

clutter.main()
