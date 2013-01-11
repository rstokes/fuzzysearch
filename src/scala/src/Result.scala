case class Result(search: String, result: String, score: Double) {
  override def toString() = {
    "Searched: " + search + " Result: " + result + " Score: " + score.toString
  }
}
