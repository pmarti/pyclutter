# -*- Mode: Python; py-indent-offset: 4 -*-

from math import sin, pi
from _clutter import *

__version__ = _clutter.__version__
MAX_ALPHA = _clutter.MAX_ALPHA

# provide pure-python implementations of the commodity alpha functions
def ramp_func (alpha, data):
    """
    Simple ramp function.
    """
    cur = alpha.get_timeline().get_current_frame()
    frames = alpha.get_timeline().get_n_frames()
    if cur < (frames / 2):
        return cur * MAX_ALPHA / (frames / 2)
    else:
        return (frames - cur) * MAX_ALPHA / (frames / 2)

def ramp_inc_func (alpha, data):
    """
    Simple monotonic increasing ramp function.
    """
    cur = alpha.get_timeline().get_current_frame()
    frames = alpha.get_timeline().get_n_frames()
    return cur * MAX_ALPHA / frames

def ramp_dec_func (alpha, data):
    """
    Simple monotonic decreasing ramp function.
    """
    cur = alpha.get_timeline().get_current_frame()
    frames = alpha.get_timeline().get_n_frames()
    return (frames - cur) * MAX_ALPHA / frames

def sine_func (alpha, data):
    """
    Simple sine waveform function.
    """
    cur = alpha.get_timeline().get_current_frame()
    frames = alpha.get_timeline().get_n_frames()
    x = cur * pi * 2 / frames
    sine = (sin (x - (pi / 2)) + 1) * .5
    return int (sine * MAX_ALPHA)
