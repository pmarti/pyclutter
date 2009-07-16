# -*- Mode: Python; py-indent-offset: 4 -*-

try:
    import ltihooks
    ltihooks # pyflakes
except ImportError:
    ltihooks = None

import sys

# fixes weird linker bugs on nvidia
try:
    import dl
    sys.setdlopenflags(dl.RTLD_LAZY|dl.RTLD_GLOBAL)
except ImportError:
    try:
        import platform
        if platform.system() == 'Linux' and platform.machine() in \
                ['x86_64', 'amd64']:
            try:
                import ctypes, ctypes.util
                ctypes.CDLL(ctypes.util.find_library('GL'),
                        mode=ctypes.RTLD_GLOBAL)
            except:
                pass
    except ImportError:
        pass

# For broken embedded programs which forgot to call Sys_SetArgv
if not hasattr(sys, 'argv'):
    sys.argv = []

# load the required modules:
import gobject as _gobject

ver = getattr(_gobject, 'pygobject_version', ())
if ver < (2, 11, 1):
    raise ImportError("PyClutter requires PyGObject 2.11.1 or higher, but %s was found" % (ver,))

if 'clutter._clutter' in sys.modules:
    _clutter = sys.modules['clutter._clutter']
else:
    from clutter import _clutter

import cogl

if ltihooks:
    try:
        ltihooks.uninstall()
        del ltihooks
    except:
        pass

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

from clutter._clutter import *

timeline_new_for_duration = _Deprecated(_clutter, 'Timeline', 'timeline_new_for_duration', 'clutter')
rectangle_new_with_color =  _Deprecated(_clutter, 'Rectangle', 'rectangle_new_with_color', 'clutter')

del _Deprecated, _DeprecatedConstant
