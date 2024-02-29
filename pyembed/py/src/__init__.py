from .utils import ndarray_from_address


def add_in_python(a: int, b: int) -> int:
    print(f"add_in_python({a}, {b}) -> {a + b}")
    return a + b


def _ndarray_from_array(arr):
    shape = (arr.size,)
    address = arr.data_address
    out = ndarray_from_address(address, "<f8", shape)
    return out


def transform_array(output, input):
    print(f"transform_array({output}, {input})")
    inp = _ndarray_from_array(input)
    out = _ndarray_from_array(output)
    out[:] = inp * 2
