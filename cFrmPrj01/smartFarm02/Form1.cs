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
using System.Windows.Forms.DataVisualization.Charting;

namespace smartFarm02
{
    public partial class Form1 : Form
    {
        private string conn = "Server=localhost;Database=smartfarm;Uid=root;Pwd=123456;";
        private Timer timer = new Timer();
        private Random random = new Random();
        private Timer chart3Timer = new Timer();

        public Form1()
        {
            InitializeComponent();
            InitializeChart2();

            timer.Interval = 1000;
            timer.Tick += TimerTick;

            chart3Timer.Interval = 1000;
            chart3Timer.Tick += Chart3Timer_Tick;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            timer.Start();

            chart3Timer.Start();
        }

        private void Chart3Timer_Tick(object sender, EventArgs e)
        {
            UpdateChart3();
        }

        private void UpdateChart3()
        {
            chart3.Series.Clear();
            chart3.ChartAreas.Clear();

            ChartArea chartArea = chart3.ChartAreas.Add("ChartArea");
            chartArea.AxisX.LabelStyle.Format = "yyyy-MM-dd HH:mm:ss";
            chartArea.AxisX.MajorGrid.LineColor = Color.LightGray;
            chartArea.AxisY.MajorGrid.LineColor = Color.LightGray;
            chartArea.AxisX.Title = "Date";
            chartArea.AxisY.Title = "Value";
            chartArea.AxisX.IsMarginVisible = true;
            chartArea.RecalculateAxesScale();

            using (MySqlConnection connection = new MySqlConnection(conn))
            {
                try
                {
                    connection.Open();
                    string query = "SELECT date, illu, temp, humi FROM smartfarm";

                    using (MySqlCommand cmd = new MySqlCommand(query, connection))
                    {
                        using (MySqlDataReader reader = cmd.ExecuteReader())
                        {
                            Series seriesIllu = new Series("Illumination");
                            seriesIllu.ChartType = SeriesChartType.Line;
                            seriesIllu.XValueType = ChartValueType.DateTime;

                            Series seriesTemp = new Series("Temperature");
                            seriesTemp.ChartType = SeriesChartType.Line;
                            seriesTemp.XValueType = ChartValueType.DateTime;

                            Series seriesHumi = new Series("Humidity");
                            seriesHumi.ChartType = SeriesChartType.Line;
                            seriesHumi.XValueType = ChartValueType.DateTime;

                            while (reader.Read())
                            {
                                DateTime date = DateTime.Parse(reader["date"].ToString());
                                int illu = int.Parse(reader["illu"].ToString());
                                int temp = int.Parse(reader["temp"].ToString());
                                int humi = int.Parse(reader["humi"].ToString());

                                seriesIllu.Points.AddXY(date, illu);
                                seriesTemp.Points.AddXY(date, temp);
                                seriesHumi.Points.AddXY(date, humi);
                            }

                            chart3.Series.Add(seriesIllu);
                            chart3.Series.Add(seriesTemp);
                            chart3.Series.Add(seriesHumi);
                        }
                    }
                }

                catch (Exception ex)
                {
                    MessageBox.Show("Error: " + ex.Message);
                }
            }

            chart3.Invalidate();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            using (MySqlConnection connection = new MySqlConnection(conn))
            {
                try
                {
                    connection.Open();

                    using (MySqlCommand cmd = connection.CreateCommand())
                    {
                        cmd.CommandText = "INSERT INTO smartfarm (illu, temp, humi, date) VALUES (@illu, @temp, @humi, @date)";
                        cmd.Parameters.AddWithValue("@illu", random.Next(1, 10));
                        cmd.Parameters.AddWithValue("@temp", random.Next(1, 10));
                        cmd.Parameters.AddWithValue("@humi", random.Next(1, 10));
                        cmd.Parameters.AddWithValue("@date", DateTime.Now);

                        for (int i = 0; i < 10; i++)
                        {
                            cmd.ExecuteNonQuery();
                        }
                    }

                    MessageBox.Show("10개의 임의 데이터가 입력되었습니다.");
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error: " + ex.Message);
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            using (MySqlConnection connection = new MySqlConnection(conn))
            {
                try
                {
                    connection.Open();
                    string query = "SELECT * FROM smartfarm";

                    using (MySqlDataAdapter adapter = new MySqlDataAdapter(query, connection))
                    {
                        DataTable dataTable = new DataTable();
                        adapter.Fill(dataTable);
                        dataGridView1.DataSource = dataTable;
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error: " + ex.Message);
                }
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            UpdateListView();
            UpdateChart3();
        }

        private void UpdateListView()
        {
            listView1.Items.Clear();

            using (MySqlConnection connection = new MySqlConnection(conn))
            {
                try
                {
                    connection.Open();
                    string query = "SELECT * FROM smartfarm";

                    using (MySqlCommand cmd = new MySqlCommand(query, connection))
                    {
                        using (MySqlDataReader reader = cmd.ExecuteReader())
                        {
                            while (reader.Read())
                            {
                                ListViewItem item = new ListViewItem(reader["id"].ToString());
                                item.SubItems.Add(reader["illu"].ToString());
                                item.SubItems.Add(reader["temp"].ToString());
                                item.SubItems.Add(reader["humi"].ToString());
                                item.SubItems.Add(Convert.ToDateTime(reader["date"]).ToString("yyyy-MM-dd HH:mm:ss"));

                                listView1.Items.Add(item);
                            }
                        }
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error: " + ex.Message);
                }
            }

            foreach (ColumnHeader column in listView1.Columns)
            {
                column.Width = -2;
            }

            ReadDataForChart2();
        }

        private void ReadDataForChart2()
        {
            Series seriesIllu = chart2.Series["Illumination"];
            Series seriesTemp = chart2.Series["Temperature"];
            Series seriesHumi = chart2.Series["Humidity"];

            seriesIllu.Points.Clear();
            seriesTemp.Points.Clear();
            seriesHumi.Points.Clear();

            foreach (ListViewItem item in listView1.Items)
            {
                DateTime date = DateTime.Parse(item.SubItems[4].Text);
                int illu = int.Parse(item.SubItems[1].Text);
                int temp = int.Parse(item.SubItems[2].Text);
                int humi = int.Parse(item.SubItems[3].Text);

                seriesIllu.Points.AddXY(date, illu);
                seriesTemp.Points.AddXY(date, temp);
                seriesHumi.Points.AddXY(date, humi);
            }

            chart2.Invalidate();
        }


        private void button4_Click(object sender, EventArgs e)
        {
            chart1.Series.Clear(); 
            chart1.ChartAreas.Clear();
            chart1.Legends.Clear();

            ChartArea mainArea = chart1.ChartAreas.Add("MainArea");

            Legend mainLegend = chart1.Legends.Add("MainLegend");
            mainLegend.Docking = Docking.Top;

            Series seriesIllu = chart1.Series.Add("Illumination");
            seriesIllu.ChartType = SeriesChartType.Line;
            seriesIllu.Legend = "MainLegend";
            seriesIllu.XValueType = ChartValueType.DateTime;

            Series seriesTemp = chart1.Series.Add("Temperature");
            seriesTemp.ChartType = SeriesChartType.Line;
            seriesTemp.Legend = "MainLegend";
            seriesTemp.XValueType = ChartValueType.DateTime;

            Series seriesHumi = chart1.Series.Add("Humidity");
            seriesHumi.ChartType = SeriesChartType.Line;
            seriesHumi.Legend = "MainLegend";
            seriesHumi.XValueType = ChartValueType.DateTime;

            foreach (ListViewItem item in listView1.Items)
            {
                DateTime date = DateTime.Parse(item.SubItems[4].Text);
                int illu = int.Parse(item.SubItems[1].Text);
                int temp = int.Parse(item.SubItems[2].Text);
                int humi = int.Parse(item.SubItems[3].Text);

                seriesIllu.Points.AddXY(date, illu);
                seriesTemp.Points.AddXY(date, temp);
                seriesHumi.Points.AddXY(date, humi);
            }

            mainArea.AxisX.LabelStyle.Format = "yyyy-MM-dd HH:mm:ss";
            mainArea.AxisX.MajorGrid.LineColor = Color.LightGray;
            mainArea.AxisY.MajorGrid.LineColor = Color.LightGray;
            mainArea.AxisX.Title = "Date";
            mainArea.AxisY.Title = "Values";
            mainArea.AxisX.IsMarginVisible = true;
            mainArea.RecalculateAxesScale();

            chart1.Legends.Clear();
            mainLegend = chart1.Legends.Add("MainLegend");
            mainLegend.Docking = Docking.Top;
            mainLegend.Alignment = StringAlignment.Center;
        }

        private void TimerTick(object sender, EventArgs e)
        {
            if (listView1.Items.Count > 0)
            {
                var lastItem = listView1.Items[listView1.Items.Count - 1];

                try
                {
                    DateTime date = DateTime.Parse(lastItem.SubItems[4].Text);
                    int illu = int.Parse(lastItem.SubItems[1].Text);
                    int temp = int.Parse(lastItem.SubItems[2].Text);
                    int humi = int.Parse(lastItem.SubItems[3].Text);

                    AddDataPointToSeries(chart2, "Illumination", date, illu);
                    AddDataPointToSeries(chart2, "Temperature", date, temp);
                    AddDataPointToSeries(chart2, "Humidity", date, humi);

                    chart2.ChartAreas[0].AxisX.Minimum = date.AddMinutes(-5).ToOADate();
                    chart2.ChartAreas[0].AxisX.Maximum = date.ToOADate();

                    chart2.Invalidate();
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Failed to update chart: " + ex.Message);
                }
            }
        }

        private void InitializeChart2()
        {
            chart2.Series.Clear();
            chart2.ChartAreas.Clear();
            chart2.Legends.Clear();

            Legend mainLegend = chart2.Legends.Add("MainLegend");
            mainLegend.Docking = Docking.Top;

            ChartArea mainArea = chart2.ChartAreas.Add("MainArea");

            AddSeriesToChart2("Illumination", Color.Red);
            AddSeriesToChart2("Temperature", Color.Blue);
            AddSeriesToChart2("Humidity", Color.Green);

            mainLegend.Docking = Docking.Top;
        }

        private void AddSeriesToChart2(string seriesName, Color color)
        {
            Series series = chart2.Series.Add(seriesName);
            series.ChartType = SeriesChartType.Line;
            series.Legend = "MainLegend";
            series.Color = color;
            series.XValueType = ChartValueType.DateTime;
        }

        private void AddDataPointToSeries(Chart chart, string seriesName, DateTime xValue, int yValue)
        {
            if (chart.Series.IndexOf(seriesName) == -1)
            {
                chart.Series.Add(seriesName);
            }

            chart.Series[seriesName].Points.AddXY(xValue, yValue);

            while (chart.Series[seriesName].Points.Count > 30)
            {
                chart.Series[seriesName].Points.RemoveAt(0);
            }
        }
    }
}