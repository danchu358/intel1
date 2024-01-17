using System;
using System.Data;
using System.Windows.Forms;
using MySql.Data.MySqlClient;
using System.Windows.Forms.DataVisualization.Charting;

namespace SmartFarm01
{
    public partial class mainWin : Form
    {
        string Conn = "Server=localhost;Database=smartfarm;Uid=root;Pwd=123456;";
        private const int MaxDataPoints = 10;

        public mainWin()
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

        private void button1_Click(object sender, EventArgs e)
        {
            using (MySqlConnection conn = new MySqlConnection(Conn))
            {
                try
                {
                    conn.Open();

                    string sql = "SELECT * FROM your_table_name ORDER BY date DESC LIMIT 1";

                    using (MySqlCommand cmd = new MySqlCommand(sql, conn))
                    {
                        using (MySqlDataReader reader = cmd.ExecuteReader())
                        {
                            if (reader.Read())
                            {
                                int id = reader.GetInt32("id");
                                double illuminance = reader.GetDouble("illu");
                                double temperature = reader.GetDouble("temp");
                                double humidity = reader.GetDouble("humi");
                                DateTime date = reader.GetDateTime("date");

                                textBox1.Text = $"ID: {id}\r\nIlluminance: {illuminance}\r\nTemperature: {temperature}\r\nHumidity: {humidity}\r\nDate: {date}";
                            }
                        }
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error: " + ex.Message);
                }
            }
        }

        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
