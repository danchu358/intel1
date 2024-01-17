using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinFormsPrj01
{
    public partial class frmConfig01 : Form
    {
        public frmConfig01(int n1 = 0, int n2 = 0, int n3 = 0, int n4 = 0, int n5 = 0)
        {
            InitializeComponent();
            string[] l = System.IO.Ports.SerialPort.GetPortNames();
            foreach (string s in l)
            {
                cmbPort.Items.Add(s);
            }
            cmbPort.SelectedIndex = n1;
            cmbBaud.SelectedIndex = n2;
            cmbParity.SelectedIndex = n3;
            cmbData.SelectedIndex = n4;
            cmbStop.SelectedIndex = n5;
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
    }
}
