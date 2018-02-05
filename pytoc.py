#! -*- coding:utf-8 -*-
import platform as pf
import ctypes as cp

if pf.system() == "Window":
    pass
elif pf.system() == "Linux":
    libc = cp.cdll.LoadLibrary("./libmain.so")

libc.foo()
