using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MySql.Data.MySqlClient;

namespace projectTest
{
    public partial class Form2 : Form
    {
        string Conn = "Server=localhost;Database=example;Uid=root;Pwd=qwer1234;";
        public Form2()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Form1 nf1 = new Form1();
            nf1.ShowDialog();
            this.Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "" || textBox2.Text == "")
            {
                MessageBox.Show("아이디 또는 비밀번호를 입력해주세요~");
            }
            else
            {
                //DB 데이터 삽입
                //using을 쓰면 알아서 MySQL과 disconnect를 해준다.
                using (MySqlConnection conn = new MySqlConnection(Conn))
                {
                    conn.Open(); //접속 
                    MySqlCommand msc = new MySqlCommand(
                        "insert into employee(id,pwd) values('" + textBox1.Text + "','" + textBox2.Text + "')"
                        , conn);
                    int res = msc.ExecuteNonQuery(); //SQL 쿼리가 MySQL로 날아간다.
                }

                listView1.Items.Clear();


            }

            using (MySqlConnection conn = new MySqlConnection(Conn))
            {
                DataSet ds = new DataSet(); //시트가 날라오면 DataSet의 자료형과 정확히 일치
                string sql = "SELECT * FROM employee limit 20";
                MySqlDataAdapter adpt = new MySqlDataAdapter(sql, conn);
                adpt.Fill(ds, "employee");

                //받아온 테이블 전체를 순회하는 과정
                for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
                {
                    //한 레코드씩 리스트뷰에 집어넣는 과정 
                    ListViewItem lvi = new ListViewItem();
                    lvi.Text = ds.Tables[0].Rows[i]["num"].ToString();

                    lvi.SubItems.Add(ds.Tables[0].Rows[i]["id"].ToString());
                    lvi.SubItems.Add(ds.Tables[0].Rows[i]["pwd"].ToString());

                    listView1.Items.Add(lvi);
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            listView1.Items.Clear();
            using (MySqlConnection conn = new MySqlConnection(Conn))
            {
                DataSet ds = new DataSet(); //시트가 날라오면 DataSet의 자료형과 정확히 일치
                string sql = "SELECT * FROM employee limit 20";
                MySqlDataAdapter adpt = new MySqlDataAdapter(sql, conn);
                adpt.Fill(ds, "employee");

                //받아온 테이블 전체를 순회하는 과정
                for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
                {
                    //한 레코드씩 리스트뷰에 집어넣는 과정 
                    ListViewItem lvi = new ListViewItem();
                    lvi.Text = ds.Tables[0].Rows[i]["num"].ToString();

                    lvi.SubItems.Add(ds.Tables[0].Rows[i]["id"].ToString());
                    lvi.SubItems.Add(ds.Tables[0].Rows[i]["pwd"].ToString());

                    listView1.Items.Add(lvi);
                }
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            using (MySqlConnection conn = new MySqlConnection(Conn))
            {
                conn.Open();
                MySqlCommand msc = new MySqlCommand("delete from employee where id = '"+textBox1.Text+"' && pwd = '"+textBox2.Text+"';", conn);
                msc.ExecuteNonQuery();
            }
            listView1.Items.Clear();

            using (MySqlConnection conn = new MySqlConnection(Conn))
            {
                DataSet ds = new DataSet(); //시트가 날라오면 DataSet의 자료형과 정확히 일치
                string sql = "SELECT * FROM employee limit 20";
                MySqlDataAdapter adpt = new MySqlDataAdapter(sql, conn);
                adpt.Fill(ds, "employee");

                //받아온 테이블 전체를 순회하는 과정
                for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
                {
                    //한 레코드씩 리스트뷰에 집어넣는 과정 
                    ListViewItem lvi = new ListViewItem();
                    lvi.Text = ds.Tables[0].Rows[i]["num"].ToString();

                    lvi.SubItems.Add(ds.Tables[0].Rows[i]["id"].ToString());
                    lvi.SubItems.Add(ds.Tables[0].Rows[i]["pwd"].ToString());

                    listView1.Items.Add(lvi);
                }
            }
        }


    }
}
