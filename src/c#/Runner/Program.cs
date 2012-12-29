using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FuzzySearch;

namespace Runner
{
    class Program
    {
        static void Main(string[] args)
        {
            var searchObj = new FuzzySearchService(new List<string> {"values", "to try", "and index"});
            Console.ReadKey();
        }
    }
}
