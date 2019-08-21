using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Production;
using Accord.Statistics.Models.Regression;
using Accord.Statistics.Models.Regression.Fitting;

namespace Console
{
    public class LogisticRegressionDemo
    {
        public static void Execute()
        {
            double[][] input =
            {
                new double[] { 55, 0 },
                new double[] { 28, 0 },
                new double[] { 65, 0 },
                new double[] { 46, 0 },
                new double[] { 86, 0 },
                new double[] { 56, 0 },
                new double[] { 85, 0 },
                new double[] { 33, 0 },
                new double[] { 21, 0 },
                new double[] { 42, 0 },
            };

            double[] output =
            {
                0, 0, 0, 1, 1, 1, 0, 0, 0, 1
            };
            LogisticRegression regression = new LogisticRegression(2);
            var trainer = new IterativeReweightedLeastSquares(regression);
            double delta = 0;
            do
            {
                // Perform an iteration
                delta = trainer.Run(input, output);


            } while (delta > 0.001);

            var b1 = regression.Coefficients[1];
            var b2 = regression.Coefficients[2];
            var b0 = regression.Intercept;
            System.Console.WriteLine(b0);
            System.Console.WriteLine(b1);
            System.Console.WriteLine(b2);

            var func = new Func<double, double, double>((x1, x2) =>
            {
                var result = 1 / (1 + Math.Exp(-b0 - b1 * x1 - b2 * x2));
                return result;
            });
            var age = 79;
            var smoking = 0;
            var r = func(age, smoking);
            System.Console.WriteLine("input x [age:{0}, smoking:{1}] is {2}", age, smoking, r);

            LogisticRegression LR = new LogisticRegression();
            LR.NumberOfInputs = 1;
            var learner = new IterativeReweightedLeastSquares<LogisticRegression>()
            {
                Tolerance = 1e-4,  // Let's set some convergence parameters
                Iterations = 100,  // maximum number of iterations to perform
                Regularization = 0
            };
            LR = learner.Learn(input, output);
            System.Console.WriteLine(LR.Intercept);
            System.Console.WriteLine(LR.GetOddsRatio(1)-1);
            System.Console.WriteLine(LR.GetOddsRatio(2)-1);
            double [] test=new double[] {79,0};
            System.Console.WriteLine(LR.Probability(test));
        }
    }
    class Program
    {
        /*
        static void Main(string[] args)
        {
            
            Random rnd = new System.Random();
            string inputPath = @"C:\Users\chento\Desktop\EsiProject\Production\testFile\PartsRawData.txt";
            string []lines=File.ReadAllLines(inputPath);
            string text = "";
            foreach (var line in lines)
            {
                text = text + "2019-5-21 12:" + rnd.Next(60).ToString() + ",";
                text = text + "0,1,";
                text = text + line+Environment.NewLine;
            }
            System.IO.File.WriteAllText(@"C:\Users\chento\Desktop\EsiProject\Production\testFile\Raw1.txt" , text);
               

         }*/
        static void Main(string[] args)
        {
            LogisticRegressionDemo.Execute();
            System.Console.ReadLine();
        }
    }
}
