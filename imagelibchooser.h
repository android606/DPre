#ifndef IMAGELIBCHOOSER_H
#define IMAGELIBCHOOSER_H
#include <QListWidget>
#include <QListWidgetItem>
#include <QTextEdit>
#include <QString>
#include <QDir>

class ImageLibChooser
{

public:
    ImageLibChooser();

    void setImageLibRootPath(QDir);
    void setImageLibSelected(QString);
    void setImageDestPath(QDir);
    void setLogWidget(QTextEdit *);
    void setUIWidget(QWidget *);
    int TakeAllActions(); //Performs any pending actions (copying files), outputs the progress to the textbox

private:
    QDir _ImageLibRootPath; //Path to location of image libraries on filesystem ("S:/Image_Libraries")
    QString _ImageLibSelected; //Name of image library selected by user ("b1234567_ab-cd")
    QDir _ImageDestPath; //Path where images will be copied to
    QTextEdit *_LogWidget; //Widget to which we will output logging info
    bool _hasImagesToCopy = false; //true if the Chooser needs to copy images based on user input

    int CopyImages(); //Copy the actual images from the library folder to the output folder
};

#endif // IMAGELIBCHOOSER_H
