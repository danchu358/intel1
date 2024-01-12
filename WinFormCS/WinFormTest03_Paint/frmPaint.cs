using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinFormTest03_Paint
{
    public partial class frmPaint : Form
    {
        Graphics g = null;
        Pen pen = null;
        Brush brush = null;
        Bitmap bmCanvas = null;

        int dMode = 0;  // 0:Not, 1:pen, 2:line, 3:rect, 4:cir, 5:text
        int dFlag = 0;  // 0:open, 1:pressed => mouse button
        Point p1, p2, p3;
        Point cp1, cp2, cp3;  // Screen 좌표계

        public frmPaint()
        {
            InitializeComponent();
            frmPaint_ResizeEnd(null, null);
            pen = new Pen(Color.Red, 2.0f);
            sbLabel4.Text = "";
        }

        private void frmPaint_ResizeEnd(object sender, EventArgs e)
        {
            int draw_X = Canvas.Width, draw_Y = Canvas.Height;

            if (bmCanvas == null)
            {
                bmCanvas = new Bitmap(draw_X, draw_Y);
                Canvas.Image = bmCanvas;
            }
            else
            {
                Bitmap tBmp = new Bitmap(draw_X, draw_Y);
                Graphics tg = Graphics.FromImage(tBmp);
                tg.DrawImage(bmCanvas, 0, 0);
                bmCanvas.Dispose();
                bmCanvas = tBmp;
                Canvas.Image = bmCanvas;
            }
            g = Graphics.FromImage(bmCanvas);
        }

        private void Canvas_MouseDown(object sender, MouseEventArgs e)
        {
            dFlag = 1;
            p1 = e.Location;
            p2 = e.Location;
            p3 = e.Location;
            cp1 = cp2 = cp3 = ((Control)sender).PointToScreen(p1);         
        }

        private void Canvas_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.X < 0 || e.Y < 0 || e.X > Canvas.Width || e.Y > Canvas.Height) return;

            if (dFlag != 0) switch(dMode)
            {
                    case 1:  // pen draw
                        g.DrawLine(pen, p1, e.Location);
                        Canvas.Invalidate();
                        p1 = e.Location;
                        break;
                    case 2:  // line draw
                        cp3 = ((Control)sender).PointToScreen(e.Location);
                        ControlPaint.DrawReversibleLine(cp1, cp2, DefaultBackColor);
                        ControlPaint.DrawReversibleLine(cp1, cp3, DefaultBackColor);
                        cp2 = cp3;
                        break;
                    case 3:  // rect draw
                    case 4:  // circle draw
                    default: break;
            }
            string str = $"{e.X} x {e.Y}";
            sbLabel1.Text = str;
        }

        private void Canvas_MouseUp(object sender, MouseEventArgs e)
        {
            switch(dMode)
            {
                case 2: // Line draw
                    g.DrawLine(pen, p1, e.Location);
                    break;
                default: break;
            }
            dFlag = 0;
        }

        private void menuDraw_Click(object sender, EventArgs e)
        {
            dMode = 1;
            sbLabel4.Text = "free draw";
        }

        private void menuLine_Click(object sender, EventArgs e)
        {
            dMode = 2;
            sbLabel4.Text = "draw line";
        }

        private void menuRect_Click(object sender, EventArgs e)
        {
            dMode = 3;
            sbLabel4.Text = "draw Rect";
        }

        private void menuCircle_Click(object sender, EventArgs e)
        {
            dMode = 4;
            sbLabel4.Text = "draw Cir";
        }

        private void frmPaint_Resize(object sender, EventArgs e)
        {
            if (WindowState == FormWindowState.Maximized) 
                frmPaint_ResizeEnd(sender, e);
        }

        SqlConnection sqlConn = new SqlConnection();
        SqlCommand sqlCom = new SqlCommand();
        string sConn;

        private void menuOpen_Click(object sender, EventArgs e)
        {
            DialogResult ret = openFileDialog1.ShowDialog();

            if (ret == DialogResult.OK)
            {
                List<int> data = new List<int>();
                FileStream fs = new FileStream(openFileDialog1.FileName, FileMode.Open);
                StreamReader sr = new StreamReader(fs);
                string[] str = sr.ReadToEnd().Split('\n');

                for (int i = 0; i < str.Length - 1; i++)
                {
                    string[] s = str[i].Split(',');
                    data.Add(int.Parse(s[1]));
                }
                int dataLength = str.Length;
                int l = 0, t = 0, r = Canvas.Width, b = Canvas.Height;
                int range = r - l - 60;
                double step = (double)range / dataLength;
                int amp = -(b - 30) * data.Max();
                int xOffset = 20;
                int yOffset = b - 10;

                g.DrawLine(pen, new Point(l + 20, b + yOffset), new Point(r - 20, b + yOffset));
                g.DrawLine(pen, new Point(l + 20, 10), new Point(l + 20, b - 10));
                PointF p1, p2;
                p1 = new PointF(xOffset, yOffset);

                for (int i = 0; i < 360; i++)
                {
                    p2 = new PointF(i * step + xOffset, (float)data[i] * amp + yOffset);
                    g.DrawLine(pen, p1, p2);
                    p1 = p2;
                }
                Canvas.Invalidate();
                sr.Close();
                fs.Close();
            }
        }

        private void menuTestSine_Click(object sender, EventArgs e)
        {
            menuErase_Click(sender, e);
            List<double> data = new List<double>();

            for (int i = 0; i < 360; i++)
            { // Pi = 3.141592
                data.Add(Math.Sin(3.141592 / 180 * i));
            }

            int dataLength = str.Length;
            int l = 0, t = 0, r = Canvas.Width, b = Canvas.Height;
            int range = r - l - 60;
            double step = (double)range / dataLength;
            int amp = -(b - 30) * data.Max();
            int xOffset = 20;
            int yOffset = b - 10;

            g.DrawLine(pen, new Point(l + 20, b + yOffset), new Point(r - 20, b + yOffset));
            g.DrawLine(pen, new Point(l + 20, 10), new Point(l + 20, b - 10));
            PointF p1, p2;
            p1 = new PointF(xOffset, yOffset);

            for (int i = 0; i < 360; i++)
            {
                p2 = new PointF(i * step + xOffset, (float)data[i] * amp + yOffset);
                g.DrawLine(pen, p1, p2);
                p1 = p2;
            }
            Canvas.Invalidate();
        }

        string GetFileName(string sPath)
        {
            string[] sa = sPath.Split('\\');
            return sa[sa.Length - 1];
        }

        private void menuText_Click(object sender, EventArgs e)
        {
            dMode = 5;
            sbLabel4.Text = "input string";
        }

        private void Canvas_Click(object sender, EventArgs e)
        {

        }

        private void menuErase_Click(object sender, EventArgs e)
        {
            g.Clear(DefaultBackColor);
            Canvas.Invalidate();
        }

        private void Canvas_Paint(object sender, PaintEventArgs e)
        {
            Graphics g= e.Graphics;
            Pen pen = new Pen(Color.Red);
            Point p1 = new Point(Left, Top);
            Point p2 = new Point(Right, Bottom);
            Point p3 = new Point(Left, Bottom);
            Point p4 = new Point(Right, Top);
            g.DrawLine(pen, p1, p2);
            g.DrawLine(pen, p3, p4);
        }
    }
}
