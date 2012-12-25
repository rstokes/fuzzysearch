class Result(search: String, result: String, score: Double) {
  override def toString() = {
    String.format("Search: %s, Returned: %s, Score: %d", search, result, score.toString)
  }
}
