import collection.mutable.Map

class FuzzySearchService(wordsToIndex: List[String]){
  require(wordsToIndex != null)

  private var index : Map[String, String] = this.init(wordsToIndex)

  private def encodeChar(value: Char) : Char = {
    value match{
      case 'b' => '1'
      case 'f' => '1'
      case 'p' => '1'
      case 'v' => '1'
      case 'c' => '2'
      case 'g' => '2'
      case 'j' => '2'
      case 'k' => '2'
      case 'q' => '2'
      case 's' => '2'
      case 'x' => '2'
      case 'z' => '2'
      case 'd' => '3'
      case 't' => '3'
      case 'l' => '4'
      case 'm' => '5'
      case 'n' => '5'
      case 'r' => '6'
      case _ => 0

    }
  }

  //TODO: This can probably be done better in an inline fashion
  private def padSoundex(value: StringBuilder) : StringBuilder ={
    var result : StringBuilder = value
    if (result.length != 4)
    {
      if (result.length == 1) result = result + '0' + '0' + '0'
      else if (result.length == 2) result = result + '0' + '0'
      else if (result.length == 3) result = result + '0'
    }
    result
  }

  private def soundex(data: String) : String = {
    var result : StringBuilder = new StringBuilder(4)

    if (data != null && data.length() > 0) {
      var previousCode : Char = Char.MinValue
      var currentCode : Char = Char.MinValue

      val charArray : Array[Char] = data.toCharArray

      result +=  data.charAt(0).toUpper

      for (index <- 1 to charArray.length - 1){
        currentCode = encodeChar(charArray(index).toLower)

        if (currentCode != previousCode)
          result += currentCode

        if (result.length == 4)
           return result.toString()

        if (currentCode != '\0')
          previousCode = currentCode
      }
    }
    padSoundex(result).toString()
  }


  def init(wordsToIndex: List[String]) : Map[String, String] = {
    var indexToBuild = Map[String, String]()

    for (word <- wordsToIndex){
      var toIndex : String = soundex(word)

      println("Indexing value: " + toIndex)
    }
    indexToBuild
  }
}
