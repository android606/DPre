#ifndef DPREMAINWINDOW_H
#define DPREMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class DPreMainWindow; }
QT_END_NAMESPACE

class DPreMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    DPreMainWindow(QWidget *parent = nullptr);
    ~DPreMainWindow();

private:
    Ui::DPreMainWindow *ui;
};
#endif // DPREMAINWINDOW_H
