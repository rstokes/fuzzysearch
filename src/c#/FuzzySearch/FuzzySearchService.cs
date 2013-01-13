using System;
using System.Collections.Generic;
using System.Text;

namespace FuzzySearch
{
    public class FuzzySearchService
    {
        private Dictionary<string, List<string>> index;

        #region Soundex
        private string EncodeChar(char c)
        {
            switch (Char.ToLower(c))
            {
                case 'b':
                case 'f':
                case 'p':
                case 'v':
                    return "1";
                case 'c':
                case 'g':
                case 'j':
                case 'k':
                case 'q':
                case 's':
                case 'x':
                case 'z':
                    return "2";
                case 'd':
                case 't':
                    return "3";
                case 'l':
                    return "4";
                case 'm':
                case 'n':
                    return "5";
                case 'r':
                    return "6";
                default:
                    return string.Empty;
            }
        }

        private string Soundex(string data)
        {
            StringBuilder result = new StringBuilder();

            if (!string.IsNullOrEmpty(data))
            {
                string previousCode, currentCode;
                result.Append(Char.ToUpper(data[0]));
                previousCode = string.Empty;

                for (int i = 1; i < data.Length; i++)
                {
                    currentCode = EncodeChar(data[i]);

                    if (currentCode != previousCode)
                        result.Append(currentCode);

                    if (result.Length == 4) break;

                    if (!currentCode.Equals(string.Empty))
                        previousCode = currentCode;
                }
            }
            if (result.Length < 4)
                result.Append(new String('0', 4 - result.Length));

            return result.ToString();
        }
        #endregion

        private IEnumerable<string> ParseValue(string value)
        {
            return value.ToLower().Split(' ');
        }

        private Dictionary<string, List<string>> Init(IEnumerable<string> valuesToIndex)
        {
            var indexToBuild = new Dictionary<string, List<string>>();

            foreach (var item in valuesToIndex)
            {
                var parsedInputs = ParseValue(item);
                foreach (var value in parsedInputs)
                {
                    var hash = Soundex(value);
                    List<string> currentlyIndexedItems;
                    if (indexToBuild.TryGetValue(hash, out currentlyIndexedItems))
                    {
                        currentlyIndexedItems.Add(item);
                    }
                    else
                    {
                        indexToBuild.Add(hash, new List<string> { item });
                    }
                }
            }
            return indexToBuild;
        }

        public FuzzySearchService(IEnumerable<string> valuesToIndex)
        {
            index = Init(valuesToIndex);
        }

        public IEnumerable<Result> Search(string inputToSearch)
        {
            List<Result> results = new List<Result>();
            foreach (var input in ParseValue(inputToSearch))
            {
                List<string> valuesFromIndex;
                if(index.TryGetValue(Soundex(input), out valuesFromIndex))
                {
                    foreach (var resultFromIndex in valuesFromIndex)
                    {
                        results.Add(new Result(inputToSearch, resultFromIndex, Score(inputToSearch, resultFromIndex)));
                    }
                }
            }

            return results;
        }

        private double Score(string in1, string in2)
        {
            return DicesCoeffienct(in1.ToLower(), in2.ToLower())*100;
        }

        private double DicesCoeffienct(string in1, string in2)
        {
            HashSet<string> nx = new HashSet<string>();
            HashSet<string> ny = new HashSet<string>();
 
            for(int i = 0; i < in1.Length - 1; i++)
            {
                char x1 = in1[i];
                char x2 = in1[i + 1];
                string temp = x1.ToString() + x2.ToString();
                nx.Add(temp);
            }
            for(int j = 0; j < in2.Length - 1; j++)
            {
                char y1 = in2[j];
                char y2 = in2[j + 1];
                string temp = y1.ToString() + y2.ToString();
                ny.Add(temp);
            }
 
            HashSet<string> intersection = new HashSet<string>(nx);
            intersection.IntersectWith(ny);
 
            double dbOne = intersection.Count;
            return (2 * dbOne) / (nx.Count + ny.Count);
        }
    }
}
