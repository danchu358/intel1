using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MySql.Data.MySqlClient;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace projectTest
{
    
    public partial class Form1 : Form
    {
        string Conn = "Server=localhost;Database=example;Uid=root;Pwd=qwer1234;";
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
            timer1.Interval = 30;
            timer1.Start();

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if(progressBar1.Value < 100)
            {

                progressBar1.Value += 1;
                label2.Text = progressBar1.Value.ToString() + "%";

 
            }
            else
            {
                
                timer1.Stop();
                label2.Text = "로딩이 완료 됐습니다. 로그인 하세요 ~";
                label1.Visible = true;
                label4.Visible = true;
                textBox1.Visible = true;
                textBox2.Visible = true;
                button1.Visible = true;
                button2.Visible = true;
                button3.Visible = true;

            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            using (MySqlConnection conn = new MySqlConnection(Conn))
            {
                DataSet ds = new DataSet(); 
                string sql = "SELECT * FROM admin";
                MySqlDataAdapter adpt = new MySqlDataAdapter(sql, conn);
                adpt.Fill(ds, "admin");

                if ((ds.Tables[0].Rows[0]["id"].ToString() == textBox1.Text.ToString())
                    && (ds.Tables[0].Rows[0]["pwd"].ToString() == textBox2.Text.ToString()))
                {
                    Form2 nf2 = new Form2();
                    nf2.ShowDialog();
                    this.Hide();
                }
                else
                {
                    MessageBox.Show("올바른 관리자 계정을 입력하세요~");
                }

            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            using (MySqlConnection conn = new MySqlConnection(Conn))
            {
                DataSet ds = new DataSet();
                string sql = "SELECT * FROM employee where id = '"+textBox1.Text.ToString()+ "' and pwd = '"+textBox2.Text.ToString()+"'";
                MySqlDataAdapter adpt = new MySqlDataAdapter(sql, conn);
                adpt.Fill(ds, "employee");
                if (ds.Tables[0].Rows.Count > 0)
                {
                    string exePath = @"C:\Users\seung\source\repos\projectTest\projectTest\bin\Debug\MachineLearningTest.exe";
                    Process process = Process.Start(exePath);
                    process.WaitForExit();

                    Form3 nf3 = new Form3();
                    nf3.ShowDialog(this);
                    this.Hide();
                }
                else
                {
                    // 일치하는 사용자가 없는 경우
                    MessageBox.Show("로그인 실패. 올바른 사용자 정보를 입력하세요.");
                }

            }
        }
    }
}
