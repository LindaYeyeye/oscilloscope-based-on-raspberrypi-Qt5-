#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QList>
#include <QMessageBox>
#include <QDateTime>
#include <QTimer>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include "qcustomplot.h"
#include "xcustomplot.h"
#include "multicurvesplot.h"
#include "mytracer.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void init();
    void plotcurve();
    void Run_clicked();
    void Read_clicked();
    void Stop_clicked();
    void basicsetting();
    void movingplot();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QVector<double> x;
    QVector<double> y;
    QCustomPlot *widget;
    QPushButton *Run;
    QPushButton *Stop;
    QPushButton *Read;
    bool enabled;
    XCustomPlot *customPlot ;

};

#endif // MAINWINDOW_H
