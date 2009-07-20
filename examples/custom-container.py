import gobject
import clutter

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
        self._orientation = orientation
        self._children = []

    def set_orientation(self, orientation):
        self._orientation = orientation
        self.notify("orientation")
        self.queue_relayout()

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
    
    def do_remove(self, *children):
        for child in children:
            if child in self._children:
                self._children.remove(child)
                child.unparent()
                self.queue_relayout()
            else:
                raise Exception("Actor %s is not a child of %s" % (
                    child, self))

    def do_get_preferred_width(self, for_height):
        min_width = 0
        natural_width = 0
        for child in self._children:
            if not child.props.visible:
                continue
            child_min_width, child_natural_width = child.get_preferred_width(
                    for_height)
            if self._orientation == self.HORIZONTAL:
                min_width += child_min_width
                natural_width += child_natural_width
            else:
                min_width = max(min_width, child_min_width)
                natural_width = max(natural_width, child_natural_width)
        return (min_width, natural_width)

    def do_get_preferred_height(self, for_width):
        min_height = 0
        natural_height = 0
        for child in self._children:
            if not child.props.visible:
                continue
            child_min_height, child_natural_width = child.get_preferred_height(
                    for_width)
            if self._orientation == self.HORIZONTAL:
                min_height = max(min_height, child_min_height)
                natural_height = max(natural_height, child_natural_width)
            else:
                min_height += child_min_height
                natural_height += child_natural_width
        return (min_height, natural_height)


    def do_allocate(self, box, flags):
        child_x = child_y = 0
        for actor in self._children:
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
        for child in self._children:
            func(child, data)
        
    def do_paint(self):
        for actor in self._children:
            actor.paint()


if __name__ == '__main__':
    def on_button_press(box, event):
        box.props.orientation = not box.props.orientation
        return True

    import random
    stage = clutter.Stage()
    stage.connect('destroy', clutter.main_quit)

    box = SimpleBox()
    for i in range(5):
        rect = clutter.Rectangle()
        color = clutter.Color(random.randint(0, 255), random.randint(0, 255),
                random.randint(0, 255), 255)
        rect.set_color(color)
        rect.set_size(50, 50)
        box.add(rect)

    stage.add(box)
    box.set_reactive(True)
    box.connect('button-press-event', on_button_press)

    stage.show()
    clutter.main()
