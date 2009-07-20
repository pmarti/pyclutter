import sys
import clutter

BUFFER = '''
[
  { "id" : "move-timeline",  "type" : "ClutterTimeline", "duration" : 2500 },
  { "id" : "scale-timeline", "type" : "ClutterTimeline", "duration" : 2000 },
  { "id" : "fade-timeline",  "type" : "ClutterTimeline", "duration" : 1500 },
  {
    "id" : "move-behaviour", "type" : "ClutterBehaviourPath",
    "alpha" : {
      "timeline" : "move-timeline",
      "mode" : "ease-out-sine"
    },
    "path" : "M 100 100 L 200 150"
  },
  {
    "id" : "scale-behaviour", "type" : "ClutterBehaviourScale",
    "x-scale-start" : 1.0, "x-scale-end" : 0.7,
    "y-scale-start" : 1.0, "y-scale-end" : 0.7,
    "alpha" : {
      "timeline" : "scale-timeline",
      "mode" : "ease-out-sine"
    }
  },
  {
    "id" : "fade-behaviour", "type" : "ClutterBehaviourOpacity",
    "opacity-start" : 255, "opacity-end" : 0,
    "alpha" : {
      "timeline" : "fade-timeline",
      "mode" : "ease-out-sine"
    }
  },
  {
    "id" : "main-stage",
    "type" : "ClutterStage",
    "color" : "#ffffff",
    "visible" : true,
    "reactive" : true,
    "signals" : [
      { "name" : "key-press-event", "handler" : "do_quit" },
      { "name" : "destroy", "handler" : "do_quit" }
    ],
    "children" : [
      {
        "id" : "red-button",
        "type" : "ClutterRectangle",
        "visible" : true,
        "reactive" : true,
        "color" : "#dd0000",
        "opacity" : 255,
        "x" : 100, "y" : 100, "width" : 300, "height" : 300,
        "rotation" : [
          { "z-axis" : [ 45.0, [ 200, 200 ] ] }
        ],
        "signals" : [
          { "name" : "button-press-event", "handler" : "do_press" }
        ],
        "behaviours" : [
          "move-behaviour",
          "scale-behaviour",
          "fade-behaviour"
        ]
      }
    ]
  }
]
'''

class TestScript:
    def __init__ (self, *args, **kwargs):
        self._score = clutter.Score()

    def do_quit (self, *args):
        print "quitting"
        clutter.main_quit()

    def do_timeline_start (self, score, timeline):
        print "timeline started: %s" % (clutter.get_script_id(timeline))

    def do_press (self, actor, event):
        print "running the score"
        self._score.connect('timeline-started', self.do_timeline_start)
        self._score.connect('completed', self.do_quit)
        self._score.start()

        return True

    def load_script (self):
        self._script = clutter.Script()
        try:
            self._script.load_from_data(BUFFER, -1)
            self._script.connect_signals(self)
        except Exception, exc:
            print "Unable to load buffer: %s" % (exc)
            sys.exit(1)

    def run (self):
        self.load_script()

        self._timelines = self._script.get_objects('move-timeline',
                                                   'scale-timeline',
                                                   'fade-timeline')
        for timeline in self._timelines:
            print "Timeline: %s" % (clutter.get_script_id (timeline))

        self._score.append(timeline=self._timelines[0])
        self._score.append(timeline=self._timelines[1], parent=self._timelines[0])
        self._score.append(timeline=self._timelines[2], parent=self._timelines[1])
        assert(3 == len(self._score.list_timelines()))

        self._stage = self._script.get_object('main-stage')
        self._stage.show_all()

        clutter.main()

        return 0

if __name__ == '__main__':
    test = TestScript()
    sys.exit(test.run())
