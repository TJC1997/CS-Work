namespace Production
{
    partial class GraphDrawer
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series2 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series3 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series4 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series5 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series6 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.GraphChart = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.drawButton = new System.Windows.Forms.Button();
            this.clearGraphButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.GraphChart)).BeginInit();
            this.SuspendLayout();
            // 
            // GraphChart
            // 
            chartArea1.Name = "ChartArea1";
            this.GraphChart.ChartAreas.Add(chartArea1);
            legend1.Name = "Legend1";
            this.GraphChart.Legends.Add(legend1);
            this.GraphChart.Location = new System.Drawing.Point(3, 3);
            this.GraphChart.Name = "GraphChart";
            this.GraphChart.Palette = System.Windows.Forms.DataVisualization.Charting.ChartColorPalette.None;
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
            series1.Legend = "Legend1";
            series1.Name = "dataPoints";
            series2.ChartArea = "ChartArea1";
            series2.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series2.Legend = "Legend1";
            series2.Name = "predictGraph";
            series3.ChartArea = "ChartArea1";
            series3.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series3.Color = System.Drawing.Color.Green;
            series3.Legend = "Legend1";
            series3.Name = "NormalFit";
            series4.ChartArea = "ChartArea1";
            series4.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.FastPoint;
            series4.Label = "Peak";
            series4.Legend = "Legend1";
            series4.Name = "Peaks";
            series5.ChartArea = "ChartArea1";
            series5.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series5.Legend = "Legend1";
            series5.Name = "NormalFitPeak1";
            series6.ChartArea = "ChartArea1";
            series6.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series6.Legend = "Legend1";
            series6.Name = "NormalFitPeak2";
            this.GraphChart.Series.Add(series1);
            this.GraphChart.Series.Add(series2);
            this.GraphChart.Series.Add(series3);
            this.GraphChart.Series.Add(series4);
            this.GraphChart.Series.Add(series5);
            this.GraphChart.Series.Add(series6);
            this.GraphChart.Size = new System.Drawing.Size(825, 454);
            this.GraphChart.TabIndex = 0;
            this.GraphChart.Text = "Graph Chart";
            // 
            // drawButton
            // 
            this.drawButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.drawButton.Location = new System.Drawing.Point(697, 134);
            this.drawButton.Name = "drawButton";
            this.drawButton.Size = new System.Drawing.Size(131, 53);
            this.drawButton.TabIndex = 1;
            this.drawButton.Text = "Draw Graph";
            this.drawButton.UseVisualStyleBackColor = true;
            this.drawButton.Click += new System.EventHandler(this.drawButton_Click);
            // 
            // clearGraphButton
            // 
            this.clearGraphButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.clearGraphButton.Location = new System.Drawing.Point(697, 235);
            this.clearGraphButton.Name = "clearGraphButton";
            this.clearGraphButton.Size = new System.Drawing.Size(131, 54);
            this.clearGraphButton.TabIndex = 2;
            this.clearGraphButton.Text = "Clear Graph";
            this.clearGraphButton.UseVisualStyleBackColor = true;
            this.clearGraphButton.Click += new System.EventHandler(this.clearGraphButton_Click);
            // 
            // GraphDrawer
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.clearGraphButton);
            this.Controls.Add(this.drawButton);
            this.Controls.Add(this.GraphChart);
            this.Name = "GraphDrawer";
            this.Size = new System.Drawing.Size(835, 454);
            ((System.ComponentModel.ISupportInitialize)(this.GraphChart)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataVisualization.Charting.Chart GraphChart;
        private System.Windows.Forms.Button drawButton;
        private System.Windows.Forms.Button clearGraphButton;
    }
}
