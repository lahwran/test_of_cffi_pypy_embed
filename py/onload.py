from my_plugin import ffi

@ffi.def_extern()
def do_stuff(p):
    print("adding %d and %d" % (p.x, p.y))
    return p.x + p.y
