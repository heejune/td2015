using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharpDebugExamples
{
    class Book
    {
        public Book()
        {
            Debugger.Break();
        }

        string title;

        public string Title { get; set; }
    }

    class Program
    {
        static void Main(string[] args)
        {
            // http://blogs.msdn.com/b/visualstudioalm/archive/2014/11/12/support-for-debugging-lambda-expressions-with-visual-studio-2015.aspx

            float[] values = Enumerable.Range(0, 100).Select(i => (float)i / 10).ToArray();

            Debugger.Break();
        }
    }
}
