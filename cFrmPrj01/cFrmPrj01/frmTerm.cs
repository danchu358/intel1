using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Management;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MySql.Data.MySqlClient;

namespace cFrmPrj01
{
    public partial class Form1 : Form
    {
        MySqlConnection connection = new MySqlConnection("Server=localhost;Database=test;Uid=root;Pwd=123456;");

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            connection.Open();
            MySqlCommand msc = new MySqlCommand("insert into new_table(new_tablecol, new_tablecol1, new_tablecol2, new_tablecol3) values('11', '22', '33', '44')", connection);
            msc.ExecuteNonQuery();
            connection.Close();
        }
    }
}
