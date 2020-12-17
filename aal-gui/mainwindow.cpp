#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), bricks(new BricksTableModel(this))
{
    ui->setupUi(this);
    ui->bricksTableView->setModel(bricks);
    connect(ui->bricksTableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onSelectionChanged);
    connect(ui->actionClear, &QAction::triggered, bricks, &BricksTableModel::clearBricks);
    connect(bricks, &BricksTableModel::solved, this, &MainWindow::onSolved);
    connect(bricks, &BricksTableModel::solvingChanged, [this] (bool solving) {ui->actionDynamic_Programming->setEnabled(!solving);});
    connect(bricks, &BricksTableModel::solvingChanged, [this] (bool solving) {ui->actionGraph_based_Algorithm->setEnabled(!solving);});
    connect(bricks, &BricksTableModel::solvingChanged, [this] (bool solving) {ui->actionBrute_Force->setEnabled(!solving);});

    ui->loadingLabel->setMovie(new QMovie(":/loader.gif"));
}

MainWindow::~MainWindow()
{
    delete ui->loadingLabel->movie();
    delete ui;
}

void MainWindow::onSelectionChanged() {
    ui->actionDeleteBrick->setEnabled(!ui->bricksTableView->selectionModel()->selectedRows().empty());
}

void MainWindow::on_actionNewBrick_triggered()
{
    BrickInfoDialog *dialog = new BrickInfoDialog(this);
    dialog->setWindowTitle("Add a brick");
    connect(dialog, &BrickInfoDialog::accepted, bricks, &BricksTableModel::addBrick);
    dialog->exec();
}

void MainWindow::on_actionDeleteBrick_triggered()
{
    bricks->removeBricks(ui->bricksTableView->selectionModel()->selectedRows());
}

void MainWindow::on_actionImportBricks_triggered()
{
    bricks->import(QFileDialog::getOpenFileName());
}

void MainWindow::on_actionExportBricks_triggered()
{
    bricks->exportToFile(QFileDialog::getOpenFileName());
}

void MainWindow::on_actionGenerate_triggered()
{
    GenerateBricksDialog *dialog = new GenerateBricksDialog(this);
    connect(dialog, &GenerateBricksDialog::accepted, bricks, &BricksTableModel::generateBricks);
    dialog->exec();
}

void MainWindow::onSolved(double depth, double time) {
    ui->unsolveButton->setEnabled(true);
    ui->loadingLabel->movie()->stop();
    ui->loadingLabel->hide();
    ui->depthLabel->setText(QString("Depth: ") + QString::number(depth));
    ui->timeLabel->setText(QString("Time: ") + QString::number(time));
}

void MainWindow::solve() {
    ui->loadingLabel->show();
    ui->loadingLabel->movie()->start();
}

void MainWindow::on_actionDynamic_Programming_triggered()
{
    solve();
    bricks->solve(0);
}

void MainWindow::on_actionGraph_based_Algorithm_triggered()
{
    solve();
    bricks->solve(1);
}

void MainWindow::on_actionBrute_Force_triggered()
{
    solve();
    bricks->solve(2);
}

void MainWindow::on_unsolveButton_clicked()
{
    ui->unsolveButton->setEnabled(false);
    ui->depthLabel->setText("");
    ui->timeLabel->setText("");
    bricks->unsolve();
}

void MainWindow::on_actionTest_triggered()
{
    TestDialog *dialog = new TestDialog(this);
    dialog->show();
}
