# Embedding Python in Scala

+ Install `cffi`

```bash
pip install -r pyembed/requirements.txt
```

+ Set `JAVA_HOME` and `PYTHON_VERSION` in `pyembed/Makefile`

+ Clean previous build

```bash
cd pyembed 
make clean
make dirs
```

+ Define Java API in `pyembed/java/PyEmbed.java`

+ Create JNI header file

```bash
make PyEmbed.h 
```

+ Put python code in `pyembed/py/src`

+ Write python ffi in `pyembed/py/plugin.h` and `pyembed/py/plugin.py` using code from `pyembed/py/src`

+ Copy JNI C signatures from `pyembed/target/pyembed_PyEmbed.h` to `pyembed/cpp/pyembed_java_tpl.cpp`

+ Compile shared library

```bash
make
```

+ Use JNI API in Scala like:

```scala
import pyembed.PyEmbed

object Hello extends App {
  System.loadLibrary("pyembed_java")
  //  System.loadLibrary("pyembed")
  val pyembed = new PyEmbed()
  val r: Int = pyembed.addInPython(5, 6)
  println(s"Got $r")
}
```

+ Run with `-Djava.library.path=pyembed/target`

