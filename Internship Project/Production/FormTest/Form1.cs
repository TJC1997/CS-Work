using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Production;

namespace FormTest
{
    public partial class Form1 : Form
    {
        ProductionFacade PF;
        ParseTxT PT;
        MyData[] fileData;
        MyData[] storedData;
       

        public Form1()
        {
            InitializeComponent();
            PF = new ProductionFacade();
            PT = new ParseTxT();
            graphDrawer1.setalgorithmsAndResult(ref algorithmsAndResult1);
        }

        private void SelectFileButton_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
            string path = openFileDialog1.FileName;
            FileLabel.Text = path;
            if (path != "openFileDialog1")
            {
                PT.setPath(path);
                fileData = PT.GetTxTArr();
            }
        }

        private void AddDataButton_Click(object sender, EventArgs e)
        {
            PF.AddMutiData(fileData);
            storedData = PF.GetData();
            MessageBox.Show(storedData.Length+ " Data are in queue now.");
            if(storedData.Length==0){
                return;
            }
            listBox1.Items.Clear();
            string title = "TimeSpan        Index   numOfParams ";
            for (int i = 0; i < storedData[0].GetNumOfParams(); i++)
            {
                title = title + " Param" + (i);
            }
            listBox1.Items.Add(title);
            for (int i = 0; i < storedData.Length; i++)
            {
                listBox1.Items.Add(storedData[i].WriteToLine());
            }
            algorithmsAndResult1.SetFacade(PF);
        }

        private void ClearDataButton_Click(object sender, EventArgs e)
        {
            PF.ClearData();
            fileData = null;
            storedData = null;
            MessageBox.Show(PF.GetData().Length + " Data are in queue now.");
            listBox1.Items.Clear();
            algorithmsAndResult1.SetFacade(PF);
        }
    }
}
