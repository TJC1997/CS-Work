using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Production
{
    public class ProductionData
    {
        private Queue<MyData> dataQueue;
        private string pattern;
        private int maxSize;
        List<MyData> ls;

        public ProductionData()
        {
            dataQueue = new Queue<MyData>();
            maxSize = -1;
            pattern = "yyyy-M-d H:m";
            ls = new List<MyData>();
        }

        public ProductionData(int size)
        {
            dataQueue = new Queue<MyData>();
            maxSize = size;
            pattern = "yyyy-M-d H:m";
        }

        public void SetSize(int size)
        {
            maxSize = size;
        }

        public void UnSetSize()
        {
            maxSize = -1;
        }

        public void SetPattern(string p)
        {
            pattern = p;
        }

        private void TransferToDate(MyData newData)
        {
            newData.SetDate(DateTime.ParseExact(newData.GetTimeSpan(), pattern, null));
        }

        public void AddSingleData(MyData newData)
        {
            if (maxSize != -1)
            {
                while (dataQueue.Count >= maxSize)
                {
                    dataQueue.Dequeue();
                }
            }
            TransferToDate(newData);
            dataQueue.Enqueue(newData);
            SortData(-1);
        }


        public void AddMutiData(MyData[] arr)
        {
            if (arr==null)
            {
                return;
            }
            for (int i = 0; i < arr.Length; i++)
            {
                AddSingleData(arr[i]);
            }
        }

        public MyData[] GetDataArr()
        {
            return ls.ToArray();
        }

        public MyData[] GetDataArr(int start, int num)
        {
            MyData[] dataArr = ls.ToArray();
            MyData[] finalArr = new MyData[num];
            for (int i = 0; i < num; i++)
            {
                finalArr[i] = dataArr[i + start];
            }
            List<MyData> ls2 = finalArr.ToList();
            return ls2.ToArray();
        }

        public void SortData(int index)
        {
            ls = dataQueue.ToList();
            if (index >= 0)
            {
                ls = ls.OrderBy(x => x.GetParameters()[index]).ToList();             
            }
            else
            {
                ls = ls.OrderBy(x => x.GetDate()).ToList();
            }
        }

        public void ClearData()
        {
            dataQueue = new Queue<MyData>();
            ls = new List<MyData>();
        }
        /*
        public string WriteToCsv(string fileName)
        {
            var csv = new StringBuilder();
            string newLine = "";
            double[] dataArr = dataQueue.ToArray();
            for (int i = 0; i < dataArr.Length; i++)
            {
                newLine = newLine + dataArr[i] + "\n";
            }
            csv.AppendLine(newLine);
            string path = Directory.GetCurrentDirectory() + @"\" + fileName+".csv";
            Console.WriteLine(path);
            File.WriteAllText(path, csv.ToString());
            return path;
        }
        */
    }
}
