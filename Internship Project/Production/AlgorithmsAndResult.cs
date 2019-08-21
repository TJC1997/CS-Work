using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Production.Properties;
using Accord.Statistics.Models.Regression;
using Accord.Statistics.Models.Regression.Fitting;

namespace Production
{
    public partial class AlgorithmsAndResult : UserControl
    {
        private ProductionFacade PF;
        private Dictionary<double, int> dataDict;
        private double[,] paramsResult;
        private points[] dataPoints;
        private List<PeekValleyData> peaksData;
        private NormalDistributionInfo NDinfo;
        private TwoDictInfo TDinfo;


        public void clear()
        {
            dataDict = null;
            paramsResult = null;
            dataPoints = null;
            peaksData = null;
            NDinfo.mean = -1;
            NDinfo.SD = -1;
            TDinfo.peak1value = -1;
            TDinfo.peak2value = -1;
        }
        private void addOptions()
        {
            XaxiscomboBox.Items.Clear();
            YaxiscomboBox.Items.Clear();
            comboBox2.Items.Clear();
            if (PF.GetData().Length == 0)
            {
                return;
            }
            YaxiscomboBox.Items.Clear();
            XaxiscomboBox.Items.Clear();
            //YaxiscomboBox.Items.Add("TimeSpan");
            XaxiscomboBox.Items.Add("TimeSpan");
            int length = PF.GetData()[0].GetNumOfParams();
            for (int i = 0; i < length; i++)
            {
                YaxiscomboBox.Items.Add("Param " + i);
                YaxiscomboBox.Items.Add("# of Param " + i);
                XaxiscomboBox.Items.Add("Param " + i);
                comboBox2.Items.Add("Param " + i);
            }
        }

        private void sortData()
        {
            if (YaxiscomboBox.Text.Contains("#"))
            {
                string text = YaxiscomboBox.Text.Substring(10).Trim();
                int num = Int32.Parse(text);
                PF.SortData(num);
            }
            else if (XaxiscomboBox.Text.Contains("Param"))
            {
                string text = XaxiscomboBox.Text.Substring(5).Trim();
                int num = Int32.Parse(text);
                //MessageBox.Show(num.ToString());
                PF.SortData(num);
            }
            else if (XaxiscomboBox.Text.Contains("TimeSpan"))
            {
                PF.SortData(-1);
            }
        }



        public void SetFacade(ProductionFacade PF)
        {
            this.PF = PF;
            addOptions();
        }

        public AlgorithmsAndResult()
        {
            InitializeComponent();
            TDinfo = new TwoDictInfo();
            TDinfo.peak1value = -1;
            TDinfo.peak2value = -1;

            comboBox1.Items.Add("Statics");
            comboBox1.Items.Add("Peak");
            comboBox1.Items.Add("Polynomial Fit");
            comboBox1.Items.Add("Normal Distribution Fit");
            comboBox1.Items.Add("Logistic Regression");
            comboBox1.Items.Add("Two Peaks");
            comboBox1.Text = (string)Settings.Default["AlgorName"];
            textBox1.Text = (string)Settings.Default["Parameter"];
            numBox.Text = (string)Settings.Default["NumOfPoints"];
            rangeBox.Text = (string)Settings.Default["Range"];
            powerBox.Text = (string)Settings.Default["Power"];
            xvalueBox.Text = (string)Settings.Default["Xvalue"];
        }

        public string GetCurrentAlgorithm()
        {
            return comboBox1.Text;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            label3.Text = comboBox1.Text;
            if (comboBox1.Text == "Statics")
            {
                label4.Hide();
                label5.Hide();
                XaxiscomboBox.Hide();
                YaxiscomboBox.Hide();
                textBox1.Show();
                NumberLabel.Show();
                numBox.Hide();
                rangeBox.Hide();
                label6.Hide();
                label7.Hide();
                label8.Hide();
                label9.Hide();
                label10.Hide();
                xvalueBox.Hide();
                powerBox.Hide();
                comboBox2.Hide();
                label11.Hide();
            }
            else if (comboBox1.Text == "Peak")
            {
                label4.Show();
                label5.Show();
                XaxiscomboBox.Show();
                YaxiscomboBox.Show();
                textBox1.Hide();
                NumberLabel.Hide();
                numBox.Show();
                rangeBox.Show();
                label7.Show();
                label8.Show();
                label9.Hide();
                label10.Hide();
                xvalueBox.Hide();
                powerBox.Hide();
                comboBox2.Hide();
                label11.Hide();
            }
            else if (comboBox1.Text == "Two Peaks")
            {
                label4.Show();
                label5.Show();
                XaxiscomboBox.Show();
                YaxiscomboBox.Show();
                textBox1.Hide();
                NumberLabel.Hide();
                numBox.Show();
                rangeBox.Show();
                label7.Show();
                label8.Show();
                label9.Hide();
                label10.Hide();
                xvalueBox.Hide();
                powerBox.Hide();
                comboBox2.Hide();
                label11.Hide();
            }
            else if (comboBox1.Text == "Polynomial Fit")
            {
                label4.Show();
                label5.Show();
                XaxiscomboBox.Show();
                YaxiscomboBox.Show();
                textBox1.Hide();
                NumberLabel.Hide();
                numBox.Hide();
                rangeBox.Hide();
                label7.Hide();
                label8.Hide();
                label9.Show();
                label10.Show();
                xvalueBox.Show();
                powerBox.Show();
                comboBox2.Hide();
                label11.Hide();
            }
            else if (comboBox1.Text == "Normal Distribution Fit")
            {
                label4.Show();
                label5.Show();
                XaxiscomboBox.Show();
                YaxiscomboBox.Show();
                textBox1.Hide();
                NumberLabel.Hide();
                numBox.Hide();
                rangeBox.Hide();
                label7.Hide();
                label8.Hide();
                label9.Hide();
                label10.Show();
                xvalueBox.Show();
                powerBox.Hide();
                comboBox2.Hide();
                label11.Hide();
            }
            else if (comboBox1.Text == "Logistic Regression")
            {
                label4.Show();
                label5.Show();
                XaxiscomboBox.Show();
                YaxiscomboBox.Show();
                textBox1.Hide();
                NumberLabel.Hide();
                numBox.Hide();
                rangeBox.Show();
                label6.Hide();
                label7.Hide();
                label8.Show();
                label9.Show();
                label10.Show();
                xvalueBox.Show();
                powerBox.Show();
                comboBox2.Show();
                label11.Show();
                label4.Hide();
                label5.Hide();
                XaxiscomboBox.Hide();
                YaxiscomboBox.Hide();
            }

            if (comboBox1.Text == "Peak" || comboBox1.Text == "Two Peaks" || comboBox1.Text == "Polynomial Fit" || comboBox1.Text == "Normal Distribution Fit")
            {
                if (YaxiscomboBox.Text.Contains("#"))
                {
                    XaxiscomboBox.Hide();
                    label6.Show();
                }
                else
                {
                    label6.Hide();
                    XaxiscomboBox.Show();
                }
            }
            peak1Box.Hide();
            peak2Box.Hide();
            label13.Hide();
            label12.Hide();
        }

        private void GetResultButton_Click(object sender, EventArgs e)
        {
            Settings.Default["AlgorName"] = label3.Text;
            ResultBox.Items.Clear();
            if (label3.Text == "Statics")
            {
                if (!(PF is Istatics))
                {
                    MessageBox.Show("Production Facade doesn't have this interface yet");
                    return;
                }
                Settings.Default["Parameter"] = textBox1.Text;
                int numOfParmas = PF.GetData()[0].GetNumOfParams();
                double mean, sd;
                for (int i = 0; i < numOfParmas; i++)
                {
                    mean = PF.GetMean(i);
                    ResultBox.Items.Add("Mean of param " + i + ": " + mean);
                    sd = PF.GetStandardDeviation(i);
                    ResultBox.Items.Add("StandardDeviation of param " + i + ": " + sd);
                    if (textBox1.Text != "")
                    {
                        double number = Double.Parse(textBox1.Text);
                        double Threshold = PF.GetThreshold(number);
                        ResultBox.Items.Add("Threshold of param " + i + ": " + Threshold);
                        ResultBox.Items.Add("");
                    }
                }
            }
            else if (label3.Text == "Peak")
            {
                if (!(PF is Ipeek))
                {
                    MessageBox.Show("Production Facade doesn't have this interface yet");
                    return;
                }
                if (XaxiscomboBox.Text == "" && YaxiscomboBox.Text == "")
                {
                    return;
                }
                sortData();
                Settings.Default["NumOfPoints"] = numBox.Text;
                Settings.Default["Range"] = rangeBox.Text;
                if (YaxiscomboBox.Text.Contains("#"))
                {
                    string text = YaxiscomboBox.Text.Substring(10).Trim();
                    int num = Int32.Parse(text);
                    int numOfpoints = 3;
                    double percentage = 0.2;
                    if (numBox.Text != "")
                    {
                        numOfpoints = Int32.Parse(numBox.Text);
                    }
                    if (rangeBox.Text != "")
                    {
                        percentage = double.Parse(rangeBox.Text);
                    }
                    dataDict = PF.CalculateTimesEachX(num);
                    List<PeekValleyData> peaks = PF.GetPeaksWithNumOfSamePoints(num, numOfpoints, percentage);
                    peaksData = peaks;
                    /*
                    for (int i = 0; i < PF.GetData().Length; i++)
                    {
                        ResultBox.Items.Add(PF.GetData()[i].WriteToLine());
                    }*/
                    if (peaksData.Count() == 0)
                    {
                        ResultBox.Items.Add("No Peak found yet.");
                    }
                    foreach (var item in peaks)
                    {
                        ResultBox.Items.Add("Peak Value: " + item.value + "   Times: " + item.times);
                    }
                }
                else if (YaxiscomboBox.Text != "")
                {
                    string text = YaxiscomboBox.Text.Substring(5).Trim();

                    int Yindex = Int32.Parse(text);
                    // MessageBox.Show(Yindex.ToString());
                    int numOfpoints = 3;
                    double percentage = 0.2;
                    if (numBox.Text != "")
                    {
                        numOfpoints = Int32.Parse(numBox.Text);
                    }
                    if (rangeBox.Text != "")
                    {
                        percentage = double.Parse(rangeBox.Text);
                    }
                    text = XaxiscomboBox.Text.Substring(5).Trim();
                    int Xindex;
                    if (XaxiscomboBox.Text.Contains("TimeSpan"))
                    {
                        Xindex = -1;
                    }
                    else
                    {
                        Xindex = Int32.Parse(text);
                    }
                    MyData[] MD = PF.GetData();
                    dataPoints = new points[MD.Count()];
                    for (int i = 0; i < MD.Count(); i++)
                    {
                        dataPoints[i].x = MD[i].GetParameters()[Xindex];
                        dataPoints[i].y = MD[i].GetParameters()[Yindex];
                    }
                    List<PeekValleyData> peaks = PF.GetPeaksWithXY(Yindex, Xindex, numOfpoints, percentage);
                    peaksData = peaks;
                    /*
                    for (int i = 0; i < PF.GetData().Length; i++)
                    {
                        ResultBox.Items.Add(PF.GetData()[i].WriteToLine());
                    }
                     * */
                    foreach (var item in peaks)
                    {
                        ResultBox.Items.Add("X: " + item.x + "   Y: " + item.y);
                    }
                }
            }
            else if (label3.Text == "Polynomial Fit")
            {
                if (!(PF is Ipolyfit))
                {
                    MessageBox.Show("Production Facade doesn't have this interface yet");
                    return;
                }
                if (XaxiscomboBox.Text == "" && YaxiscomboBox.Text == "")
                {
                    return;
                }
                sortData();
                int power = 1;
                if (powerBox.Text != "")
                {
                    power = Int32.Parse(powerBox.Text);
                }
                if (YaxiscomboBox.Text.Contains("#"))
                {
                    string text = YaxiscomboBox.Text.Substring(10).Trim();
                    int num = Int32.Parse(text);
                    Dictionary<double, int> dict = PF.CalculateTimesEachX(num);
                    dataDict = dict;
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
                    double[,] result = PF.GetPolyFit(x, y, power);
                    paramsResult = result;
                    string r = "y=";
                    r = r + result[0, 0].ToString("#.000");
                    for (int i = 1; i <= power; i++)
                    {
                        r = r + "+ " + result[i, 0].ToString("#.000") + "x^" + i.ToString();
                    }
                    ResultBox.Items.Add(r);
                }
                else if (YaxiscomboBox.Text != "")
                {
                    string text = YaxiscomboBox.Text.Substring(5).Trim();
                    int Yindex = Int32.Parse(text);
                    int Xindex;
                    if (XaxiscomboBox.Text.Contains("TimeSpan"))
                    {
                        MessageBox.Show("We have not support Timespan in this algorithm yet.");
                        return;
                    }
                    else
                    {
                        text = XaxiscomboBox.Text.Substring(5).Trim();
                        Xindex = Int32.Parse(text);
                    }
                    MyData[] MD = PF.GetData();
                    dataPoints = new points[MD.Count()];
                    double[,] x = new double[MD.Count(), power];
                    for (int i = 0; i < MD.Count(); i++)
                    {
                        dataPoints[i].x = MD[i].GetParameters()[Xindex];
                        for (int j = 0; j < power; j++)
                        {
                            x[i, j] = Math.Pow(MD[i].GetParameters()[Xindex], j + 1);
                        }
                    }
                    double[] y = new double[MD.Count()];
                    for (int i = 0; i < y.Length; i++)
                    {
                        y[i] = MD[i].GetParameters()[Yindex];
                        dataPoints[i].y = y[i];
                    }
                    double[,] result = PF.GetPolyFit(x, y, power);
                    paramsResult = result;
                    string r = "y=";
                    r = r + result[0, 0].ToString("#.000");
                    for (int i = 1; i <= power; i++)
                    {
                        r = r + "+ " + result[i, 0].ToString("#.000") + "x^" + i.ToString();
                    }
                    ResultBox.Items.Add(r);
                }
                if (xvalueBox.Text != "")
                {
                    double x = Convert.ToDouble(xvalueBox.Text);
                    double y = 0;
                    for (int j = 0; j < paramsResult.GetLength(0); j++)
                    {
                        y = y + Math.Pow(x, j) * paramsResult[j, 0];
                    }
                    ResultBox.Items.Add("X-value: " + x.ToString("#.000") + " Y-value: " + y.ToString("#.000"));
                    Settings.Default["Xvalue"] = xvalueBox.Text;
                }
                Settings.Default["Power"] = powerBox.Text;
            }
            else if (label3.Text == "Normal Distribution Fit")
            {
                if (!(PF is INormalDistributionFit))
                {
                    MessageBox.Show("Production Facade doesn't have this interface yet");
                    return;
                }
                if (XaxiscomboBox.Text == "" && YaxiscomboBox.Text == "")
                {
                    return;
                }
                sortData();
                /*
                for (int i = 0; i < PF.GetData().Length; i++)
                {
                    ResultBox.Items.Add(PF.GetData()[i].WriteToLine());
                }*/
                if (YaxiscomboBox.Text.Contains("#"))
                {
                    string text = YaxiscomboBox.Text.Substring(10).Trim();
                    int num = Int32.Parse(text);
                    dataDict = PF.CalculateTimesEachX(num);
                    NormalDistributionInfo ndi = PF.GetNormalDistributionFitWithNumOfSamePoints(num);
                    NDinfo = ndi;
                    ResultBox.Items.Add("Mean: " + ndi.mean.ToString() + " SD: " + ndi.SD.ToString());
                }
                else
                {
                    if (XaxiscomboBox.Text == "" || YaxiscomboBox.Text == "")
                    {
                        return;
                    }
                    string text = YaxiscomboBox.Text.Substring(5).Trim();
                    int Yindex = Int32.Parse(text);
                    int Xindex;
                    if (XaxiscomboBox.Text.Contains("TimeSpan"))
                    {
                        MessageBox.Show("We have not support Timespan in this algorithm yet.");
                        return;
                    }
                    else
                    {
                        text = XaxiscomboBox.Text.Substring(5).Trim();
                        Xindex = Int32.Parse(text);
                    }
                    MyData[] MD = PF.GetData();
                    dataPoints = new points[MD.Count()];
                    for (int i = 0; i < MD.Count(); i++)
                    {
                        dataPoints[i].x = MD[i].GetParameters()[Xindex];
                        dataPoints[i].y = MD[i].GetParameters()[Yindex];
                    }
                    int num = Int32.Parse(text);
                    dataDict = PF.CalculateTimesEachX(num);
                    NormalDistributionInfo ndi = PF.GetNormalDistributionFitWithNumOfSamePoints(num);
                    NDinfo = ndi;
                    ResultBox.Items.Add("Mean: " + ndi.mean.ToString() + " SD: " + ndi.SD.ToString());
                }
                if (xvalueBox.Text != "")
                {
                    double x = Convert.ToDouble(xvalueBox.Text);
                    double y = 0;
                    y = (1 / (NDinfo.SD * Math.Sqrt(2 * Math.PI))) * Math.Exp(-Math.Pow((x - NDinfo.mean), 2) / (2 * Math.Pow(NDinfo.SD, 2)));
                    int numberOfdata = 0;
                    foreach (var item in dataDict)
                    {
                        numberOfdata = numberOfdata + item.Value;
                    }
                    y = y * numberOfdata;
                    ResultBox.Items.Add("X-value: " + x.ToString("#.000") + " Y-value: " + y.ToString("#.000"));
                    Settings.Default["Xvalue"] = xvalueBox.Text;
                }
            }
            else if (label3.Text == "Logistic Regression")
            {
                if (!(PF is ILogisticRegression))
                {
                    MessageBox.Show("Production Facade doesn't have this interface yet");
                    return;
                }
                if (comboBox2.Text != "")
                {
                    string text = comboBox2.Text.Substring(5).Trim();
                    int index = Int32.Parse(text);
                    dataDict = PF.CalculateTimesEachX(index);
                    double percentage = 0.1;
                    PF.SortData(index);
                    if (rangeBox.Text != "")
                    {
                        percentage = double.Parse(rangeBox.Text);
                    }
                    LogisticRegression LR = PF.GetLogisticRegressionParams(index, percentage);
                    LogisticInfo LI = new LogisticInfo();
                    LI.LogisticParams = new double[2];
                    LI.LogisticParams[0] = LR.Intercept;
                    LI.LogisticParams[1] = LR.GetOddsRatio(1) - 1;
                    ResultBox.Items.Add("Param0: " + LI.LogisticParams[0] + " Parma1: " + LI.LogisticParams[1]);
                    if (xvalueBox.Text != "")
                    {
                        double x = Convert.ToDouble(xvalueBox.Text);
                        double[] valueArr = new double[] { x, 0 };
                        ResultBox.Items.Add("Value: " + x + " Probability: " + LR.Probability(valueArr) + " Conclusion:" + LR.Decide(valueArr));
                    }
                    MyData[] MD = PF.GetData();
                    double threshold = -1;
                    /*
                    for (int i = 0; i < MD.Length; i++)
                    {
                        double value = MD[i].GetParameters()[index];
                        double[] valueArr = new double[] { value, 0 };
                        ResultBox.Items.Add("Value: " + value + " Probability: " + LR.Probability(valueArr) + " Conclusion:" + LR.Decide(valueArr));
                    }*/
                    Dictionary<double, int> lowerDict = new Dictionary<double, int>();
                    Dictionary<double, int> higherDict = new Dictionary<double, int>();
                    for (int i = 0; i < MD.Length; i++)
                    {
                        double value = MD[i].GetParameters()[index];
                        double[] valueArr = new double[] { value, 0 };
                        if (threshold == -1 && LR.Decide(valueArr) == true)
                        {
                            threshold = value;
                        }
                        if (threshold == -1)
                        {
                            if (lowerDict.ContainsKey(value))
                            {
                                lowerDict[value]++;
                            }
                            else
                            {
                                lowerDict.Add(value, 1);
                            }
                        }
                        else
                        {
                            if (higherDict.ContainsKey(value))
                            {
                                higherDict[value]++;
                            }
                            else
                            {
                                higherDict.Add(value, 1);
                            }
                        }
                    }
                    ResultBox.Items.Add("Threshold: " + threshold);
                }
            }
            else if (label3.Text == "Two Peaks")
            {
                if (!(PF is Ipeek))
                {
                    MessageBox.Show("Production Facade doesn't have this interface yet");
                    return;
                }
                if (peak1Box.Text != "" && peak2Box.Text != "")
                {
                    string text = YaxiscomboBox.Text.Substring(10).Trim();
                    int index = Int32.Parse(text);
                    double peak1 = Convert.ToDouble(peak1Box.Text);
                    double peak2 = Convert.ToDouble(peak2Box.Text);
                    int numOfpoints = 5;
                    if (numBox.Text != "")
                    {
                        numOfpoints = Int32.Parse(numBox.Text);
                    }
                    NormalDistributionInfo peak1Info = PF.GetPeakNormalDistribution(peak1, index, numOfpoints);
                    ResultBox.Items.Add("Mean: " + peak1Info.mean.ToString("#.000") + " SD: " + peak1Info.SD.ToString("#.000"));

                    NormalDistributionInfo peak2Info = PF.GetPeakNormalDistribution(peak2, index, numOfpoints);
                    ResultBox.Items.Add("Mean: " + peak2Info.mean.ToString("#.000") + " SD: " + peak2Info.SD.ToString("#.000"));
                 
                    if (xvalueBox.Text != "")
                    {
                        double x = Convert.ToDouble(xvalueBox.Text);
                        double end = 0;
                        double y = (1 / (peak1Info.SD * Math.Sqrt(2 * Math.PI))) * Math.Exp(-Math.Pow((x - peak1Info.mean), 2) / (2 * Math.Pow(peak1Info.SD, 2)));
                        if (y < 0.01)
                        {
                            double x1 = x - 1;
                            double y1 = (1 / (peak1Info.SD * Math.Sqrt(2 * Math.PI))) * Math.Exp(-Math.Pow((x1 - peak1Info.mean), 2) / (2 * Math.Pow(peak1Info.SD, 2)));
                            if (y1 < y)
                            {
                                end = x1;
                            }
                            else
                            {
                                end = x + 1;
                            }
                        }
                        else
                        {
                            double x1 = x - 1;
                            double y1 = (1 / (peak1Info.SD * Math.Sqrt(2 * Math.PI))) * Math.Exp(-Math.Pow((x1 - peak1Info.mean), 2) / (2 * Math.Pow(peak1Info.SD, 2)));
                            if (y1 < y)
                            {
                                end = x1;
                                while (y1 > 0.01)
                                {
                                    end--;
                                    y1 = (1 / (peak1Info.SD * Math.Sqrt(2 * Math.PI))) * Math.Exp(-Math.Pow((end - peak1Info.mean), 2) / (2 * Math.Pow(peak1Info.SD, 2)));
                                }
                            }
                            else
                            {
                                end = x + 1;
                                y1 = (1 / (peak1Info.SD * Math.Sqrt(2 * Math.PI))) * Math.Exp(-Math.Pow((end - peak1Info.mean), 2) / (2 * Math.Pow(peak1Info.SD, 2)));
                                while (y1 > 0.01)
                                {
                                    end++;
                                    y1 = (1 / (peak1Info.SD * Math.Sqrt(2 * Math.PI))) * Math.Exp(-Math.Pow((end - peak1Info.mean), 2) / (2 * Math.Pow(peak1Info.SD, 2)));
                                }
                            }
                        }
                        Func<double, double> f1 = (a) => (1 / (peak1Info.SD * Math.Sqrt(2 * Math.PI))) * Math.Exp(-Math.Pow((a - peak1Info.mean), 2) / (2 * Math.Pow(peak1Info.SD, 2)));
                        double result1 = MathNet.Numerics.Integration.NewtonCotesTrapeziumRule.IntegrateTwoPoint(f1, x, end);
                        if (x <= peak1)
                        {
                            result1 = 1 - Math.Abs(result1);
                            if (result1 > 1)
                            {
                                result1 = 1;
                            }
                        }
                        ResultBox.Items.Add("Probablity of keeping bad chips: " + Math.Abs(result1).ToString("#.000"));
                        double end1 = 0;
                        y = (1 / (peak2Info.SD * Math.Sqrt(2 * Math.PI))) * Math.Exp(-Math.Pow((x - peak2Info.mean), 2) / (2 * Math.Pow(peak2Info.SD, 2)));
                        if (y < 0.01)
                        {
                            double x1 = x - 1;
                            double y1 = (1 / (peak2Info.SD * Math.Sqrt(2 * Math.PI))) * Math.Exp(-Math.Pow((x1 - peak2Info.mean), 2) / (2 * Math.Pow(peak2Info.SD, 2)));
                            if (y1 < y)
                            {
                                end1 = x1;
                            }
                            else
                            {
                                end1 = x + 1;
                            }
                        }
                        else
                        {
                            double x1 = x - 1;
                            double y1 = (1 / (peak2Info.SD * Math.Sqrt(2 * Math.PI))) * Math.Exp(-Math.Pow((x1 - peak2Info.mean), 2) / (2 * Math.Pow(peak2Info.SD, 2)));
                            if (y1 < y)
                            {
                                end1 = x1;
                                while (y1 > 0.01)
                                {
                                    end1--;
                                    y1 = (1 / (peak2Info.SD * Math.Sqrt(2 * Math.PI))) * Math.Exp(-Math.Pow((end1 - peak2Info.mean), 2) / (2 * Math.Pow(peak2Info.SD, 2)));
                                }
                            }
                            else
                            {
                                end1 = x + 1;
                                y1 = (1 / (peak2Info.SD * Math.Sqrt(2 * Math.PI))) * Math.Exp(-Math.Pow((end1 - peak2Info.mean), 2) / (2 * Math.Pow(peak2Info.SD, 2)));
                                while (y1 > 0.01)
                                {
                                    end1++;
                                    y1 = (1 / (peak2Info.SD * Math.Sqrt(2 * Math.PI))) * Math.Exp(-Math.Pow((end1 - peak2Info.mean), 2) / (2 * Math.Pow(peak2Info.SD, 2)));
                                }
                            }
                        }
                        Func<double, double> f2 = (a) => (1 / (peak2Info.SD * Math.Sqrt(2 * Math.PI))) * Math.Exp(-Math.Pow((a - peak2Info.mean), 2) / (2 * Math.Pow(peak2Info.SD, 2)));
                        double result2 = MathNet.Numerics.Integration.NewtonCotesTrapeziumRule.IntegrateTwoPoint(f2, x, end1);
                        if (x >= peak2)
                        {
                            result2 = 1 - Math.Abs(result2);
                            if (result2 > 1)
                            {
                                result2 = 1;
                            }
                        }
                        ResultBox.Items.Add("probability of losing good chips: " + Math.Abs(result2).ToString("#.000"));
                       
                    }
                    dataDict = PF.CalculateTimesEachX(index);



                    TDinfo = new TwoDictInfo();
                    TDinfo.peak1Info = peak1Info;
                    TDinfo.peak2Info = peak2Info;
                    TDinfo.peak1value = peak1;
                    TDinfo.peak2value = peak2;
                    TDinfo.peak1times = dataDict[peak1];
                    TDinfo.peak2times = dataDict[peak2];
                    TDinfo.last = dataDict.Keys.ToList().Last();
                    //peak1Box.Text = "";
                   // peak2Box.Text = "";
                }
                else
                {
                    if (XaxiscomboBox.Text == "" && YaxiscomboBox.Text == "")
                    {
                        return;
                    }
                    sortData();
                    Settings.Default["NumOfPoints"] = numBox.Text;
                    Settings.Default["Range"] = rangeBox.Text;
                    if (YaxiscomboBox.Text.Contains("#"))
                    {
                        string text = YaxiscomboBox.Text.Substring(10).Trim();
                        int num = Int32.Parse(text);
                        int numOfpoints = 3;
                        double percentage = 0.2;
                        if (numBox.Text != "")
                        {
                            numOfpoints = Int32.Parse(numBox.Text);
                        }
                        if (rangeBox.Text != "")
                        {
                            percentage = double.Parse(rangeBox.Text);
                        }
                        dataDict = PF.CalculateTimesEachX(num);
                        List<PeekValleyData> peaks = PF.GetPeaksWithNumOfSamePoints(num, numOfpoints, percentage);
                        peaksData = peaks;
                        /*
                        for (int i = 0; i < PF.GetData().Length; i++)
                        {
                            ResultBox.Items.Add(PF.GetData()[i].WriteToLine());
                        }*/
                        if (peaksData.Count() == 0)
                        {
                            ResultBox.Items.Add("No Peak found yet.");
                        }
                        foreach (var item in peaks)
                        {
                            ResultBox.Items.Add("Peak Value: " + item.value + "   Times: " + item.times);
                        }
                    }
                    else if (YaxiscomboBox.Text != "")
                    {
                        string text = YaxiscomboBox.Text.Substring(5).Trim();

                        int Yindex = Int32.Parse(text);
                        // MessageBox.Show(Yindex.ToString());
                        int numOfpoints = 3;
                        double percentage = 0.2;
                        if (numBox.Text != "")
                        {
                            numOfpoints = Int32.Parse(numBox.Text);
                        }
                        if (rangeBox.Text != "")
                        {
                            percentage = double.Parse(rangeBox.Text);
                        }
                        text = XaxiscomboBox.Text.Substring(5).Trim();
                        int Xindex;
                        if (XaxiscomboBox.Text.Contains("TimeSpan"))
                        {
                            Xindex = -1;
                        }
                        else
                        {
                            Xindex = Int32.Parse(text);
                        }
                        MyData[] MD = PF.GetData();
                        dataPoints = new points[MD.Count()];
                        for (int i = 0; i < MD.Count(); i++)
                        {
                            dataPoints[i].x = MD[i].GetParameters()[Xindex];
                            dataPoints[i].y = MD[i].GetParameters()[Yindex];
                        }
                        List<PeekValleyData> peaks = PF.GetPeaksWithXY(Yindex, Xindex, numOfpoints, percentage);
                        peaksData = peaks;
                        /*
                        for (int i = 0; i < PF.GetData().Length; i++)
                        {
                            ResultBox.Items.Add(PF.GetData()[i].WriteToLine());
                        }
                         * */
                        foreach (var item in peaks)
                        {
                            ResultBox.Items.Add("X: " + item.x + "   Y: " + item.y);
                        }
                    }
                    if (peaksData.Count() < 2)
                    {
                        ResultBox.Items.Add("We need at least two peaks in this algorithm");
                    }
                    else
                    {
                        peak1Box.Show();
                        peak2Box.Show();
                        label13.Show();
                        label12.Show();
                        xvalueBox.Show();
                        label10.Show();
                        peak1Box.Items.Clear();
                        peak2Box.Items.Clear();
                        points[] pts = GetPeakPoints();
                        foreach (var point in pts)
                        {
                            if (!peak1Box.Items.Contains(point.x))
                            {
                                peak1Box.Items.Add(point.x);
                            }
                            if (!peak2Box.Items.Contains(point.x))
                            {
                                peak2Box.Items.Add(point.x);
                            }
                        }
                    }
                }

            }
            Settings.Default.Save();
        }

        public points[] GetPoints()
        {
            if (label3.Text == "Polynomial Fit" || label3.Text == "Peak" || label3.Text == "Two Peaks" || label3.Text == "Normal Distribution Fit")
            {
                if (YaxiscomboBox.Text.Contains("#"))
                {
                    points[] dataPoints = new points[dataDict.Count()];
                    int i = 0;
                    foreach (var item in dataDict)
                    {
                        dataPoints[i].x = item.Key;
                        dataPoints[i].y = item.Value;
                        i++;
                    }
                    return dataPoints;
                }
                else
                {
                    return dataPoints;
                }
            }
            else if (label3.Text == "Logistic Regression")
            {
                points[] dataPoints = new points[dataDict.Count()];
                int i = 0;
                foreach (var item in dataDict)
                {
                    dataPoints[i].x = item.Key;
                    dataPoints[i].y = item.Value;
                    i++;
                }
                return dataPoints;
            }
            return null;
        }

        public points[] GetPeakPoints()
        {
            if (label3.Text == "Peak" || label3.Text == "Two Peaks")
            {
                points[] peakPoints = new points[peaksData.Count()];
                if (YaxiscomboBox.Text.Contains("#"))
                {
                    int i = 0;
                    foreach (var item in peaksData)
                    {
                        peakPoints[i].x = item.value;
                        peakPoints[i].y = item.times;
                        i++;
                    }
                }
                else
                {
                    int i = 0;
                    foreach (var item in peaksData)
                    {
                        peakPoints[i].x = item.x;
                        peakPoints[i].y = item.y;
                        i++;
                    }
                }
                return peakPoints;
            }
            return null;
        }

        public double[,] GetEquationParmas()
        {
            return paramsResult;
        }


        public NormalDistributionInfo GetNDinfo()
        {
            return NDinfo;
        }

        public TwoDictInfo GetTDinfo()
        {
            return TDinfo;
        }

        private void YaxiscomboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (YaxiscomboBox.Text.Contains("#"))
            {
                XaxiscomboBox.Hide();
                label6.Show();
            }
            else
            {
                label6.Hide();
                XaxiscomboBox.Show();
            }
        }
    }
}
