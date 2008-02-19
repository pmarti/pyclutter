# -*- Mode: Python; py-indent-offset: 4 -*-

import sys

# For broken embedded programs which forgot to call Sys_SetArgv
if not hasattr(sys, 'argv'):
    sys.argv = []

# load the required modules:
import gobject as _gobject

ver = getattr(_gobject, 'pygobject_version', ())
if ver < (2, 11, 1):
    raise ImportError("PyGTK requires PyGObject 2.11.1 or higher, but %s was found" % (ver,))

if 'clutter._clutter' in sys.modules:
    _clutter = sys.modules['clutter._clutter']
else:
    from clutter import _clutter

# use the pygtk module lazy loading stuff
from gtk._lazyutils import LazyNamespace, LazyModule
# and our own for the deprecation warnings
from clutter.deprecation import _Deprecated, _DeprecatedConstant

def _init ():
    import sys

    try:
        sys_path = sys.path[:]

        try:
            _clutter.init()
        except RuntimeError, e:
            import warnings
            warnings.warn(str(e), _clutter.Warning)
    finally:
        if sys.path != sys_path:
            sys.path[:] = sys_path

keysyms = LazyModule('keysyms', locals())

_init()

__version__ = _clutter.__version__
MAX_ALPHA = _clutter.MAX_ALPHA

from clutter._clutter import *

stage_get_default = _Deprecated(_clutter, 'Stage', 'stage_get_default', 'clutter')

del _Deprecated, _DeprecatedConstant
