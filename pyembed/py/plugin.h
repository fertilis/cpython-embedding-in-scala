#include <stdint.h>

int add_in_python(int a, int b);

struct ArrayPtr {
    uint64_t data_address;
    size_t size;
};

void transform_array(struct ArrayPtr output, const struct ArrayPtr input);
