SHELL := /bin/bash

JAVA_HOME := /usr/lib/jvm/java-17-openjdk-amd64

PYTHON_VERSION := 3.10

all: dirs libpyembed_java.so

.PHONY: all clean

dirs:
	mkdir -p target

libpyembed.so:
	python3 py/plugin.py
	rm -f target/pyembed_plugin.o
	rm -f target/pyembed_plugin.c

PyEmbed.h:
	javac -d target/ -h target/ java/PyEmbed.java
	rm -rf target/pyembed

pyembed_java.o: PyEmbed.h
	sed 's/PYTHON_VERSION/$(PYTHON_VERSION)/g' cpp/pyembed_java_tpl.cpp > target/pyembed_java.cpp
	g++ -c -fPIC -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux target/pyembed_java.cpp -o target/pyembed_java.o
	rm -f target/pyembed_java.cpp

libpyembed_java.so: pyembed_java.o libpyembed.so
	g++ target/pyembed_java.o -o target/libpyembed_java.so -shared -fPIC -L./target -lpyembed -lc -ldl -Wl,-rpath=\$$ORIGIN
	rm -f target/pyembed_java.o
#	rm -f target/pyembed_PyEmbed.h

clean:
	rm -rf target/pyembed
	rm -f target/*


test1:
	g++ -fPIC cpp/test1.cpp -o target/test1 -Ltarget -lpyembed


test2:
	g++ -fPIC cpp/test2.cpp -o target/test2 -ldl
