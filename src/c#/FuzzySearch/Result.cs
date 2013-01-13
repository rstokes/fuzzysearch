namespace FuzzySearch
{
    public class Result
    {
        private string searched;
        private string result;
        private double score;

        public Result(string searched, string result, double score)
        {
            this.searched = searched;
            this.result = result;
            this.score = score;
        }

        public string Searched
        {
            get { return searched; }
        }

        public string Result1
        {
            get { return result; }
        }

        public double Score
        {
            get { return score; }
        }

        public override string ToString()
        {
            return string.Format("Searched: {0}, Result: {1}, Score: {2}", searched, result, score);
        }  
    }
}
