#define _USE_MATH_DEFINES
#include <math.h>

#include <string>
#include <sstream>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "aboutdlg.h"

#include <QMessageBox>

#define MODE_NATIVE_CALCULATE  0
#define MODE_FLOATING_POINT    1
#define MODE_TRIGONOMERTY      2
// see:
// http://www.developer.com/java/article.php/3856906/Java-vs-C-The-Performance-Showdown.htm
// http://www.developer.com/java/article.php/10922_3856906_2/Java-vs-C-The-Performance-Showdown.htm
// and:
// http://en.cppreference.com/w/cpp/chrono/c/time

const int N_MULTIPLY = 10000000;
const int N_GENERATED = 1000;

int randoms[N_GENERATED];
int outputs[N_GENERATED];

double randDbl[N_GENERATED];
double outpDbl[N_GENERATED];

int g_iMode;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->mainToolBar->addAction(ui->actionTest_Math_1);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actionTest_Math_2);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actionTest_Math_3);
    ui->mainToolBar->addSeparator();

    ui->mainToolBar->addAction(ui->actionExit);

	ui->progressBar->setAlignment(Qt::AlignCenter); // Set percent indicator to center
	ui->pushBtnStart->setEnabled(false);

    // see:
    // http://stackoverflow.com/questions/24254006/rightclick-event-in-qt-to-open-a-context-menu
    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
                this, SLOT(ShowContextMenu(const QPoint &)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// see:
// http://stackoverflow.com/questions/24254006/rightclick-event-in-qt-to-open-a-context-menu
void MainWindow::ShowContextMenu(const QPoint &pos)
{
   QMenu contextMenu("Context menu", this);

   // QAction action1("Remove Data Point", this);
   // connect(&action1, SIGNAL(triggered()), this, SLOT(removeDataPoint()));
   contextMenu.addAction(ui->actionTest_Math_1);
   contextMenu.addSeparator();
   contextMenu.addAction(ui->actionTest_Math_2);
   contextMenu.addSeparator();
   contextMenu.addAction(ui->actionTest_Math_3);
   contextMenu.addSeparator();
   contextMenu.addAction(ui->actionExit);

   contextMenu.exec(mapToGlobal(pos));
}

////////////////////////////////////////////////
void MainWindow::generate_randoms()
{
    for( int i = 0; i < N_GENERATED; i++ )
        randoms[i] = rand();
}

void MainWindow::nativeCompute()
{
   ui->labelMode->setText("Native Compute - start of perform...");

   ui->progressBar->setValue(2); // start position of progress-bar

   std::time_t timeStart = std::time(0);
   int result = 0;
   for(int i = 2; i < N_MULTIPLY; i++)
   {
      for( int j = 0; j < N_GENERATED; j++ )
      {
         result = randoms[j] * i;
         result++;
         outputs[j] = result;
      }
      if (!(i % 100000))
      {
          int val = ui->progressBar->value();
          ui->progressBar->setValue(++val);
      }
   }
   std::time_t timeStop = std::time(0);
   ui->labelMode->setText("Native Compute - complete!");

   std::string strMode("Native Compute");
   ShowDuration(timeStart, timeStop, strMode);
   ui->pushBtnStart->setEnabled(false);
}
///////////////////////////////////////////////////
void MainWindow::generate_dbl_randoms()
{
    for( int i = 0; i < N_GENERATED; i++ )
        randDbl[i] = double(1.11 * (double)rand());
}

void MainWindow::nativeComputeDbl() // Floating Point
{
   ui->labelMode->setText("Floating Point - start of perform...");

   ui->progressBar->setValue(2); // start position of progress-bar

   std::time_t timeStart = std::time(0);
   double resultDbl = 0.0;
   for(int i = 2; i < N_MULTIPLY; i++)
   {
      for( int j = 0; j < N_GENERATED; j++ )
      {
         double dbMult = (double)(i * 1.1);
         resultDbl = randDbl[j] * dbMult;
         resultDbl += 1.555;
         outpDbl[j] = resultDbl;
      }
      if (!(i % 100000))
      {
          int val = ui->progressBar->value();
          ui->progressBar->setValue(++val);
      }
   }
   std::time_t timeStop = std::time(0);
   ui->labelMode->setText("Floating Point - complete!");

   std::string strMode("Floating Point");
   ShowDuration(timeStart, timeStop, strMode);
   ui->pushBtnStart->setEnabled(false);
}
///////////////////////////////////////////////////

void MainWindow::nativeComputeTrg() // Trigonometry
{
   ui->labelMode->setText("Trigonometry - start of perform...");

   ui->progressBar->setValue(2); // start position of progress-bar

   std::time_t timeStart = std::time(0);
   double resultDbl = 0.0;    
   for(int i = 2; i < N_MULTIPLY; i++)
   {
      for( int j = 0; j < N_GENERATED; j++ )
      {
         double dbMult = (double)(i * 2 * M_PI);
         resultDbl = randDbl[j] + sin(dbMult);
         resultDbl += 0.375;
         outpDbl[j] = resultDbl;
      }
      if (!(i % 100000))
      {
          int val = ui->progressBar->value();
          ui->progressBar->setValue(++val);
      }
   }
   std::time_t timeStop = std::time(0);
   ui->labelMode->setText("Trigonometry - complete!");

   std::string strMode("Trigonometry");
   ShowDuration(timeStart, timeStop, strMode);
   ui->pushBtnStart->setEnabled(false);
}

void MainWindow::ShowDuration(std::time_t t1, std::time_t t2, std::string& sMode)
{
    std::time_t tDuration = t2 - t1;
    std::stringstream ss;
    ss << "Duration = " << tDuration << " sec " << "(mode: " << sMode << ").";
    std::string sDur = ss.str();

    QString qsDur(sDur.c_str());
    ui->labelTime->setText(qsDur);
}

void  MainWindow::PrepareCalculate(int iMode)
{
	ui->progressBar->reset();

    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);

    switch (iMode)
    {
        case MODE_NATIVE_CALCULATE:
            generate_randoms();
            ui->labelMode->setText("Native Compute");
            break;
        case MODE_FLOATING_POINT:
            generate_dbl_randoms();
            ui->labelMode->setText("Floating Point");
            break;
        case MODE_TRIGONOMERTY:
            generate_dbl_randoms();
            ui->labelMode->setText("Trigonometry");
            break;
    }

	ui->pushBtnStart->setEnabled(true);
}

void MainWindow::MathCalculate(int iMode)
{
    switch (iMode)
    {
        case MODE_NATIVE_CALCULATE:
            nativeCompute();
            break;

        case MODE_FLOATING_POINT:
            nativeComputeDbl();
            break;

        case MODE_TRIGONOMERTY:
            nativeComputeTrg();
            break;
    }
}

void MainWindow::showPrepareResult()
{
    QMessageBox msgBox;

    msgBox.setText("Preparing array - array ready!!!");
    msgBox.setInformativeText("PrepareCalculate completed.");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);

    msgBox.exec();
}

void MainWindow::on_actionTest_Math_1_triggered()
{
    ::g_iMode = MODE_NATIVE_CALCULATE; // 0
    PrepareCalculate(::g_iMode);
    showPrepareResult();
}

void MainWindow::on_actionTest_Math_2_triggered()
{
    ::g_iMode = MODE_FLOATING_POINT; // 1
    PrepareCalculate(::g_iMode);
    showPrepareResult();
}

void MainWindow::on_actionTest_Math_3_triggered()
{
    ::g_iMode = MODE_TRIGONOMERTY; // 2
    PrepareCalculate(::g_iMode);
    showPrepareResult();
}

void MainWindow::on_pushBtnStart_clicked()
{
    MathCalculate(::g_iMode);
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}


void MainWindow::on_actionAbout_Math_triggered()
{
    AboutDlg dlg;

    dlg.exec();
}
