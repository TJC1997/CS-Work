using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MathNet.Numerics.Distributions;
using System.Windows.Forms.DataVisualization.Charting;

namespace Production
{
    public partial class GraphDrawer : UserControl
    {
        private AlgorithmsAndResult algorithmsAndResult;
        public GraphDrawer()
        {
            InitializeComponent();
            GraphChart.ChartAreas[0].AxisX.ScaleView.Zoomable = true;
            GraphChart.ChartAreas[0].AxisY.ScaleView.Zoomable = true;
            GraphChart.MouseWheel += chart1_MouseWheel;
            GraphChart.ChartAreas[0].AxisX.LabelStyle.Format = "0.000";
            GraphChart.ChartAreas[0].AxisY.LabelStyle.Format = "0.000";
        }

        public void setalgorithmsAndResult(ref AlgorithmsAndResult AAR)
        {
            algorithmsAndResult = AAR;
        }

        private void chart1_MouseWheel(object sender, MouseEventArgs e)
        {
            var chart = (Chart)sender;
            var xAxis = chart.ChartAreas[0].AxisX;
            var yAxis = chart.ChartAreas[0].AxisY;

            try
            {
                if (e.Delta < 0) // Scrolled down.
                {
                    xAxis.ScaleView.ZoomReset();
                    yAxis.ScaleView.ZoomReset();
                }
                else if (e.Delta > 0) // Scrolled up.
                {
                    var xMin = xAxis.ScaleView.ViewMinimum;
                    var xMax = xAxis.ScaleView.ViewMaximum;
                    var yMin = yAxis.ScaleView.ViewMinimum;
                    var yMax = yAxis.ScaleView.ViewMaximum;

                    var posXStart = xAxis.PixelPositionToValue(e.Location.X) - (xMax - xMin) / 4;
                    var posXFinish = xAxis.PixelPositionToValue(e.Location.X) + (xMax - xMin) / 4;
                    var posYStart = yAxis.PixelPositionToValue(e.Location.Y) - (yMax - yMin) / 4;
                    var posYFinish = yAxis.PixelPositionToValue(e.Location.Y) + (yMax - yMin) / 4;

                    xAxis.ScaleView.Zoom(posXStart, posXFinish);
                    yAxis.ScaleView.Zoom(posYStart, posYFinish);
                }
            }
            catch { }
        }


        private void drawButton_Click(object sender, EventArgs e)
        {
            string algorName = algorithmsAndResult.GetCurrentAlgorithm();

            GraphChart.Series["dataPoints"].Points.Clear();
            GraphChart.Series["predictGraph"].Points.Clear();
            GraphChart.Series["NormalFit"].Points.Clear();
            GraphChart.Series["Peaks"].Points.Clear();
            GraphChart.Series["NormalFitPeak1"].Points.Clear();
            GraphChart.Series["NormalFitPeak2"].Points.Clear();
            double numOfData = 0;

            points[] dataPoints = algorithmsAndResult.GetPoints();
            if (dataPoints== null) { return; }

            for (int i = 0; i < dataPoints.Length; i++)
            {
                GraphChart.Series["dataPoints"].Points.AddXY(dataPoints[i].x, dataPoints[i].y);
                numOfData = numOfData + dataPoints[i].y;
            }
            GraphChart.Series["dataPoints"].Color = Color.Red;

            double startX = dataPoints[0].x;
            double endX = dataPoints[dataPoints.Length - 1].x;
            int numOfTestPoints = dataPoints.Length * 10;
            double diff = (endX - startX) / numOfTestPoints;

            if (algorName == "Normal Distribution Fit")
            {
                NormalDistributionInfo ndi = algorithmsAndResult.GetNDinfo();
                if (ndi.SD != -1 && ndi.mean != -1)
                {
                    // double rate = (1 / (ndi.SD * Math.Sqrt(2 * Math.PI))) * Math.Exp(-Math.Pow((ndi.mean - ndi.mean), 2) / (2 * Math.Pow(ndi.SD, 2)));
                    // rate = ndi.mean / rate;
                    for (int i = 0; i <= numOfTestPoints; i++)
                    {

                        double testX = startX + i * diff;
                        double testY = (1 / (ndi.SD * Math.Sqrt(2 * Math.PI))) * Math.Exp(-Math.Pow((testX - ndi.mean), 2) / (2 * Math.Pow(ndi.SD, 2)));
                        testY = testY * numOfData;
                        GraphChart.Series["NormalFit"].Points.AddXY(testX, testY);
                    }
                    GraphChart.Series["NormalFit"].Color = Color.Green;
                }
            }

            else if (algorName == "Polynomial Fit")
            {
                double[,] paramsResult = algorithmsAndResult.GetEquationParmas();
                if (paramsResult == null)
                {
                    return;
                }

                for (int i = 0; i <= numOfTestPoints; i++)
                {
                    double testX = startX + i * diff;
                    double testY = 0;
                    for (int j = 0; j < paramsResult.GetLength(0); j++)
                    {
                        testY = testY + Math.Pow(testX, j) * paramsResult[j, 0];
                    }
                    GraphChart.Series["predictGraph"].Points.AddXY(testX, testY);
                }
                GraphChart.Series["predictGraph"].Color = Color.Blue;
            }

            else if (algorName == "Peak" || algorName == "Two Peaks")
            {
                points[] pts = algorithmsAndResult.GetPeakPoints();
                foreach (var pt in pts)
                {
                    GraphChart.Series["Peaks"].Points.AddXY(pt.x, pt.y);
                }
                GraphChart.Series["Peaks"].Color = Color.Purple;
            }

            if (algorName == "Two Peaks")
            {
      
                TwoDictInfo TDinfo = algorithmsAndResult.GetTDinfo();

                NormalDistributionInfo ndi = TDinfo.peak1Info;
                if (TDinfo.peak1value == -1 || TDinfo.peak2value == -1)
                {
                    return;
                }
                double y = (1 / (ndi.SD * Math.Sqrt(2 * Math.PI))) * Math.Exp(-Math.Pow((TDinfo.peak1value - ndi.mean), 2) / (2 * Math.Pow(ndi.SD, 2)));
                double rate = TDinfo.peak1times/y;
                if (ndi.SD != -1 && ndi.mean != -1)
                {
                    
                    for (int i = 0; i < TDinfo.peak2value; i++)
                    {
                        double testX = i;
                        double testY = (1 / (ndi.SD * Math.Sqrt(2 * Math.PI))) * Math.Exp(-Math.Pow((testX - ndi.mean), 2) / (2 * Math.Pow(ndi.SD, 2)));
                        testY = testY * rate;
                        GraphChart.Series["NormalFitPeak1"].Points.AddXY(testX, testY);
                    }
                    GraphChart.Series["NormalFitPeak1"].Color = Color.Green;
                }
                
                ndi = TDinfo.peak2Info;

                y = (1 / (ndi.SD * Math.Sqrt(2 * Math.PI))) * Math.Exp(-Math.Pow((TDinfo.peak2value - ndi.mean), 2) / (2 * Math.Pow(ndi.SD, 2)));
                rate = TDinfo.peak2times / y;
                if (ndi.SD != -1 && ndi.mean != -1)
                {

                    for (int i = (int)TDinfo.peak1value; i < TDinfo.last; i++)
                    {
                        double testX = i;
                        double testY = (1 / (ndi.SD * Math.Sqrt(2 * Math.PI))) * Math.Exp(-Math.Pow((testX - ndi.mean), 2) / (2 * Math.Pow(ndi.SD, 2)));
                        testY = testY * rate;
                        GraphChart.Series["NormalFitPeak2"].Points.AddXY(testX, testY);
                    }
                    GraphChart.Series["NormalFitPeak2"].Color = Color.Red;
                }
            }

            if (algorithmsAndResult.GetCurrentAlgorithm() != "Two Peaks") { 
                algorithmsAndResult.clear();
            }
        }

        private void clearGraphButton_Click(object sender, EventArgs e)
        {
            GraphChart.Series["dataPoints"].Points.Clear();
            GraphChart.Series["predictGraph"].Points.Clear();
            GraphChart.Series["NormalFit"].Points.Clear();
            GraphChart.Series["Peaks"].Points.Clear();
            GraphChart.Series["NormalFitPeak1"].Points.Clear();
            GraphChart.Series["NormalFitPeak2"].Points.Clear();
            algorithmsAndResult.clear();
        }
    }
}
