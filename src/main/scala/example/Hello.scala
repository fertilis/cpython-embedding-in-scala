package example

import pyembed.PyEmbed

object Hello extends App {
  System.loadLibrary("pyembed_java")
  val pyembed = new PyEmbed()
  val r: Int = pyembed.addInPython(5, 6)
  println(s"Addition in python: $r")
  val inp: Array[Double] = Array(1.0, 2.0, 3.0, 4.0, 5.0)
  val out: Array[Double] = new Array[Double](5)
  pyembed.transformArray(out, inp)
  println(s"Transformed array: ${out.mkString(", ")}")
}
