#ifndef DPREMAINWINDOW_H
#define DPREMAINWINDOW_H

#include <QMainWindow>
#include "settings.h"
#include "imagelibchooser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DPreMainWindow; }
QT_END_NAMESPACE

class DPreMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    DPreMainWindow(QWidget *parent = nullptr);
    ~DPreMainWindow();

private slots:
    void on_pushButton_NextDone_clicked();

    void on_tabWidgetMain_currentChanged(int index);

    void on_listOfImageLibs_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    Ui::DPreMainWindow *ui;
    Settings * _settings;
    ImageLibChooser *_imagelibchooser;

    void PopulateImageLibList();

    bool _copyImageLibFiles;
    QString _imageLibName;
};
#endif // DPREMAINWINDOW_H
