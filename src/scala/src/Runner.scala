object Runner {
  def main(args: Array[String]) {
    var list : List[String] = List()

    list ::= "FEstival"


    var inst = new FuzzySearchService(list)
  }
}