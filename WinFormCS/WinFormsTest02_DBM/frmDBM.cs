using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinFormsTest02_DBM
{
    public partial class frmDBM : Form
    {
        public frmDBM()
        {
            InitializeComponent();
        }

        private void splitContainer1_Panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void tbSQL_TextChanged(object sender, EventArgs e)
        {

        }

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {

        }

        string GetFileName(string sPath)
        {
            string[] sa = sPath.Split('\\');
            return sa[sa.Length - 1];
        }
        SqlConnection sqlConn = new SqlConnection();
        SqlCommand sqlCom = new SqlCommand();
        string sConn; 
        
        private void menuOpen_Click(object sender, EventArgs e)
        {   // DB file select
            openFileDialog1.Filter = "MS-SQL Database file|*.mdf";
            if(DialogResult.OK == openFileDialog1.ShowDialog())
            {
                sConn = $"Data Source=(LocalDB)\\MSSQLLocalDB;AttachDbFilename={openFileDialog1.FileName};Integrated Security=True;Connect Timeout=30";
                sqlConn.ConnectionString = sConn;
                sqlConn.Open();
                sqlCom.Connection = sqlConn;
                sbLabel1.BackColor = Color.Green;
                sbLabel1.Text = GetFileName(openFileDialog1.FileName);
            }
        }

        string[] RunSql(string sql)  // Select vs Others
        {
            sqlCom.CommandText = sql;

            if (sql.Trim().ToLower().Substring(0, 6) == "select")
            {
                SqlDataReader sr = sqlCom.ExecuteReader();

                for (int i = 0; i < sr.FieldCount; i++)
                {
                    string colName = sr.GetName(i);
                    dataView.Columns.Add(colName, colName);
                }
            }

            SqlDataReader sr = sqlCom.ExecuteReader();

            for (int i = 0; i < sr.FieldCount; i++)
            {
                string colName = sr.GetName(i);
                dataView.Columns.Add(colName, colName);
            }

            for (; sr.Read();)
            {
                int nRow = dataView.Rows.Add();

                for (int i = 0; i < sr.FieldCount; i++)
                {
                    object o = sr.GetValue(i);
                    dataView.Rows[nRow].Cells[i].Value = o;
                }
            }
        }

        private void menuSql1_Click(object sender, EventArgs e)
        {
            string sql = "Select * from person";
        }
    }
}
