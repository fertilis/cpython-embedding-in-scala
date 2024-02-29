package example

import pyembed.PyEmbed

object Hello extends App {
  System.loadLibrary("pyembed_java")
//  System.loadLibrary("pyembed")
  val pyembed = new PyEmbed()
  val r: Int = pyembed.addInPython(5, 6)
  println(s"Got $r")
}
