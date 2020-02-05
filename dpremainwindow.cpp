#include "dpremainwindow.h"
#include "ui_dpremainwindow.h"
#include "imagelibchooser.h"
#include <QDir>
#include <QDebug>

DPreMainWindow::DPreMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DPreMainWindow)
{

    ui->setupUi(this);

    _settings = Settings::getInstance();

    //Select first tab
    ui->tabWidgetMain->setCurrentIndex(0);


    //IMAGE LIBRARY CHOOSER INIT
    _imagelibchooser = new ImageLibChooser();
    _imagelibchooser->setImageLibRootPath(_settings->ImageLibraryRoot);
    _imagelibchooser->setImageDestPath(_settings->ImageDest);
    _imagelibchooser->setLogWidget(ui->OutputLog_textEdit);
    //Populate Image Library Root box and List o' libs
    ui->lineEdit_ImgLibRoot->setText(_settings->ImageLibraryRoot.canonicalPath());
    PopulateImageLibList();

}


DPreMainWindow::~DPreMainWindow()
{
    delete ui;
}


void DPreMainWindow::on_pushButton_NextDone_clicked()
{
    // Go to the next tab (unless we're already at the last tab)
    if(ui->tabWidgetMain->currentIndex() < ui->tabWidgetMain->count() - 1)
    {
        ui->tabWidgetMain->setCurrentIndex(ui->tabWidgetMain->currentIndex() + 1);
    }
    // Otherwise, we were already at the last tab, so the user clicked "Done"
    // That means we should actually do stuff.
    else
    {
        _imagelibchooser->TakeAllActions();
    }

}

void DPreMainWindow::on_tabWidgetMain_currentChanged(int index)
{
    // If we're at the last tab, change the button text to "Done"
    // Otherwise, change it to "Next"
    if(index == ui->tabWidgetMain->count() - 1)
    {
        ui->pushButton_NextDone->setText("Finish");
    }
    else
    {
        ui->pushButton_NextDone->setText("Next");
    }

}


/*
 * IMAGE LIBRARY SELECTOR
 */
void DPreMainWindow::PopulateImageLibList()
{
    ui->listOfImageLibs->clear();
    ui->listOfImageLibs->addItem("--Use Default Images--");

    QDir ImgLibRootDir;
    ImgLibRootDir.setPath(ui->lineEdit_ImgLibRoot->text());
    ImgLibRootDir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

    QFileInfoList fileinfolist = ImgLibRootDir.entryInfoList();
    for(int i = 0; i < fileinfolist.size(); i++)
    {
        QFileInfo fileinfo = fileinfolist.at(i);
        ui->listOfImageLibs->addItem(fileinfo.baseName());
    }

    //Select first item in the list
    ui->listOfImageLibs->setCurrentRow(0);
}


void DPreMainWindow::on_listOfImageLibs_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    //If an item index greater than 0 is selected, set the current 'selected image
    //library' to the item selected.
    //If the first item in the list (index 0) is selected, or if no item in the
    //list is selected at all (index -1), unset the current 'selected image library'.
    if(ui->listOfImageLibs->currentRow() > 0)
    {
        _imagelibchooser->setImageLibSelected(current->text());
    }
    else
    {
        _imagelibchooser->setImageLibSelected("");
    }

}
