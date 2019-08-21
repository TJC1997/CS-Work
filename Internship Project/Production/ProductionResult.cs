using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MathNet.Numerics.LinearAlgebra;
using MathNet.Numerics.LinearAlgebra.Double;
//using Meta.Numerics.Statistics.Distributions;
using Accord.Statistics.Distributions.Univariate;
using Accord.Statistics.Models.Regression;
using Accord.Statistics.Models.Regression.Fitting;

namespace Production
{
    public class ProductionResult
    {
        protected string algorithmName;
        protected int id;
        protected MyData[] MD;

        public string GetAlgorithmName() { return algorithmName; }
        public int GetID() { return id; }

        public void SetAlgorithmName(string name) { algorithmName = name; }
        public void SetID(int num) { id = num; }
        public void SetData(MyData[] data) { MD = data; }
    }

    public class ProductionResultStatics : ProductionResult, Istatics
    {
        public ProductionResultStatics()
        {
            algorithmName = "Statics";
            id = 1;
        }
        public double mean { get; set; }
        //public double standardDeviation { get; set; }
        public double GetMean(int index)
        {
            int length = MD.Length;
            double sum = 0;
            for (int i = 0; i < length; i++)
            {
                sum = sum + MD[i].GetParameters()[index];
            }
            mean = sum / length;
            return mean;
        }

        public double standardDeviation { get; set; }
        public double GetStandardDeviation(int index)
        {
            GetMean(index);
            double sum = 0;
            int length = MD.Length;
            for (int i = 0; i < length; i++)
            {
                sum = sum + Math.Pow((MD[i].GetParameters()[index] - mean), 2);
            }
            standardDeviation = Math.Sqrt(sum / length);
            return standardDeviation;
        }

        public double threshold { get; set; }
        public double GetThreshold(double n)
        {
            threshold = mean - n * standardDeviation;
            return threshold;
        }
    }

    public class ProductionResultPeekValley : ProductionResultStatics, Ipeek
    {
        public ProductionResultPeekValley()
        {
            algorithmName = "Peak";
            id = 2;
            peakData = new List<PeekValleyData>();
        }
        public List<PeekValleyData> peakData { get; set; }
        public List<PeekValleyData> GetPeaksWithNumOfSamePoints(int index, int range, double percentage)
        {
            peakData = new List<PeekValleyData>();
            int numOfPoints = range / 2;
            Dictionary<double, int> MyDataDict = new Dictionary<double, int>();
            for (int i = 0; i < MD.Length; i++)
            {
                double num = MD[i].GetParameters()[index];
                if (MyDataDict.ContainsKey(num))
                {
                    MyDataDict[num]++;
                }
                else
                {
                    MyDataDict.Add(num, 1);
                }
            }
            double[] keyArr = MyDataDict.Keys.ToArray();
            for (int i = 0; i < keyArr.Length; i++)
            {
                double keyI = keyArr[i];
                int leftTimes = numOfPoints;
                int rightTimes = numOfPoints;
                int leftIndex = i - 1;
                int rightIndex = i + 1;
                bool biggerThanLeft = false;
                bool biggerThanRight = false;
                while (leftIndex >= 0 && leftTimes != 0)
                {
                    double key = keyArr[leftIndex];
                    double left = MyDataDict[key];
                    double Ivalue = MyDataDict[keyI];
                    if (left > Ivalue)
                    {
                        break;
                    }
                    else
                    {
                        double ratio = (Ivalue - left) / Ivalue;
                        if (ratio >= percentage)
                        {
                            biggerThanLeft = true;
                            break;
                        }
                        leftIndex--;
                        leftTimes--;
                    }
                }
                while (rightIndex < keyArr.Length && rightTimes != 0)
                {
                    double key = keyArr[rightIndex];
                    double right = MyDataDict[key];
                    double Ivalue = MyDataDict[keyI];
                    if (right > Ivalue)
                    {
                        break;
                    }
                    else
                    {
                        double ratio = (Ivalue - right) / Ivalue;
                        if (ratio >= percentage)
                        {
                            biggerThanRight = true;
                            break;
                        }
                        rightIndex++;
                        rightTimes--;
                    }
                }
                if (biggerThanRight == true && biggerThanLeft == true)
                {
                    PeekValleyData pd = new PeekValleyData();
                    pd.value = keyI;
                    pd.times = MyDataDict[keyI];
                    peakData.Add(pd);
                }
            }
            return peakData;
        }
        public List<PeekValleyData> GetPeaksWithXY(int Yindex, int Xindex, int range, double percentage)
        {
            peakData = new List<PeekValleyData>();
            int numOfPoints = range / 2;
            for (int i = 0; i < MD.Length; i++)
            {
                int leftTimes = numOfPoints;
                int rightTimes = numOfPoints;
                int leftIndex = i - 1;
                int rightIndex = i + 1;
                bool biggerThanLeft = false;
                bool biggerThanRight = false;
                while (leftIndex >= 0 && leftTimes != 0)
                {
                    double left = MD[leftIndex].GetParameters()[Yindex];
                    double Ivalue = MD[i].GetParameters()[Yindex];
                    if (left > Ivalue)
                    {
                        break;
                    }
                    else
                    {
                        double ratio = (Ivalue - left) / Ivalue;
                        if (ratio >= percentage)
                        {
                            biggerThanLeft = true;
                            break;
                        }
                        leftIndex--;
                        leftTimes--;
                    }
                }
                while (rightIndex < MD.Length && rightTimes != 0)
                {
                    double right = MD[rightIndex].GetParameters()[Yindex];
                    double Ivalue = MD[i].GetParameters()[Yindex];
                    if (right > Ivalue)
                    {
                        break;
                    }
                    else
                    {
                        double ratio = (Ivalue - right) / Ivalue;
                        if (ratio >= percentage)
                        {
                            biggerThanRight = true;
                            break;
                        }
                        rightIndex++;
                        rightTimes--;
                    }
                }
                if (biggerThanRight == true && biggerThanLeft == true)
                {
                    PeekValleyData pd = new PeekValleyData();
                    if (Yindex == -1)
                    {
                        pd.y = MD[i].GetDate();
                    }
                    else
                    {
                        pd.y = MD[i].GetParameters()[Yindex];
                    }
                    if (Xindex == -1)
                    {
                        pd.x = MD[i].GetDate();
                    }
                    else
                    {
                        pd.x = MD[i].GetParameters()[Xindex];
                    }

                    peakData.Add(pd);
                }
            }
            return peakData;
        }
    }

    public class ProductionResultPolyFit : ProductionResultPeekValley, Ipolyfit
    {
        public double[,] matrixX;
        public double[,] matrixY;
        public int order;

        public ProductionResultPolyFit()
        {
            algorithmName = "Polynomial Fit";
            id = 3;
        }

        public Dictionary<double, int> CalculateTimesEachX(int index)
        {
            Dictionary<double, int> MyDataDict = new Dictionary<double, int>();
            for (int i = 0; i < MD.Length; i++)
            {
                double num = MD[i].GetParameters()[index];
                if (MyDataDict.ContainsKey(num))
                {
                    MyDataDict[num]++;
                }
                else
                {
                    MyDataDict.Add(num, 1);
                }
            }
            return MyDataDict;
        }


        public double[,] GetPolyFit(double[,] x, double[] y, int order)
        {
            matrixX = new double[x.GetLength(0), order + 1];
            matrixY = new double[y.Count(), 1];


            for (int i = 0; i < x.GetLength(0); i++)
            {
                for (int j = 0; j < order + 1; j++)
                {
                    if (j == 0)
                    {
                        matrixX[i, 0] = 1;
                    }
                    else
                    {
                        matrixX[i, j] = x[i, j - 1];
                    }
                }
            }

            for (int i = 0; i < y.Count(); i++)
            {
                matrixY[i, 0] = y[i];
            }


            Matrix<double> a = DenseMatrix.OfArray(matrixX);
            Matrix<double> b = DenseMatrix.OfArray(matrixY);
            Matrix<double> r1, r2, r3, t;

            t = a.Transpose();
            r1 = t.Multiply(a);
            r1 = r1.Inverse();

            r2 = t.Multiply(b);
            r3 = r1.Multiply(r2);


            return r3.ToArray();
        }
    }

    public class ProductionResultNormalDistribution : ProductionResultPolyFit, INormalDistributionFit
    {

        public ProductionResultNormalDistribution()
        {
            algorithmName = "Normal Distribution Fit";
            id = 4;
        }


        public NormalDistributionInfo GetNormalDistributionFitWithNumOfSamePoints(int index)
        {
            NormalDistributionInfo Info = new NormalDistributionInfo();
            int length = MD.Length;
            double[] arr = new double[length];
            for (int i = 0; i < length; i++)
            {
                arr[i] = MD[i].GetParameters()[index];
            }
            NormalDistribution ND = new NormalDistribution();
            ND.Fit(arr);
            Info.mean = ND.Mean;
            Info.SD = ND.StandardDeviation;
            return Info;
        }
    }

    public class ProductionLogisticRegression : ProductionResultNormalDistribution, ILogisticRegression{
        public ProductionLogisticRegression()
        {
            algorithmName = "LogisticRegression";
            id = 5;
        }

        public double[,] GetPolyFitWithDict(Dictionary<double, int> dict,int power)
        {
            double[,] x = new double[dict.Keys.Count(), power];
            double[] keys = dict.Keys.ToArray();
            for (int i = 0; i < dict.Keys.Count(); i++)
            {
                for (int j = 0; j < power; j++)
                {
                    x[i, j] = Math.Pow(keys[i], j + 1);
                }
            }
            double[] y = new double[keys.Length];
            for (int i = 0; i < keys.Length; i++)
            {
                y[i] = dict[keys[i]];
            }
            return GetPolyFit(x, y, power);
        }

        public LogisticRegression GetLogisticRegressionParams(int index, double percentage)
        {
            LogisticInfo LI = new LogisticInfo();
            LI.LogisticParams = new double[2];
            int length = MD.Length;
            int samplesize = (int)(length * percentage);
            
            double [][] inputArr = new double[samplesize * 2][];
            for (int i = 0; i < samplesize*2; i++)
            {
                inputArr[i] = new double[2];
            }
            double[] outputArr = new double[samplesize * 2];
            for (int i = 0; i < samplesize; i++)
            {
                inputArr[i][0] = MD[i].GetParameters()[index];
                inputArr[i][1] = 0;
                outputArr[i] = 0;
            }
            int j = length - samplesize;
            for (int i = samplesize; i < samplesize*2; i++)
            {
                inputArr[i][0] = MD[j].GetParameters()[index];
                inputArr[i][1] = 0;
                outputArr[i] = 1;
                j++;
            }
            
            LogisticRegression LR = new LogisticRegression();
            LR.NumberOfInputs=1;
            var learner = new IterativeReweightedLeastSquares<LogisticRegression>()
            {
                Tolerance = 1e-4,  // Let's set some convergence parameters
                Iterations = 100,  // maximum number of iterations to perform
                Regularization = 0
            };
            LogisticRegression regression = learner.Learn(inputArr, outputArr);

            LI.LogisticParams[0] = -(regression.Intercept+1);
            LI.LogisticParams[1] = regression.GetOddsRatio(1)-1;
            return regression;
        }
    }

    public class ProductionTwoPeaks : ProductionLogisticRegression
    {
        public ProductionTwoPeaks()
        {
            algorithmName = "TwoPeaks";
            id = 6;
        }
        public NormalDistributionInfo GetPeakNormalDistribution(double peak, int index, int numOfPoints)
        {
            NormalDistributionInfo Info = new NormalDistributionInfo();
            List<double> ls = new List<double>();
            Dictionary<double,int> dict= CalculateTimesEachX(index);
            double[] keyArr = dict.Keys.ToArray();
            int i = 0;
            for (i = 0; i < keyArr.Length;i++ )
            {
                if (keyArr[i] == peak)
                {
                    break;
                }
            }
            for (int j = i - numOfPoints; j < i; j++)
            {
                if (j < 0)
                {
                    j = 0;
                }
                int value = dict[keyArr[j]];
                for (int k = 0; k < value; k++)
                {
                    ls.Add(keyArr[j]);
                }
            }

            for (int j = i ; j < i+numOfPoints+1; j++)
            {
                if (j >= keyArr.Length)
                {
                    break;
                }
                int value = dict[keyArr[j]];
                for (int k = 0; k < value; k++)
                {
                    ls.Add(keyArr[j]);
                }
            }
            
            NormalDistribution ND = new NormalDistribution();
            ND.Fit(ls.ToArray());
            Info.mean = ND.Mean;
            Info.SD = ND.StandardDeviation;
            return Info;

        }


        
    }
}
