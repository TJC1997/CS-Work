using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Accord.Statistics.Models.Regression;
using Accord.Statistics.Models.Regression.Fitting;
namespace Production
{
    public struct NormalDistributionInfo
    {
        public double mean;
        public double SD;
    }

    public struct points
    {
        public dynamic x;
        public double y;
    }

    public struct PeekValleyData
    {
        public double times;
        public double value;
        //public double x;
        public dynamic x;
        public dynamic y;
        //public DateTime y;
    }

    public struct LogisticInfo
    {
        public double[] LogisticParams;
    }

    public struct TwoDictInfo
    {
        public NormalDistributionInfo peak1Info;
        public NormalDistributionInfo peak2Info;
        public double peak1value;
        public double peak2value;
        public double peak1times;
        public double peak2times;
        public double last;
    }

    public interface Istatics
    {
        double mean { get; set; }
        double standardDeviation { get; set; }
        double threshold { get; set; }

        double GetMean(int index);
        double GetStandardDeviation(int index);
        double GetThreshold(double n);
    }

    public interface Ipeek
    {
        List<PeekValleyData> peakData { get; set; }
        List<PeekValleyData> GetPeaksWithNumOfSamePoints(int index, int range, double percentage);
        List<PeekValleyData> GetPeaksWithXY(int Yindex, int Xindex, int range, double percentage);
        //void GoThoughData(int index);
    }

    public interface Ipolyfit
    {
        Dictionary<double, int> CalculateTimesEachX(int index);
        double[,] GetPolyFit(double[,] x, double[] y, int order);
    }

    public interface INormalDistributionFit
    {
        NormalDistributionInfo GetNormalDistributionFitWithNumOfSamePoints(int index);
    }

    public interface ILogisticRegression
    {
        LogisticRegression GetLogisticRegressionParams(int index, double percentage);
    }
}
