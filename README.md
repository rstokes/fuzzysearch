Fuzzy Search
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
Results:
```
Searched: succesful politician Result: Successful Beach Score: 52.94117647058824
Searched: succesful politician Result: Virginia Politican Score: 50.0
```

Simple example using C#:
```csharp
using System;
using System.Collections.Generic;
using System.Linq;
using FuzzySearch;

namespace Run
{
    class Program
    {
        static void Main(string[] args)
        {
            var ItemsToIndex = new List<string>()
                {
                    "Successful Beach",
                    "Virginia Politican",
                    "South Beach",
                    "Grand Cayman",
                    "Caymon Brac"
                };

            var FuzzyService = new FuzzySearchService(ItemsToIndex);

            var Results = FuzzyService.Search("succesful politician").OrderByDescending(r => r.Score);

            foreach (var result in Results)
            {
                Console.WriteLine(result);
            }

            Console.ReadKey();
        }
    }
}

```
Results:
```
Searched: succesful politician, Result: Successful Beach, Score: 52.9411764705882
Searched: succesful politician, Result: Virginia Politican, Score: 50
```
