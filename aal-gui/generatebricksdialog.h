#ifndef GENERATEBRICKSDIALOG_H
#define GENERATEBRICKSDIALOG_H

#include <QDialog>

namespace Ui {
class GenerateBricksDialog;
}

class GenerateBricksDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GenerateBricksDialog(QWidget *parent = nullptr);
    ~GenerateBricksDialog();
signals:
    void accepted(int amount, double min, double max);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::GenerateBricksDialog *ui;
};

#endif // GENERATEBRICKSDIALOG_H
