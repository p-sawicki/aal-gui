#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QFileDialog>
#include <QMovie>
#include "brickstablemodel.h"
#include "brickinfodialog.h"
#include "generatebricksdialog.h"
#include "testdialog.h"
#include "aal/inc/brick.h"
#include "aal/inc/dp.h"
#include "aal/inc/graph.h"
#include "aal/inc/bf.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addBrick(const Brick & brick);

private slots:
    void onSelectionChanged();
    void onSolved(double depth, double time);

    void on_actionNewBrick_triggered();

    void on_actionDeleteBrick_triggered();

    void on_actionImportBricks_triggered();

    void on_actionExportBricks_triggered();

    void on_actionGenerate_triggered();

    void on_actionDynamic_Programming_triggered();

    void on_actionGraph_based_Algorithm_triggered();

    void on_actionBrute_Force_triggered();

    void on_unsolveButton_clicked();

    void on_actionTest_triggered();

private:
    void solve();

    Ui::MainWindow *ui;
    BricksTableModel *bricks;
};
#endif // MAINWINDOW_H
