using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinFormTest01_Base
{
    public partial class frmBase : Form
    {
        int EncMode = 0;  // 0:UTF-8, 1:ANSI

        public frmBase()
        {
            InitializeComponent();
            if(EncMode == 0 ) menuUTF_Click(null, null);
            else              menuANSI_Click(null, null);
        }

        private void btnOpen_Click(object sender, EventArgs e)
        {
            menuOpen_Click(sender, e);
        }
        
        Encoding enc = Encoding.UTF8;
        private void menuOpen_Click(object sender, EventArgs e)
        {
            DialogResult ret = openFileDialog1.ShowDialog();

            if (ret == DialogResult.OK)
            {
                string fn = openFileDialog1.FileName;
                FileStream fs = new FileStream(fn, FileMode.Open);
                StreamReader sr = new StreamReader(fs, enc);
                tbMemo.Text += sr.ReadToEnd();
                sr.Close();
                fs.Close();

                //while (true)
                //{
                //    string str1 = sr.ReadLine();
                //    if (str1 == null) break;
                //    tbMemo.Text += str1;
                //}
            }
        }

        private void menuSave_Click(object sender, EventArgs e)
        {
            DialogResult ret = saveFileDialog1.ShowDialog();

            if (ret == DialogResult.OK)
            {
                string fn = saveFileDialog1.FileName;
                FileStream fs = new FileStream(fn, FileMode.Create);
                StreamWriter sw = new StreamWriter(fs, enc);
                sw.Write(tbMemo.Text);
                sw.Close();
                fs.Close();
            }
        }

        private void menuANSI_Click(object sender, EventArgs e)
        {
            enc = Encoding.Default;
            Label1.Text = "ANSI";
            menuANSI.Checked = true;
            menuUTF.Checked = false;
        }

        private void menuUTF_Click(object sender, EventArgs e)
        {
            enc = Encoding.UTF8;
            Label1.Text = "UTF-8";
            menuANSI.Checked = false;
            menuUTF.Checked = true;
        }
        
        private void menuAbout_Click(object sender, EventArgs e)
        {
            string s = "";
            frmAbout frm = new frmAbout();
            DialogResult r = frm.ShowDialog();

            if (r == DialogResult.OK) s = "About...OK";
            else                      s = "About...Cancel";

            Label2.Text = s;
        }
    }
}
