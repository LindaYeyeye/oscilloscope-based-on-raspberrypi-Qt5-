#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include "qDebug.h"
#include "xcustomplot.h"
#include "mytracer.h"

#include <QMouseEvent>
#include <QMap>
#include <QMouseEvent>
#include <QDebug>
#include <QHBoxLayout>
#include <QSet>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    ui->setupUi(this);
    //run，stop,read三个按键
    QPushButton *Run = new QPushButton("Run",this);
    Run->setGeometry(50,10,60,40);
    Run->setFont((QFont("Times",18,QFont::Bold)));
    QPushButton *Read = new QPushButton("Read",this);
    Read->setGeometry(350,10,60,40);
    Read->setFont((QFont("Times",18,QFont::Bold)));
    QPushButton *Stop = new QPushButton("Stop",this);
    Stop->setGeometry(200,10,60,40);
    Stop->setFont((QFont("Times",18,QFont::Bold)));
    connect(Run,SIGNAL(clicked()),this,SLOT(Run_clicked()));//这里要实现，按住按钮，开始运行的功能,读取文件内容
    connect(Stop,SIGNAL(clicked()),this,SLOT(Stop_clicked()));//这里要实现，按住按钮，暂停画图
    connect(Read,SIGNAL(clicked()),this,SLOT(Read_clicked()));//


}
void MainWindow::plotcurve()
{
            //绘图中的基本设置
             basicsetting();
             movingplot();
}
void MainWindow::Read_clicked()
{
  QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Excel file"),
                                                        "./",
                                                        tr("Files (*.csv)"));
        if(!fileName.isEmpty())
        {
            x.clear(); //x的值
            y.clear();  //y的值

            QFile file(fileName); // 新建QFile对象
            if (!file.open(QFile::ReadOnly | QFile::Text))
            {
                QMessageBox::warning(this, tr("打开csv文件"),
                                     tr("无法读取文件 %1:\n%2.")
                                     .arg(fileName).arg(file.errorString()));
                return ;
            }
            QTextStream in(&file); // 新建文本流对象
            QStringList list;//用于存储逐行数据

            //逐行读取*.csv数据并将每列分别存入x、y数组中
            while(!in.atEnd())
            {
                QString fileLine=in.readLine();//逐行读取数据
                list=fileLine.split(",");//一行中的单元格以，区分
                qDebug()<<"list="<<list;

                double A = (list.at(0)).toDouble();//获取该行第1个单元格内容
                x.append(A);

                double B = (list.at(1)).toDouble();//获取该行第2个单元格内容
                y.append(B);
            }
            file.close();

}}
void MainWindow::Stop_clicked()
{
        enabled=false;//关闭使能，令读取数据并plot跳出循环
}
void MainWindow::Run_clicked()
{
        enabled=true;//开启使能，令读取数据并plot跳出循环
        plotcurve();//绘制图像
}
void MainWindow::basicsetting()//画图时的基本设施
{

    XCustomPlot *customPlot = new XCustomPlot();
    ui->customPlot ->showTracer(true);

    // add title layout element:
     ui->customPlot->plotLayout()->insertRow(0);
    ui-> customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(customPlot, "标题", QFont("黑体", 12, QFont::Bold)));

    ui-> customPlot->legend->setVisible(true);
    QFont legendFont = font();  // start out with MainWindow's font..
    legendFont.setPointSize(9); // and make a bit smaller for legend
     ui->customPlot->legend->setFont(legendFont);
     ui->customPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));
    // by default, the legend is in the inset layout of the main axis rect. So this is how we access it to change legend placement:
     ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignCenter);

    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

    ui->customPlot->addGraph(0);
    //下面可以实现静态绘图
    ui->customPlot->graph(0)->setPen(QPen(Qt::red)); // 第一条曲线颜色
    ui-> customPlot->xAxis->setLabel( "Time/s");
    ui-> customPlot->yAxis->setLabel( "Voltage/V");
    ui-> customPlot->xAxis->setVisible(true);
    ui-> customPlot->xAxis->setTickLabels(true);
    ui-> customPlot->graph(0)->rescaleAxes();
    ui-> customPlot->setInteractions(QCP::iRangeDrag           //< 可平移
                          | QCP::iRangeZoom         //< 可滚轮缩放
                          | QCP::iSelectPlottables  //< 可选中曲线
                          | QCP::iSelectLegend);    //< 可选中图例

}
void MainWindow::movingplot()
 {
    QVector<double> sx_vec,xAxis_vec;// 存放数据的容器
     int m_chartPoint_counter=0;  //  计数器  一直增加 来一条数据增加一下 控制x轴前进 实现动态效果
     //这时容器里面还没200个点 所有一直向里面存
     for(m_chartPoint_counter;(m_chartPoint_counter<y.size())&&(enabled==true);m_chartPoint_counter++)
     {

         if(m_chartPoint_counter<20)
         {
             xAxis_vec.append(x[m_chartPoint_counter]);//x轴的范围数据
             sx_vec.append(y[m_chartPoint_counter]);
             //设置范围正好 能显示当前点
             ui-> customPlot->xAxis->setRange(0,xAxis_vec.at(xAxis_vec.size()-1));
         }
         else
         {
             //容器数据现在是正好10个  把第一个出栈  把第11个入栈  正好还是10个数据
             sx_vec.removeFirst();
             xAxis_vec.removeFirst();
             //入栈
             xAxis_vec.append(x[m_chartPoint_counter]);
             sx_vec.append(y[m_chartPoint_counter]);
             //设置范围正好 能显示当前点
           ui-> customPlot->xAxis->setRange(xAxis_vec.at(0),xAxis_vec.at(
                                          xAxis_vec.size()-1));
         }
         //绘制部分，的设置和延时
         {ui-> customPlot->yAxis->rescale(true);
           //设置数据
         ui-> customPlot->graph()->setData(xAxis_vec,sx_vec);
           //重绘制
           //设置绘图延时，同时不阻塞线程
                   QTime delayTime = QTime::currentTime().addMSecs(300);
                  while( QTime::currentTime()<delayTime)
                  QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
          ui-> customPlot->replot();
         }
 }


}

