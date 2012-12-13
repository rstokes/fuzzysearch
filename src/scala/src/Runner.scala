object Runner {
  def main(args: Array[String]) {
    var list : List[String] = List()

    list ::= "test"

    var inst = new FuzzySearchService(list)
  }
}