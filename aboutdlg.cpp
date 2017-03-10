#include "aboutdlg.h"
#include "ui_aboutdlg.h"

AboutDlg::AboutDlg(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::AboutDlg)
{
    m_ui->setupUi(this);

    m_ui->labelDateInfo->setText("Math: time of generation:");
	ShowTimeOfGeneration();
}

AboutDlg::~AboutDlg()
{
    delete m_ui;
}

void AboutDlg::ShowTimeOfGeneration()
{
    char* pTime = new char[32];
    sprintf(pTime, "%s; %s", __DATE__, __TIME__);
	    
    QString qstr(pTime); 
    m_ui->labelDateTime->setText(qstr);
	   
    delete[] pTime;
}

void AboutDlg::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type())
    {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
