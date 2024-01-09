namespace WinFormTest01_Base
{
    partial class frmBase
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
            this.tbMemo = new System.Windows.Forms.TextBox();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.Label1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.Label2 = new System.Windows.Forms.ToolStripStatusLabel();
            this.Label3 = new System.Windows.Forms.ToolStripStatusLabel();
            this.serviceController1 = new System.ServiceProcess.ServiceController();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.파일ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuNew = new System.Windows.Forms.ToolStripMenuItem();
            this.menuOpen = new System.Windows.Forms.ToolStripMenuItem();
            this.menuSave = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.menuExit = new System.Windows.Forms.ToolStripMenuItem();
            this.편집ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuFind = new System.Windows.Forms.ToolStripMenuItem();
            this.menuReplace = new System.Windows.Forms.ToolStripMenuItem();
            this.보기ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuFont = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripSeparator();
            this.menuANSI = new System.Windows.Forms.ToolStripMenuItem();
            this.menuUTF = new System.Windows.Forms.ToolStripMenuItem();
            this.도움말ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuAbout = new System.Windows.Forms.ToolStripMenuItem();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.btnOpen = new System.Windows.Forms.Button();
            this.statusStrip1.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tbMemo
            // 
            this.tbMemo.AcceptsReturn = true;
            this.tbMemo.Location = new System.Drawing.Point(24, 26);
            this.tbMemo.Multiline = true;
            this.tbMemo.Name = "tbMemo";
            this.tbMemo.Size = new System.Drawing.Size(439, 381);
            this.tbMemo.TabIndex = 0;
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Label1,
            this.Label2,
            this.Label3});
            this.statusStrip1.Location = new System.Drawing.Point(0, 462);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(680, 22);
            this.statusStrip1.TabIndex = 1;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // Label1
            // 
            this.Label1.AutoSize = false;
            this.Label1.BackColor = System.Drawing.Color.RosyBrown;
            this.Label1.Name = "Label1";
            this.Label1.Size = new System.Drawing.Size(70, 17);
            // 
            // Label2
            // 
            this.Label2.AutoSize = false;
            this.Label2.BackColor = System.Drawing.Color.LightGreen;
            this.Label2.Name = "Label2";
            this.Label2.Size = new System.Drawing.Size(70, 17);
            // 
            // Label3
            // 
            this.Label3.AutoSize = false;
            this.Label3.BackColor = System.Drawing.Color.Turquoise;
            this.Label3.Name = "Label3";
            this.Label3.Size = new System.Drawing.Size(70, 17);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.파일ToolStripMenuItem,
            this.편집ToolStripMenuItem,
            this.보기ToolStripMenuItem,
            this.도움말ToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(680, 24);
            this.menuStrip1.TabIndex = 3;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 파일ToolStripMenuItem
            // 
            this.파일ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuNew,
            this.menuOpen,
            this.menuSave,
            this.toolStripMenuItem1,
            this.menuExit});
            this.파일ToolStripMenuItem.Name = "파일ToolStripMenuItem";
            this.파일ToolStripMenuItem.Size = new System.Drawing.Size(43, 20);
            this.파일ToolStripMenuItem.Text = "파일";
            // 
            // menuNew
            // 
            this.menuNew.Name = "menuNew";
            this.menuNew.Size = new System.Drawing.Size(103, 22);
            this.menuNew.Text = "New";
            // 
            // menuOpen
            // 
            this.menuOpen.Name = "menuOpen";
            this.menuOpen.Size = new System.Drawing.Size(103, 22);
            this.menuOpen.Text = "Open";
            this.menuOpen.Click += new System.EventHandler(this.menuOpen_Click);
            // 
            // menuSave
            // 
            this.menuSave.Name = "menuSave";
            this.menuSave.Size = new System.Drawing.Size(103, 22);
            this.menuSave.Text = "Save";
            this.menuSave.Click += new System.EventHandler(this.menuSave_Click);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(100, 6);
            // 
            // menuExit
            // 
            this.menuExit.Name = "menuExit";
            this.menuExit.Size = new System.Drawing.Size(103, 22);
            this.menuExit.Text = "Exit";
            // 
            // 편집ToolStripMenuItem
            // 
            this.편집ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuFind,
            this.menuReplace});
            this.편집ToolStripMenuItem.Name = "편집ToolStripMenuItem";
            this.편집ToolStripMenuItem.Size = new System.Drawing.Size(43, 20);
            this.편집ToolStripMenuItem.Text = "편집";
            // 
            // menuFind
            // 
            this.menuFind.Name = "menuFind";
            this.menuFind.Size = new System.Drawing.Size(110, 22);
            this.menuFind.Text = "찾기";
            // 
            // menuReplace
            // 
            this.menuReplace.Name = "menuReplace";
            this.menuReplace.Size = new System.Drawing.Size(110, 22);
            this.menuReplace.Text = "바꾸기";
            // 
            // 보기ToolStripMenuItem
            // 
            this.보기ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuFont,
            this.toolStripMenuItem2,
            this.menuANSI,
            this.menuUTF});
            this.보기ToolStripMenuItem.Name = "보기ToolStripMenuItem";
            this.보기ToolStripMenuItem.Size = new System.Drawing.Size(43, 20);
            this.보기ToolStripMenuItem.Text = "보기";
            // 
            // menuFont
            // 
            this.menuFont.Name = "menuFont";
            this.menuFont.Size = new System.Drawing.Size(106, 22);
            this.menuFont.Text = "글꼴";
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(103, 6);
            // 
            // menuANSI
            // 
            this.menuANSI.Name = "menuANSI";
            this.menuANSI.Size = new System.Drawing.Size(106, 22);
            this.menuANSI.Text = "ANSI";
            this.menuANSI.Click += new System.EventHandler(this.menuANSI_Click);
            // 
            // menuUTF
            // 
            this.menuUTF.Name = "menuUTF";
            this.menuUTF.Size = new System.Drawing.Size(106, 22);
            this.menuUTF.Text = "UTF-8";
            this.menuUTF.Click += new System.EventHandler(this.menuUTF_Click);
            // 
            // 도움말ToolStripMenuItem
            // 
            this.도움말ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuAbout});
            this.도움말ToolStripMenuItem.Name = "도움말ToolStripMenuItem";
            this.도움말ToolStripMenuItem.Size = new System.Drawing.Size(55, 20);
            this.도움말ToolStripMenuItem.Text = "도움말";
            // 
            // menuAbout
            // 
            this.menuAbout.Name = "menuAbout";
            this.menuAbout.Size = new System.Drawing.Size(107, 22);
            this.menuAbout.Text = "About";
            this.menuAbout.Click += new System.EventHandler(this.menuAbout_Click);
            // 
            // btnOpen
            // 
            this.btnOpen.BackColor = System.Drawing.Color.DeepSkyBlue;
            this.btnOpen.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.btnOpen.Location = new System.Drawing.Point(501, 47);
            this.btnOpen.Name = "btnOpen";
            this.btnOpen.Size = new System.Drawing.Size(138, 51);
            this.btnOpen.TabIndex = 2;
            this.btnOpen.Text = "Open";
            this.btnOpen.UseVisualStyleBackColor = false;
            this.btnOpen.Click += new System.EventHandler(this.btnOpen_Click);
            // 
            // frmBase
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(680, 484);
            this.Controls.Add(this.btnOpen);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.menuStrip1);
            this.Controls.Add(this.tbMemo);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "frmBase";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Note";
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox tbMemo;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.ServiceProcess.ServiceController serviceController1;
        private System.Windows.Forms.Button btnOpen;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 파일ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem menuNew;
        private System.Windows.Forms.ToolStripMenuItem menuOpen;
        private System.Windows.Forms.ToolStripMenuItem menuSave;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem menuExit;
        private System.Windows.Forms.ToolStripMenuItem 편집ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem menuFind;
        private System.Windows.Forms.ToolStripMenuItem menuReplace;
        private System.Windows.Forms.ToolStripMenuItem 보기ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem menuFont;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem menuANSI;
        private System.Windows.Forms.ToolStripMenuItem menuUTF;
        private System.Windows.Forms.ToolStripMenuItem 도움말ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem menuAbout;
        private System.Windows.Forms.ToolStripStatusLabel Label1;
        private System.Windows.Forms.ToolStripStatusLabel Label2;
        private System.Windows.Forms.ToolStripStatusLabel Label3;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
    }
}

