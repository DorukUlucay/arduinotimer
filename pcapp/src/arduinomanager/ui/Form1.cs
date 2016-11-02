using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ArduinoDriver;
using System.IO.Ports;

namespace ui
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            SerialPort port = new SerialPort("COM4", 9600);
            port.Open();
            port.Write(textBox1.Text);
            port.Close();
        }
    }
}
