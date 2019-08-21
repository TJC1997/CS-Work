using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Production
{
    public class ParseTxT
    {
        public string path;


        public ParseTxT(string p = null)
        {
            path = p;
        }

        public void setPath(string p)
        {
            path = p;
        }

        public string getPath()
        {
            return path;
        }

        public MyData[] GetTxTArr()
        {
            var MD = new List<MyData>();
            string line = "";
            using (StreamReader sr = new StreamReader(path))
            {
                line = sr.ReadLine();
                while (line != null)
                {
                    if (line != "")
                    {
                        MyData element = new MyData();
                        int i = 0;
                        string timespan = "";
                        string index = "";
                        string numOfParams = "";
                        string parms = "";
                        if (line != "")
                        {
                            while (line[i] != ',')
                            {
                                timespan = timespan + line[i];
                                i++;
                            }
                            element.SetTimeSpan(timespan);
                            i++;
                            while (line[i] != ',')
                            {
                                index = index + line[i];
                                i++;
                            }
                            element.SetIndex(Convert.ToInt32(index));
                            i++;
                            while (line[i] != ',')
                            {
                                numOfParams = numOfParams + line[i];
                                i++;
                            }
                            i++;
                            int number = Convert.ToInt32(numOfParams);
                            element.SetNumOfParams(number);
                            List<double> ls = new List<double>();
                            for (int j = 0; j < number; j++)
                            {
                                while (line[i] != ',')
                                {
                                    parms = parms + line[i];
                                    i++;
                                    if (i == line.Length)
                                    {
                                        break;
                                    }
                                }
                                ls.Add(Convert.ToDouble(parms));
                                i++;
                                parms = "";
                            }
                            element.SetParameters(ls);
                        }
                        MD.Add(element);
                    }
                    line = sr.ReadLine();
                }
            }
            return MD.ToArray();
        }
    }
}
