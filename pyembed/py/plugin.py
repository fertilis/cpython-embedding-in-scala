import cffi
import os

project_root = os.path.abspath(f"{__file__}/../..")
py_root = os.path.abspath(f"{__file__}/..")
target_dir = os.path.abspath(f"{project_root}/target")

ffibuilder = cffi.FFI()

with open(f"{py_root}/plugin.h") as f:
    text = f.read()
    text = "".join(line for line in text.splitlines() if not line.startswith("#"))
    ffibuilder.embedding_api(text)

ffibuilder.set_source(
    "pyembed_plugin",
    """
#include "../py/plugin.h"
""",
)

ffibuilder.embedding_init_code(
    f"""
    import sys
    sys.path.insert(0, "{py_root}")
    from pyembed_plugin import ffi
    
    @ffi.def_extern()
    def add_in_python(a: int, b: int) -> int:
        import src
        return src.add_in_python(a, b)
    
    @ffi.def_extern()
    def transform_array(output: ffi.CData, input: ffi.CData):
        import src
        src.transform_array(output, input)
"""
)

ffibuilder.compile(tmpdir=target_dir, target="libpyembed.*", verbose=True)
