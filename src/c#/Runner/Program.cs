using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using FuzzySearch;

namespace Runner
{
    class Program
    {
        static void Main(string[] args)
        {
            var items = new List<string>();


            string line;

            var file = new StreamReader("c:\\Users\\Rob\\Desktop\\Vendors.txt");
            while ((line = file.ReadLine()) != null)
            {
                items.Add(line);
            }

            file.Close();

            Stopwatch sw = Stopwatch.StartNew();
            var service = new FuzzySearchService(items);
            Console.WriteLine("Initilaized in: {0}ms", sw.ElapsedMilliseconds);

            while (true)
            {
                var input = Console.ReadLine();
                var timer = Stopwatch.StartNew();
                var results = service.Search(input);
                Console.WriteLine("Search took {0}ms", timer.ElapsedMilliseconds);
                foreach (var result in results.OrderByDescending(r => r.Score))
                {
                    Console.WriteLine(result);
                }
            }
        }
    }
}
