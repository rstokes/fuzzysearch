fuzzysearch
===========

Fuzzy String Searching

The service takes a list of strings, up to more than 10,000, and indexes them by each word.  The Search method takes a string and does a lookup
by each word in the string.  The results are then scored using Dice's coefficient.

There is a .net implementation in C# and a jvm implementation in Scala.  The binaries are available in the bin folder.

Simple example usage in scala:
```scala
import fuzzysearch._

object Run {
  def main(args: Array[String]) : Unit = {
    val itemsToIndex = List("Successful Beach", "Virginia Politican", "South Beach", "Grand Cayman", "Caymon Brac")

    val fuzzyService = new FuzzySearchService(itemsToIndex)

    val results = fuzzyService.search("succesful politician")

    results.sortBy(- _.score).foreach(result => println(result))
  }
}
```
