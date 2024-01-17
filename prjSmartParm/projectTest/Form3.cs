using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;
using MySql.Data.MySqlClient;
using static System.Net.Mime.MediaTypeNames;


namespace projectTest
{
    public partial class Form3 : Form
    {
        string Conn = "Server=localhost;Database=example;Uid=root;Pwd=qwer1234;";
        char whichData = 'v';
        double temp;
        double humid;
        double light;
        double landmois;
        //private int _x = -1, _y = -1;
        public Form3()
        {
            InitializeComponent();

        }

        private void button1_Click(object sender, EventArgs e)
        {
            serialPort1.Close();
            this.Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "") {
                MessageBox.Show("포트를 선택하세요");
            }
            else
            {
                serialPort1.PortName = textBox1.Text;
                if(serialPort1.IsOpen == false)
                {
                    serialPort1.Open();
                }

                timer1.Interval = 2000;
                timer1.Start();
                timer2.Interval = 2111;
                timer2.Start();
                timer3.Interval = 2222;
                timer3.Start();
                timer4.Interval = 2711;
                timer4.Start();
                timer5.Interval = 2433;
                timer5.Start();

            }    
        }
        
        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            if (whichData == 'v') {
                serialPort1.Write("v");
                timer1.Enabled = false;
                timer2.Enabled = false;
                timer3.Enabled = false;
                timer4.Enabled = false;
                timer5.Enabled = false;
                string dist = serialPort1.ReadLine();
                double length = double.Parse(dist);

                string angle = serialPort1.ReadLine();
                double radians = double.Parse(angle) * (Math.PI / 180);
                double cosValue = Math.Cos(radians);
                double sinValue = Math.Sin(radians);

                string date = DateTime.Now.ToString("yyyy-MM-dd HH:mm::ss");      

                double x = (length*10) * cosValue;
                int _x =  270 + (int)x;
                double y = (length*4) * sinValue;
                int _y = 150 - (int)y;

                this.Invoke((MethodInvoker)delegate
                {
                    pictureBox6.Location = new Point(_x, _y);
                });


                using (MySqlConnection conn = new MySqlConnection(Conn))
                {
                    conn.Open();
                    MySqlCommand msc = new MySqlCommand(
                        "insert into example(target_x, target_y, date) values('" + _x + "', '" + _y + "', '" + date + "')", conn);
                    msc.ExecuteNonQuery();
                }
                timer1.Enabled = true;
                timer2.Enabled = true;
                timer3.Enabled = true;
                timer4.Enabled = true;
                timer5.Enabled = true;
            }

            if (whichData == 'c')
            {
                
                string test = serialPort1.ReadLine();
                light = double.Parse(test);
                light = ((light - 2400.0) * (10.0/(3500.0-2600.0)));
                if (light < 0) light = 5.5;
                this.Invoke((MethodInvoker)delegate
                {
                    label2.Text = String.Format("조도: {0:F2}", light);
                });
                whichData = 'v';

            }
            if(whichData == 't')
            {
                
                string test = serialPort1.ReadLine();
                this.Invoke((MethodInvoker)delegate
                {
                    label3.Text = "온도 :" + test;
                });
                temp = double.Parse(test);
                whichData = 'v';
            }
            if (whichData == 'h')
            {
                
                string test = serialPort1.ReadLine();
                this.Invoke((MethodInvoker)delegate
                {
                    label4.Text = "습도 :" + test;
                });

                humid = double.Parse(test);
                whichData = 'v';
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen == true)
            {
                serialPort1.Close();
                timer1.Stop();
                timer2.Stop();
                timer3.Stop();
                timer4.Stop();

            }
        }

        

        private void timer1_Tick(object sender, EventArgs e)  // 조도데이터 읽어오는 타이머 
        {
            
            if (serialPort1.IsOpen == true)
            {
                whichData = 'c';
                serialPort1.Write("c");
            }
            else
            {
                MessageBox.Show("시리얼 포트를 열어주세요 ~");
            }
            
        }

        private void timer2_Tick(object sender, EventArgs e)  // 온도데이터 읽어오는 타이머 
        {
            timer6.Enabled = false;
            if (serialPort1.IsOpen == true)
            {
                whichData = 't';
                serialPort1.Write("t");
            }
            else
            {
                MessageBox.Show("시리얼 포트를 열어주세요 ~");
            }
            
        }

        private void timer3_Tick(object sender, EventArgs e) // 습도데이터 stm32보드로 보내는 타이머 
        {
            timer6.Enabled = false;
            if (serialPort1.IsOpen == true)
            {
                whichData = 'h';
                serialPort1.Write("h");
            }
            else
            {
                MessageBox.Show("시리얼 포트를 열어주세요 ~");
            }
            
        }

        private void timer4_Tick(object sender, EventArgs e)  // 받아온 조도, 온도, 습도 데이터를 
        {
            timer6.Enabled = false;
            using (MySqlConnection conn = new MySqlConnection(Conn))
            {
                DataSet ds = new DataSet();
                string sql = "SELECT * FROM machinelearningresult";
                MySqlDataAdapter adpt = new MySqlDataAdapter(sql, conn);
                adpt.Fill(ds, "machinelearningresult");

                DataTable dt = ds.Tables["machinelearningresult"];

                double w_0, w_1, w_2, w_3;

                w_0 = double.Parse(dt.Rows[0]["w_0"].ToString());
                w_1 = double.Parse(dt.Rows[0]["w_1"].ToString());
                w_2 = double.Parse(dt.Rows[0]["w_2"].ToString());
                w_3 = double.Parse(dt.Rows[0]["w_3"].ToString());

                landmois = (temp * w_3) + (humid * w_2) + (light * w_1) + w_0;

                label5.Text = String.Format("토양수분량: {0:F2}", landmois);
            }

            using (MySqlConnection conn = new MySqlConnection(Conn))
            {
                conn.Open();
                MySqlCommand msc = new MySqlCommand("insert into sensor(light, temp, humid, soilmoist) values("+light+","+temp+","+humid+","+landmois+")", conn);
                msc.ExecuteNonQuery();
            }

        }

      
        private void button4_Click(object sender, EventArgs e)
        {
            using (MySqlConnection conn = new MySqlConnection(Conn))
            {
                DataSet ds = new DataSet();
                string sql = "SELECT * FROM sensor order by num desc limit 10";
                MySqlDataAdapter adpt = new MySqlDataAdapter(sql, conn);
                adpt.Fill(ds, "sensor");

                listView1.Items.Clear();
                for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
                {
                    ListViewItem lvi = new ListViewItem();
                    lvi.Text = ds.Tables[0].Rows[i]["num"].ToString();

                    lvi.SubItems.Add(ds.Tables[0].Rows[i]["light"].ToString());
                    lvi.SubItems.Add(ds.Tables[0].Rows[i]["temp"].ToString());
                    lvi.SubItems.Add(ds.Tables[0].Rows[i]["humid"].ToString());
                    lvi.SubItems.Add(ds.Tables[0].Rows[i]["soilmoist"].ToString());

                    listView1.Items.Add(lvi);
                }

                chart1.Series.Clear();
                chart1.Series.Add("조도");
                chart1.Series.Add("온도");
                chart1.Series.Add("습도");
                chart1.Series.Add("토양수분량");

                for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
                {
                    double lightValue = Convert.ToDouble(ds.Tables[0].Rows[i]["light"]);
                    double tempValue = Convert.ToDouble(ds.Tables[0].Rows[i]["temp"]);
                    double humidValue = Convert.ToDouble(ds.Tables[0].Rows[i]["humid"]);
                    double soilmoistValue = Convert.ToDouble(ds.Tables[0].Rows[i]["soilmoist"]);

                    chart1.Series["조도"].Points.AddXY(i + 1, lightValue);
                    chart1.Series["온도"].Points.AddXY(i + 1, tempValue);
                    chart1.Series["습도"].Points.AddXY(i + 1, humidValue);
                    chart1.Series["토양수분량"].Points.AddXY(i + 1, soilmoistValue);
                }

                chart1.ChartAreas[0].AxisX.Title = "최근 10개 데이터";
                chart1.ChartAreas[0].AxisY.Title = "값";

                foreach (var series in chart1.Series)
                {
                    series.ChartType = SeriesChartType.Line;
                }

                chart1.Series["조도"].Color = Color.Blue;
                chart1.Series["온도"].Color = Color.Red;
                chart1.Series["습도"].Color = Color.Green;
                chart1.Series["토양수분량"].Color = Color.Brown;
            }
        }


        private void button5_Click(object sender, EventArgs e)
        {
            listView1.Items.Clear();
            using (MySqlConnection conn = new MySqlConnection(Conn))
            {
                conn.Open();
                MySqlCommand msc = new MySqlCommand("TRUNCATE table sensor", conn);
                msc.ExecuteNonQuery();
            }
        }

        private void timer5_Tick(object sender, EventArgs e)
        {
            timer6.Enabled = false;
            if (light < 6)
            {
                pictureBox2.Load(@"C:\Users\seung\source\repos\projectTest\projectTest\Resources\LEDON.PNG");
                pictureBox2.SizeMode = PictureBoxSizeMode.StretchImage;
            }
            else
            {
                pictureBox2.Load(@"C:\Users\seung\source\repos\projectTest\projectTest\Resources\LEDOFF.PNG");
                pictureBox2.SizeMode = PictureBoxSizeMode.StretchImage;
            }

            if (temp < 20 || humid > 40)
            {
                pictureBox3.Load(@"C:\Users\seung\source\repos\projectTest\projectTest\Resources\LEDON.PNG");
                pictureBox3.SizeMode = PictureBoxSizeMode.StretchImage;
            }
            else
            {
                pictureBox3.Load(@"C:\Users\seung\source\repos\projectTest\projectTest\Resources\LEDOFF.PNG");
                pictureBox3.SizeMode = PictureBoxSizeMode.StretchImage;
            }

            if (temp > 25)
            {
                pictureBox1.Load(@"C:\Users\seung\source\repos\projectTest\projectTest\Resources\LEDON.PNG");
                pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
            }
            else
            {
                pictureBox1.Load(@"C:\Users\seung\source\repos\projectTest\projectTest\Resources\LEDOFF.PNG");
                pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
            }

            if (landmois < 10)
            {
                pictureBox4.Load(@"C:\Users\seung\source\repos\projectTest\projectTest\Resources\LEDON.PNG");
                pictureBox4.SizeMode = PictureBoxSizeMode.StretchImage;
            }
            else
            {
                pictureBox4.Load(@"C:\Users\seung\source\repos\projectTest\projectTest\Resources\LEDOFF.PNG");
                pictureBox4.SizeMode = PictureBoxSizeMode.StretchImage;
            }
            timer6.Enabled = true;
        }

        private void checkBox1_Click(object sender, EventArgs e)
        {
            serialPort1.Write("v");
            //checkBox1.Checked = true;
            //checkBox2.Checked = false;

            //LeftB.Enabled = false;
            //RightB.Enabled = false;
            //String str = "A";

            //serialPort1.Write(Encoding.Default.GetBytes(str), 0, 1);
        }

       

        
        //void viewpicture()
        //{
        //    if (_x == -1 && _y == -1) return;
        //    pictureBox6.Location = new Point(_x, _y);
        //    if (_x != 0 && _y != 0) pictureBox6.Visible = true;
        //}

        private void ResetB_Click(object sender, EventArgs e)
        {
            listView2.Items.Clear();
            using (MySqlConnection conn = new MySqlConnection(Conn))
            {  

                DataSet ds = new DataSet();
                string sql = "delete FROM example";
                MySqlDataAdapter adpt = new MySqlDataAdapter(sql, conn);
                adpt.Fill(ds, "example");
            }
        }

        private void returnB_Click(object sender, EventArgs e)
        {
            using (MySqlConnection conn = new MySqlConnection(Conn))
            {   

                DataSet ds = new DataSet();
                string sql = "SELECT * FROM example order by num desc limit 10";
                MySqlDataAdapter adpt = new MySqlDataAdapter(sql, conn);
                adpt.Fill(ds, "example");


                for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
                {

                    ListViewItem lvi = new ListViewItem();
                    lvi.Text = ds.Tables[0].Rows[i]["num"].ToString();
                    lvi.SubItems.Add(ds.Tables[0].Rows[i]["Target_x"].ToString());
                    lvi.SubItems.Add(ds.Tables[0].Rows[i]["Target_y"].ToString());
                    lvi.SubItems.Add(ds.Tables[0].Rows[i]["date"].ToString());
                    listView2.Items.Add(lvi);

                }
            }
        }

        


        //private void timer6_Tick(object sender, EventArgs e)
        //{
        //    timer1.Enabled = false;
        //    timer2.Enabled = false;
        //    timer3.Enabled = false;
        //    timer4.Enabled = false;
        //    timer5.Enabled = false;
        //    viewpicture();
        //timer1.Enabled = true;
        //    timer2.Enabled = true;
        //    timer3.Enabled = true;
        //    timer4.Enabled = true;
        //    timer5.Enabled = true;
        //}

    }
}
