object Runner {
  def main(args: Array[String]) {
    var list : List[String] = List()

    list ::= "FEstival Tentman"
    list ::= "festival Shimmer"


    var startTime = System.currentTimeMillis()

    val inst = new FuzzySearchService(list)
    println(String.format("Initialization took: %s ms", (java.lang.System.currentTimeMillis() - startTime).toString))

    startTime = System.currentTimeMillis()
    val res = inst.search("Festival")
    println(String.format("Search took: %s ms", (System.currentTimeMillis() - startTime).toString))


    println(res)
    val a = 3
  }
}