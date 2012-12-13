import collection.mutable
import scala.collection.mutable.{Map, SynchronizedMap, HashMap}

class FuzzySearchService(wordsToIndex: List[String]){
  require(wordsToIndex != null)

  private var index : mutable.Map[String, String] = this.init(wordsToIndex)

  def init(wordsToIndex: List[String]) : mutable.Map[String, String] = {
    var indexToBuild = mutable.Map[String, String]()

    for (word <- wordsToIndex){
      println(word)
    }
    indexToBuild
  }
}
