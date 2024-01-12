namespace WinFormTest03_Paint
{
    partial class frmPaint
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.파일ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuNew = new System.Windows.Forms.ToolStripMenuItem();
            this.menuOpen = new System.Windows.Forms.ToolStripMenuItem();
            this.menuSave = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.menuEnd = new System.Windows.Forms.ToolStripMenuItem();
            this.홈ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuDraw = new System.Windows.Forms.ToolStripMenuItem();
            this.menuLine = new System.Windows.Forms.ToolStripMenuItem();
            this.menuRect = new System.Windows.Forms.ToolStripMenuItem();
            this.menuCircle = new System.Windows.Forms.ToolStripMenuItem();
            this.menuText = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripSeparator();
            this.menuErase = new System.Windows.Forms.ToolStripMenuItem();
            this.보기ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuColor = new System.Windows.Forms.ToolStripMenuItem();
            this.ㄷToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.sbLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.sbLabel2 = new System.Windows.Forms.ToolStripStatusLabel();
            this.sbLabel3 = new System.Windows.Forms.ToolStripStatusLabel();
            this.sbLabel4 = new System.Windows.Forms.ToolStripStatusLabel();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.Canvas = new System.Windows.Forms.PictureBox();
            this.menuTestSine = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Canvas)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.파일ToolStripMenuItem,
            this.홈ToolStripMenuItem,
            this.보기ToolStripMenuItem,
            this.ㄷToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(800, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 파일ToolStripMenuItem
            // 
            this.파일ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuNew,
            this.menuOpen,
            this.menuSave,
            this.toolStripMenuItem1,
            this.menuEnd});
            this.파일ToolStripMenuItem.Name = "파일ToolStripMenuItem";
            this.파일ToolStripMenuItem.Size = new System.Drawing.Size(43, 20);
            this.파일ToolStripMenuItem.Text = "파일";
            // 
            // menuNew
            // 
            this.menuNew.Name = "menuNew";
            this.menuNew.Size = new System.Drawing.Size(138, 22);
            this.menuNew.Text = "새로 만들기";
            // 
            // menuOpen
            // 
            this.menuOpen.Name = "menuOpen";
            this.menuOpen.Size = new System.Drawing.Size(180, 22);
            this.menuOpen.Text = "열기";
            this.menuOpen.Click += new System.EventHandler(this.menuOpen_Click);
            // 
            // menuSave
            // 
            this.menuSave.Name = "menuSave";
            this.menuSave.Size = new System.Drawing.Size(138, 22);
            this.menuSave.Text = "저장";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(135, 6);
            // 
            // menuEnd
            // 
            this.menuEnd.Name = "menuEnd";
            this.menuEnd.Size = new System.Drawing.Size(138, 22);
            this.menuEnd.Text = "끝내기";
            // 
            // 홈ToolStripMenuItem
            // 
            this.홈ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuDraw,
            this.menuLine,
            this.menuRect,
            this.menuCircle,
            this.menuText,
            this.toolStripMenuItem2,
            this.menuErase});
            this.홈ToolStripMenuItem.Name = "홈ToolStripMenuItem";
            this.홈ToolStripMenuItem.Size = new System.Drawing.Size(55, 20);
            this.홈ToolStripMenuItem.Text = "그리기";
            // 
            // menuDraw
            // 
            this.menuDraw.Name = "menuDraw";
            this.menuDraw.Size = new System.Drawing.Size(150, 22);
            this.menuDraw.Text = "자유도형";
            this.menuDraw.Click += new System.EventHandler(this.menuDraw_Click);
            // 
            // menuLine
            // 
            this.menuLine.Name = "menuLine";
            this.menuLine.Size = new System.Drawing.Size(150, 22);
            this.menuLine.Text = "선그리기";
            this.menuLine.Click += new System.EventHandler(this.menuLine_Click);
            // 
            // menuRect
            // 
            this.menuRect.Name = "menuRect";
            this.menuRect.Size = new System.Drawing.Size(150, 22);
            this.menuRect.Text = "사각형 그리기";
            this.menuRect.Click += new System.EventHandler(this.menuRect_Click);
            // 
            // menuCircle
            // 
            this.menuCircle.Name = "menuCircle";
            this.menuCircle.Size = new System.Drawing.Size(150, 22);
            this.menuCircle.Text = "원그리기";
            this.menuCircle.Click += new System.EventHandler(this.menuCircle_Click);
            // 
            // menuText
            // 
            this.menuText.Name = "menuText";
            this.menuText.Size = new System.Drawing.Size(150, 22);
            this.menuText.Text = "문자 입력";
            this.menuText.Click += new System.EventHandler(this.menuText_Click);
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(147, 6);
            // 
            // menuErase
            // 
            this.menuErase.Name = "menuErase";
            this.menuErase.Size = new System.Drawing.Size(150, 22);
            this.menuErase.Text = "모두 지우기";
            this.menuErase.Click += new System.EventHandler(this.menuErase_Click);
            // 
            // 보기ToolStripMenuItem
            // 
            this.보기ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuColor});
            this.보기ToolStripMenuItem.Name = "보기ToolStripMenuItem";
            this.보기ToolStripMenuItem.Size = new System.Drawing.Size(43, 20);
            this.보기ToolStripMenuItem.Text = "보기";
            // 
            // menuColor
            // 
            this.menuColor.Name = "menuColor";
            this.menuColor.Size = new System.Drawing.Size(98, 22);
            this.menuColor.Text = "색상";
            // 
            // ㄷToolStripMenuItem
            // 
            this.ㄷToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuTestSine});
            this.ㄷToolStripMenuItem.Name = "ㄷToolStripMenuItem";
            this.ㄷToolStripMenuItem.Size = new System.Drawing.Size(79, 20);
            this.ㄷToolStripMenuItem.Text = "동작테스트";
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.sbLabel1,
            this.sbLabel2,
            this.sbLabel3,
            this.sbLabel4});
            this.statusStrip1.Location = new System.Drawing.Point(0, 426);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(800, 24);
            this.statusStrip1.TabIndex = 1;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // sbLabel1
            // 
            this.sbLabel1.AutoSize = false;
            this.sbLabel1.BackColor = System.Drawing.Color.IndianRed;
            this.sbLabel1.BorderSides = System.Windows.Forms.ToolStripStatusLabelBorderSides.Right;
            this.sbLabel1.BorderStyle = System.Windows.Forms.Border3DStyle.Etched;
            this.sbLabel1.Name = "sbLabel1";
            this.sbLabel1.Size = new System.Drawing.Size(100, 19);
            this.sbLabel1.Text = " ";
            // 
            // sbLabel2
            // 
            this.sbLabel2.AutoSize = false;
            this.sbLabel2.BackColor = System.Drawing.Color.Fuchsia;
            this.sbLabel2.BorderSides = System.Windows.Forms.ToolStripStatusLabelBorderSides.Right;
            this.sbLabel2.BorderStyle = System.Windows.Forms.Border3DStyle.Etched;
            this.sbLabel2.Name = "sbLabel2";
            this.sbLabel2.Size = new System.Drawing.Size(100, 19);
            this.sbLabel2.Text = " ";
            // 
            // sbLabel3
            // 
            this.sbLabel3.AutoSize = false;
            this.sbLabel3.BackColor = System.Drawing.Color.DarkTurquoise;
            this.sbLabel3.BorderSides = System.Windows.Forms.ToolStripStatusLabelBorderSides.Right;
            this.sbLabel3.BorderStyle = System.Windows.Forms.Border3DStyle.Etched;
            this.sbLabel3.Name = "sbLabel3";
            this.sbLabel3.Size = new System.Drawing.Size(100, 19);
            this.sbLabel3.Text = " ";
            // 
            // sbLabel4
            // 
            this.sbLabel4.BackColor = System.Drawing.Color.Chartreuse;
            this.sbLabel4.BorderSides = System.Windows.Forms.ToolStripStatusLabelBorderSides.Right;
            this.sbLabel4.BorderStyle = System.Windows.Forms.Border3DStyle.Etched;
            this.sbLabel4.Name = "sbLabel4";
            this.sbLabel4.Size = new System.Drawing.Size(15, 19);
            this.sbLabel4.Text = " ";
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // Canvas
            // 
            this.Canvas.Dock = System.Windows.Forms.DockStyle.Fill;
            this.Canvas.Location = new System.Drawing.Point(0, 24);
            this.Canvas.Name = "Canvas";
            this.Canvas.Size = new System.Drawing.Size(800, 402);
            this.Canvas.TabIndex = 2;
            this.Canvas.TabStop = false;
            this.Canvas.Click += new System.EventHandler(this.Canvas_Click);
            this.Canvas.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Canvas_MouseDown);
            this.Canvas.MouseMove += new System.Windows.Forms.MouseEventHandler(this.Canvas_MouseMove);
            this.Canvas.MouseUp += new System.Windows.Forms.MouseEventHandler(this.Canvas_MouseUp);
            // 
            // menuTestSine
            // 
            this.menuTestSine.Name = "menuTestSine";
            this.menuTestSine.Size = new System.Drawing.Size(180, 22);
            this.menuTestSine.Text = "Sine Graph";
            this.menuTestSine.Click += new System.EventHandler(this.menuTestSine_Click);
            // 
            // frmPaint
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.Canvas);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "frmPaint";
            this.Text = "myPaint";
            this.MaximizedBoundsChanged += new System.EventHandler(this.frmPaint_ResizeEnd);
            this.MaximumSizeChanged += new System.EventHandler(this.frmPaint_ResizeEnd);
            this.ResizeEnd += new System.EventHandler(this.frmPaint_ResizeEnd);
            this.Resize += new System.EventHandler(this.frmPaint_Resize);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Canvas)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 파일ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem menuNew;
        private System.Windows.Forms.ToolStripMenuItem menuOpen;
        private System.Windows.Forms.ToolStripMenuItem menuSave;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem menuEnd;
        private System.Windows.Forms.ToolStripMenuItem 홈ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 보기ToolStripMenuItem;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.PictureBox Canvas;
        private System.Windows.Forms.ToolStripMenuItem menuDraw;
        private System.Windows.Forms.ToolStripMenuItem menuLine;
        private System.Windows.Forms.ToolStripMenuItem menuRect;
        private System.Windows.Forms.ToolStripMenuItem menuCircle;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem menuErase;
        private System.Windows.Forms.ToolStripMenuItem menuColor;
        private System.Windows.Forms.ToolStripMenuItem menuText;
        private System.Windows.Forms.ToolStripStatusLabel sbLabel1;
        private System.Windows.Forms.ToolStripStatusLabel sbLabel2;
        private System.Windows.Forms.ToolStripStatusLabel sbLabel3;
        private System.Windows.Forms.ToolStripStatusLabel sbLabel4;
        private System.Windows.Forms.ToolStripMenuItem ㄷToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem menuTestSine;
    }
}

