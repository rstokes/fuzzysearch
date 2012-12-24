object Runner {
  def main(args: Array[String]) {
    var list : List[String] = List()

    list ::= "FEstival Tentman"
    list ::= "China"
    list ::= "canada"
    list ::= "mexico"
    list ::= "florida"


    var inst = new FuzzySearchService(list)
  }
}