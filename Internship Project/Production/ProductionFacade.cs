using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Accord.Statistics.Models.Regression;
using Accord.Statistics.Models.Regression.Fitting;

namespace Production
{
    public class ProductionFacade : Istatics, Ipeek, Ipolyfit, INormalDistributionFit,ILogisticRegression
    {
        private ProductionData PD;
        private ProductionTwoPeaks PR;

        public ProductionFacade()
        {
            PD = new ProductionData();
            PR = new ProductionTwoPeaks();
        }

        public void AddMutiData(MyData[] arr)
        {
            PD.AddMutiData(arr);
        }

        public void AddSingleData(MyData newData)
        {
            PD.AddSingleData(newData);
        }

        public void SetSize(int size)
        {
            PD.SetSize(size);
        }

        public void UnSetSize()
        {
            PD.UnSetSize();
        }

        public void SetPattern(string p)
        {
            PD.SetPattern(p);
        }

        public MyData[] GetData()
        {
            return PD.GetDataArr();
        }

        public MyData[] GetData(int start, int num)
        {
            return PD.GetDataArr(start, num);
        }

        public void SortData(int index)
        {
            PD.SortData(index);
        }

        public void ClearData()
        {
            PD.ClearData();
        }


        public double mean { get; set; }

        public double GetMean(int index)
        {
            PR.SetData(PD.GetDataArr());
            if (PR is Istatics)
            {
                mean = PR.GetMean(index);
                return mean;
            }
            return -1;
        }

        public double standardDeviation { get; set; }

        public double GetStandardDeviation(int index)
        {
            PR.SetData(PD.GetDataArr());
            if (PR is Istatics)
            {
                standardDeviation = PR.GetStandardDeviation(index);
                return standardDeviation;
            }
            return -1;
        }

        public double threshold { get; set; }
        public double GetThreshold(double n)
        {
            if (PR is Istatics)
            {
                threshold = PR.GetThreshold(n);
                return threshold;
            }
            return -1;
        }

        public List<PeekValleyData> peakData { get; set; }
        public List<PeekValleyData> GetPeaksWithNumOfSamePoints(int index, int range, double percentage)
        {
            PR.SetData(PD.GetDataArr());
            if(PR is Ipeek){
                return PR.GetPeaksWithNumOfSamePoints(index, range, percentage);
            }
            return null;
        }

        public List<PeekValleyData> GetPeaksWithXY(int Yindex, int Xindex, int range, double percentage)
        {
            PR.SetData(PD.GetDataArr());
            if (PR is Ipeek)
            {
                return PR.GetPeaksWithXY(Yindex,Xindex, range, percentage);
            }
            return null;
        }

        public Dictionary<double, int> CalculateTimesEachX(int index)
        {
            PR.SetData(PD.GetDataArr());
            if (PR is Ipolyfit)
            {
                return PR.CalculateTimesEachX(index);
            }
            return null;
        }


        public double[,] GetPolyFit(double[,] x, double[] y, int order)
        {
            PR.SetData(PD.GetDataArr());
            if (PR is Ipolyfit)
            {
                return PR.GetPolyFit(x, y, order);
            }
            return null;
        }

        public NormalDistributionInfo GetNormalDistributionFitWithNumOfSamePoints(int index)
        {
            PR.SetData(PD.GetDataArr());
            if (PR is INormalDistributionFit)
            {
                return PR.GetNormalDistributionFitWithNumOfSamePoints(index);
            }
            NormalDistributionInfo n = new NormalDistributionInfo();
            n.mean = -1;
            n.SD = -1;
            return n;
        }

        public double[,] GetPolyFitWithDict(Dictionary<double, int> dict, int power)
        {
            PR.SetData(PD.GetDataArr());
            if (PR is ILogisticRegression)
            {
                return PR.GetPolyFitWithDict(dict, power);
            }
            return null;
        }

        public LogisticRegression GetLogisticRegressionParams(int index, double percentage)
        {
            PR.SetData(PD.GetDataArr());
            if (PR is ILogisticRegression)
            {
                return PR.GetLogisticRegressionParams(index, percentage);
            }
            LogisticRegression LR = null;
            return LR;
        }

        public NormalDistributionInfo GetPeakNormalDistribution(double peak, int index, int numOfPoints)
        {
            return PR.GetPeakNormalDistribution(peak, index, numOfPoints);
        }

    }
}
