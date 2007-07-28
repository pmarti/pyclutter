# -*- Mode: Python; py-indent-offset: 4 -*-

from _clutter import *

__version__ = _clutter.__version__
MAX_ALPHA = _clutter.MAX_ALPHA

# use the pygtk module lazy loading stuff
from gtk._lazyutils import LazyNamespace, LazyModule

keysyms = LazyModule('keysyms', locals())
