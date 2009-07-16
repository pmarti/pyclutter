import gobject
import clutter

#class SimpleBox(clutter.Group):
class SimpleBox(clutter.Actor, clutter.Container):
    __gtype_name__ = 'SimpleBox'
    __gproperties__ = {
            'orientation': (gobject.TYPE_INT, 'Orientation', 'Box orientation',
                0, 1, 0, gobject.PARAM_READWRITE),
    }
    HORIZONTAL = 0
    VERTICAL = 1
    def __init__(self, orientation=0):
        clutter.Actor.__init__(self)
        #clutter.Group.__init__(self)
        self._orientation = orientation
        self._children = []

    def set_orientation(self, orientation):
        self._orientation = orientation
        self.notify("orientation")

    def get_orientation(self):
        return self._orientation

    def do_get_property(self, pspec):
        if pspec.name == 'orientation':
            return self.get_orientation()

    def do_set_property(self, pspec, value):
        if pspec.name == 'orientation':
            self.set_orientation(value)

    def do_add(self, *children):
        for child in children:
            if child in self._children:
                raise Exception("Actor %s is already a children of %s" % (
                    child, self))
            self._children.append(child)
            child.set_parent(self)
            self.queue_relayout()
    
    def do_allocate(self, box, flags):
        child_x = child_y = 0
        #for actor in self._children:
        for actor in self.get_children():
            w, h = actor.get_preferred_size()[2:]
            child_box = clutter.ActorBox()
            child_box.x1 = child_x
            child_box.y1 = child_y
            child_box.x2 = child_box.x1 + w
            child_box.y2 = child_box.y1 + h
            actor.allocate(child_box, flags)
            if self._orientation == self.HORIZONTAL:
                child_x += w
            else:
                child_y += h
        clutter.Actor.do_allocate(self, box, flags)

    def do_foreach(self, func, data=None):
        print 'foreach', func, data
        func(self, data)
        

    def do_paint(self):
        for actor in self._children:
            print 'paint', actor
            actor.paint()
        #clutter.Group.paint(self)

def funny_func(*args):
    print 'funny_func', args

if __name__ == '__main__':
    import random
    stage = clutter.Stage()
    stage.connect('destroy', clutter.main_quit)

    box = SimpleBox()
    #box = clutter.Group()
    for i in range(5):
        rect = clutter.Rectangle()
        color = clutter.Color(random.randint(0, 255), random.randint(0, 255),
                random.randint(0, 255), 255)
        rect.set_color(color)
        rect.set_size(50, 50)
        box.add(rect)

    box.set_size(300, 300)
    stage.add(box)
    box.foreach(funny_func, 'baum')
    #print box.get_children()

    stage.show()
    clutter.main()
