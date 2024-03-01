#include <dlfcn.h>

#include "pyembed_PyEmbed.h"
#include "../py/plugin.h"


typedef int (*add_in_python_t)(int, int);
typedef void (*transform_array_t)(struct ArrayPtr, const struct ArrayPtr);

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

JNIEXPORT void JNICALL Java_pyembed_PyEmbed_transformArray
  (JNIEnv* env, jobject obj, jdoubleArray output, jdoubleArray input)
{
    transform_array_t f = reinterpret_cast<transform_array_t>(dlsym(load_pyemb_once(), "transform_array"));
    jdouble* input_arr_ptr = env->GetDoubleArrayElements(input, nullptr);
    jsize input_size = env->GetArrayLength(input);
    ArrayPtr input_ptr = { (uint64_t)input_arr_ptr, (size_t)input_size };
    jdouble* output_arr_ptr = env->GetDoubleArrayElements(output, nullptr);
    jsize output_size = env->GetArrayLength(output);
    ArrayPtr output_ptr = { (uint64_t)output_arr_ptr, (size_t)output_size };
    f(output_ptr, input_ptr);
    env->ReleaseDoubleArrayElements(output, output_arr_ptr, 0);
    env->ReleaseDoubleArrayElements(input, input_arr_ptr, 0);
}
