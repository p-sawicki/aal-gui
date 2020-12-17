#ifndef TESTDIALOG_H
#define TESTDIALOG_H

#include <QDialog>
#include <QThread>
#include <sstream>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include "testrunner.h"
#include "aal/inc/gen.h"
#include "aal/inc/dp.h"
#include "aal/inc/graph.h"
#include "aal/inc/bf.h"

namespace Ui {
class TestDialog;
}

class TestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TestDialog(QWidget *parent = nullptr);
    ~TestDialog();

private slots:
    void on_startPushButton_clicked();

    void on_stopPushButton_clicked();

    void updateGraph(TestRunner *runner, int bricks, double time);
    void onFinished();

private:
    Ui::TestDialog *ui;
    QVector<TestRunner*> workers;
    QVector<QtCharts::QLineSeries*> series;
    QtCharts::QChartView *chartView;
};

#endif // TESTDIALOG_H
