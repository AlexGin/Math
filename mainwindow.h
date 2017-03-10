#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <ctime>
#include <QtWidgets/QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void ShowDuration(std::time_t t1, std::time_t t2, std::string& sMode);
    void PrepareCalculate(int iMode);
    void MathCalculate(int iMode);
    void generate_randoms();
    void nativeCompute();
    void generate_dbl_randoms();
    void nativeComputeDbl(); // Floating Point
    void nativeComputeTrg(); // Trigonometry
    void showPrepareResult();
private:
    Ui::MainWindow *ui;

private slots:
    void on_actionAbout_Math_triggered();
    void on_actionTest_Math_3_triggered();
    void on_actionTest_Math_2_triggered();
    void on_actionTest_Math_1_triggered();
    void on_actionExit_triggered();
    void on_pushBtnStart_clicked();
    void ShowContextMenu(const QPoint &pos);
};

#endif // MAINWINDOW_H
