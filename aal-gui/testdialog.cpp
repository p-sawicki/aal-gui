#include "testdialog.h"
#include "ui_testdialog.h"

TestDialog::TestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestDialog)
{
    ui->setupUi(this);
    ui->loadingLabel->setVisible(false);
    QtCharts::QChart *chart = new QtCharts::QChart();
    chartView = new QtCharts::QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->horizontalLayout_3->addWidget(chartView);
}

TestDialog::~TestDialog()
{
    delete ui;
}

void TestDialog::on_startPushButton_clicked()
{
    ui->loadingLabel->setVisible(true);

    int min = ui->minSizeSpinBox->value();
    int max = ui->maxSizeSpinBox->value();
    int step = ui->stepSpinBox->value();
    int repeats = ui->repeatsSpinBox->value();
    int selectedAlgorithm = ui->comboBox->currentIndex();
    series.push_back(new QtCharts::QLineSeries(this));
    switch (selectedAlgorithm) {
    case 0:
        series.back()->setName("Dynamic programming");
        break;
    case 1:
        series.back()->setName("Graph-based");
        break;
    case 2:
        series.back()->setName("Brute force");
        break;
    }
    workers.push_back(new TestRunner(min, max, step, repeats, selectedAlgorithm, this));
    connect(workers.back(), &TestRunner::updated, this, &TestDialog::updateGraph);
    connect(workers.back(), &TestRunner::finished, this, &TestDialog::onFinished);

    workers.back()->start();
}

void TestDialog::updateGraph(TestRunner *runner, int bricks, double time) {
    QtCharts::QLineSeries *seriesToUpdate = series[workers.indexOf(runner)];
    if (chartView->chart()->series().contains(seriesToUpdate))
        chartView->chart()->removeSeries(seriesToUpdate);
    seriesToUpdate->append(bricks, time);
    chartView->chart()->addSeries(seriesToUpdate);

    chartView->chart()->createDefaultAxes();
    chartView->chart()->axes(Qt::Horizontal).front()->setTitleText("Amount of bricks");
    chartView->chart()->axes(Qt::Vertical).front()->setTitleText("Time [s]");
}

void TestDialog::on_stopPushButton_clicked()
{
    for (TestRunner *runner : workers) {
        runner->cancel();
    }
}

void TestDialog::onFinished() {
    for (TestRunner *runner : workers) {
        if (!runner->isFinished())
            return;
    }
    ui->loadingLabel->setVisible(false);
}
