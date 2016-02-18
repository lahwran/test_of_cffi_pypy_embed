# file plugin_build.py
import cffi
import os
import glob
import shutil
ffi = cffi.FFI()

class DerpOOPath(str):
    def __call__(self, *a, **kw):
        return DerpOOPath(os.path.abspath(os.path.join(self, *a, **kw)))

    def dirname(self):
        return DerpOOPath(os.path.abspath(os.path.dirname(self)))

    def basename(self):
        return DerpOOPath(os.path.basename(self))



pypath = DerpOOPath(__file__).dirname()
os.chdir(pypath)
path = pypath("..")
libpath = path("lib")
include = path("include")

with open(pypath("plugin.h")) as f:
    lines = [line for line in f if not line.startswith('#')]
    ffi.embedding_api(''.join(lines))

with open(pypath('plugin.c')) as f:
    ffi.set_source("my_plugin", f.read())

with open(pypath('onload.py')) as f:
    ffi.embedding_init_code(f.read())

ffi.compile(target="libmy_plugin.*", verbose=True)
shutil.copy(pypath("plugin.h"), include('plugin.h'))
libfile = DerpOOPath(glob.glob(pypath("libmy_plugin.*"))[0])
shutil.copy(libfile, libpath(libfile.basename()))
