using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinFormsPrj01
{
    public partial class frmTerm : Form
    {
        public frmTerm()
        {
            InitializeComponent();
        }

        delegate void AddTextCB(string str);

        void AddText(string s)
        {
            if (tbTerm.InvokeRequired)
            {
                AddTextCB cb = new AddTextCB(AddText);
                object[] arg = new object[] { s };
                Invoke(cb, arg);
            }
            else
            {
                tbTerm.Text += s;
            }
        }

        string StrComm = "";
        void OpenPort()
        {
            serialPort1.Open();
            sbLabel1.Text = StrComm;
            sbLabel1.BackColor = Color.Green;
            AddText(StrComm);
        }

        private void menuConfig_Click(object sender, EventArgs e)
        {
            frmConfig01 dlg = new frmConfig01(0, 0, 0, 0, 1);
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                serialPort1.PortName = dlg.cmbPort.Text;
                serialPort1.BaudRate = int.Parse(dlg.cmbBaud.Text);
                serialPort1.Parity = (Parity)dlg.cmbParity.SelectedIndex;
                serialPort1.DataBits = int.Parse(dlg.cmbData.Text);
                serialPort1.StopBits = (StopBits)dlg.cmbStop.SelectedIndex;
                StrComm = $"{serialPort1.PortName}:{serialPort1.BaudRate}{dlg.cmbParity.Text[0]}{serialPort1.DataBits}{dlg.cmbStop.Text}";
                OpenPort();
            }
        }

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            string str = serialPort1.ReadExisting();
            AddText(str);
        }
    }
}
