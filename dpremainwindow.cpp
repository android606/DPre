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
    // If the button text is "Close", just close and exit
    if(ui->pushButton_NextDone->text() == "Close")
    {
        QApplication::quit();
    }

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
        updateNextButton();
    }

}

void DPreMainWindow::updateNextButton()
{
    int selectedTab = ui->tabWidgetMain->currentIndex();
    /*-If we're at the last tab, and there are things to do,
     * change the button text to "Make Final Changes"
     *-If we're at the last tab, and there are NOT things to do,
     * change the button text to "Close"
     *
     *-Otherwise, change the button text to "Next"
     */
    if((selectedTab == ui->tabWidgetMain->count() - 1) & !(_imagelibchooser->HasActionsToTake()))
    {
        ui->pushButton_NextDone->setText("Close");
    }
    else if((selectedTab == ui->tabWidgetMain->count() - 1) & (_imagelibchooser->HasActionsToTake()))
    {
        ui->pushButton_NextDone->setText("Make Final Changes");
    }
    else
    {
        ui->pushButton_NextDone->setText("Next");
    }

}

void DPreMainWindow::on_tabWidgetMain_currentChanged(int index)
{
    (void)index;

    updateNextButton();
}



/*
 * IMAGE LIBRARY SELECTOR
 */
void DPreMainWindow::PopulateImageLibList()
{
    //Populate list of image libraries so the user has something to choose from
    ui->listOfImageLibs->clear();
    ui->listOfImageLibs->addItems(_imagelibchooser->getImageLibList());

    //Select first item in the list
    ui->listOfImageLibs->setCurrentRow(0);
}

void DPreMainWindow::on_listOfImageLibs_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    //unused parameters
    (void)current;
    (void)previous;

    //Tell ImageLibChooser which lib the user selected in the list
    _imagelibchooser->setImageLibSelected(ui->listOfImageLibs->currentRow());
}
