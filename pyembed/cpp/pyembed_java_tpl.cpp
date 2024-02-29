#include <dlfcn.h>

#include "pyembed_PyEmbed.h"
#include "../py/plugin.h"


typedef int (*add_in_python_t)(int, int);

static void* pyemb = nullptr;

static void* load_pyemb_once() {
    if (pyemb == nullptr) {
        dlopen("libpythonPYTHON_VERSION.so", RTLD_LAZY|RTLD_GLOBAL); // see https://cffi.readthedocs.io/en/latest/embedding.html#issues-about-using-the-so
        pyemb = dlopen("libpyembed.so", RTLD_NOW); // RTLD_LAZY | RTLD_DEEPBIND ?
    }
    return pyemb;
}

JNIEXPORT jint JNICALL Java_pyembed_PyEmbed_addInPython
  (JNIEnv* env, jobject obj, jint a, jint b)
{
    int a_n = (int)a;
    int b_n = (int)b;
    add_in_python_t f = reinterpret_cast<add_in_python_t>(dlsym(load_pyemb_once(), "add_in_python"));
    int result = f(a_n, b_n);
    return (jint)result;
}
