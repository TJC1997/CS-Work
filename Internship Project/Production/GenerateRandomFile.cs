using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Production
{
    public class GenerateRandomFile
    {
        public GenerateRandomFile(int numOfData, int numOfParams, int randomRange, string fileName)
        {
            Random rnd = new System.Random();
            string allText = "";
            for (int i = 0; i < numOfData; i++)
            {
                string text = "";
                string time = "2019-5-21 12:" + rnd.Next(60).ToString() + ",";
                text = time + i.ToString() + "," + numOfParams.ToString();
                for (int j = 0; j < numOfParams; j++)
                {
                    text = text + "," + rnd.Next(randomRange).ToString();
                }
                allText = allText + text + Environment.NewLine;
            }
            System.IO.File.WriteAllText(@"C:\Users\chento\Desktop\EsiProject\Production\testFile\" + fileName + ".txt", allText);
        }
    }
}
