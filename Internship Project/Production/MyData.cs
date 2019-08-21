using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Production
{
    public class MyData
    {
        private string timeSpan;
        private int index;
        private int numOfParams;
        private List<double> parameters;
        private DateTime date;

        public MyData()
        {
            timeSpan = "";
            index = 0;
            numOfParams = 0;
            parameters =null;
        }

        public MyData(string t, int i, int n, List<double> p)
        {
            timeSpan = t;
            index = i;
            numOfParams = n;
            parameters = p;
        }

        public string WriteToLine()
        {
            string line = timeSpan + "\t" + index + "\t" + numOfParams + "\t";
            for (int i = 0; i <numOfParams; i++)
            {
                line = line + parameters[i] + "\t";
            }
            return line;
        }

        public string GetTimeSpan() { return timeSpan; }
        public int GetIndex() { return index; }
        public int GetNumOfParams() { return numOfParams; }
        public List<double> GetParameters() { return parameters; }
        public DateTime GetDate() { return date; }

        public void SetTimeSpan(string st) { timeSpan = st; }
        public void SetIndex(int i) { index = i; }
        public void SetNumOfParams(int n) { numOfParams = n; }
        public void SetParameters(List<double> p) { parameters = p; }
        public void SetDate(DateTime d) { date = d; }
    }
}
