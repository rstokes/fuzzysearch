package fuzzysearch

import collection.mutable.ListBuffer
import scala.io.Source

object Runner {
  def main(args: Array[String]) {
    val list: ListBuffer[String] = ListBuffer()


    val s = Source.fromFile("/Users/rob/Desktop/movies.txt")
    val lines = s.getLines()
    for (line <- lines){
      list.append(line)
    }

    var startTime = System.currentTimeMillis()
    val inst = new FuzzySearchService(list.toList)
    println(String.format("Initialization took: %s ms", (java.lang.System.currentTimeMillis() - startTime).toString))

    while(true){
      val line = readLine()
      startTime = System.currentTimeMillis()
      val results = inst.search(line).sortBy(- _.score)
      println(String.format("Search took: %s ms", (System.currentTimeMillis() - startTime).toString))
      results.foreach(result => println(result.toString()))
    }
  }
}