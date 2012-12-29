using System.Collections.Generic;

namespace FuzzySearch
{
    public class FuzzySearchService
    {
        private Dictionary<string, string> index;

        private IEnumerable<string> ParseValue(string value)
        {
            return value.ToLower().Split(' ');
        }

        private void Init(IEnumerable<string> valuesToIndex)
        {
            var indexToBuild = new Dictionary<string, string>();

            foreach (var item in valuesToIndex)
            {
               
            }
        }

        public FuzzySearchService(IEnumerable<string> valuesToIndex)
        {
            Init(valuesToIndex);
        }
    }
}
