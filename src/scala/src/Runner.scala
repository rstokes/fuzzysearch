object Runner {
  def main(args: Array[String]) {
    var list : List[String] = List()

    list ::= "FEstival"
    list ::= "China"
    list ::= "canada"
    list ::= "mexico"
    list ::= "florida"


    var inst = new FuzzySearchService(list)
  }
}