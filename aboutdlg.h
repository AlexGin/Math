#ifndef ABOUTDLG_H
#define ABOUTDLG_H

#include <QtWidgets/QDialog>

namespace Ui
{
    class AboutDlg;
}

class AboutDlg : public QDialog
{
    Q_OBJECT
public:
    AboutDlg(QWidget *parent = 0);
    ~AboutDlg();
    void ShowTimeOfGeneration();
protected:
    void changeEvent(QEvent *e);

private:
    Ui::AboutDlg *m_ui;
};

#endif // ABOUTDLG_H
