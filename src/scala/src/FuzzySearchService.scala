import collection.mutable
import collection.mutable.Map
import collection.mutable.HashSet

class FuzzySearchService(wordsToIndex: List[String]){
  require(wordsToIndex != null)

  private val index: Map[String, Array[String]] = this.init(wordsToIndex)

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
        val encodedChar: Char = encodeChar(charArray(index).toLower)
        if (encodedChar != 0)
          currentCode = encodedChar


        if (currentCode != previousCode)
          result += currentCode

        if (result.length == 4)
           return result.toString()

        if (currentCode != 0)
          previousCode = currentCode
      }
    }
    padSoundex(result).toString()
  }

  private def init(phrasesToIndex: List[String]) : Map[String, Array[String]] = {
    val indexToBuild = Map[String, Array[String]]()

    for (phrase <- phrasesToIndex){
      val words = phrase.split(" ")
      for (word <- words){
        val hash = soundex(word)
        if (indexToBuild.contains(hash)){
          indexToBuild.get(hash) +: phrase
        }else {
          indexToBuild += hash -> Array(phrase)
        }
      }
    }
    println(indexToBuild)
    indexToBuild
  }

  private def score(input1: String, input2: String) : Double = {
    return diceCoefficient(input1, input2) * 100
  }

  private def diceCoefficient(input1: String, input2: String) : Double = {
    val set1: HashSet[String] = HashSet()
    val set2: HashSet[String] = HashSet()

    for(index <- 0 to input1.length - 1){
      val x1: Char = input1(index)
      val x2: Char = input1(index)
      val tmp: String = new String(Array(x1, x2))
      set1.add(tmp)
    }
    for(index <- 0 to input2.length - 1){
      val x1: Char = input2(index)
      val x2: Char = input2(index)
      val tmp: String = new String(Array(x1, x2))
      set2.add(tmp)
    }

    val intersection : HashSet[String] = set1.intersect(set1)
    return (intersection.size * 2D)/(set1.size + set2.size)
  }



  def search(input: String) : List[(String, String, Double)] = {
     var result : List[(String, String, Double)] = List()

    for (valueToSearch <- input.split(" ")){
      val valuesFromIndex = index.get(soundex(valueToSearch)).get
      for (value <- valuesFromIndex){
        result ::= (input, value, score(input, value))
      }
    }

    return result
  }
}
