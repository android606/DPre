#include "imagelibchooser.h"
#include <QDebug>

ImageLibChooser::ImageLibChooser()
{
}

void ImageLibChooser::setLogWidget(QTextEdit *logwidget)
{
    _LogWidget = logwidget;
}


void ImageLibChooser::setImageLibRootPath(QDir path)
{
    _ImageLibRootPath = path;
}

void ImageLibChooser::setImageLibSelected(QString libname)
{
    _ImageLibSelected = libname;
    _hasImagesToCopy = true;
}

void ImageLibChooser::setImageDestPath(QDir path)
{
    _ImageDestPath = path;
}

//Copies image files from library to extract folder, if needed.
//Returns non-zero on failure
int ImageLibChooser::TakeAllActions()
{

    //If the first item in the list of image libs is selected, don't
    //do anything except say in the log that we're not doing anything.
    if(_ImageLibSelected == "")
    {
        //Don't copy images, output a message to the log
        _LogWidget->append("<hr/><b>Image Library Chooser</b> has no actions to take.");
        return 0;
    }
    else
    {
        //Copy images, output messages to the log
        _LogWidget->append("<hr/><b>Image Library Chooser</b> has images to process...");
        CopyImages();

        return 0;
    }

    return 0;
}

int ImageLibChooser::CopyImages()
{
    QDir SourceFolder(_ImageLibRootPath.filePath(_ImageLibSelected)); //Concatenate selected image lib folder name to complete path

    QDir DestFolder(_ImageDestPath);
    qDebug() << SourceFolder.canonicalPath();

    SourceFolder.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    QStringList imagesFilters;
    imagesFilters << "*.ai"
             << "*.bmp"
             << "*.emf"
             << "*.eps"
             << "*.gif"
             << "*.heif"
             << "*.jpg"
             << "*.jpeg"
             << "*.jpf"
             << "*.pdf"
             << "*.png"
             << "*.psd"
             << "*.raw"
             << "*.svg"
             << "*.tif"
             << "*.tiff"
             << "*.webp"
             << "*.wmf";
    int countallfiles = SourceFolder.count();
    SourceFolder.setNameFilters(imagesFilters);
    int countimagefiles = SourceFolder.count();

    _LogWidget->append("Source: " + SourceFolder.path());
    _LogWidget->append("Destination: " + DestFolder.path());
    _LogWidget->append(QString::number(countimagefiles) + " image files to copy. ("
                      + QString::number(countallfiles - countimagefiles) + " non-image files ignored.)");

    //Quick sanity check
    if(!DestFolder.exists())
    {
        _LogWidget->append("<b>ERROR:</b> Destination folder '"
                           + DestFolder.path()
                           + "' does not exist! Sorry, I can't continue...");
        return 1;
    }
    //Sanity check passed, so try to copy some files
    else
    {
        //Copy each file from source to dest
        QFileInfoList filelist = SourceFolder.entryInfoList();
        for(int i=0; i < filelist.count(); i++)
        {
            _LogWidget->append("\n Copy:" + filelist.at(i).canonicalFilePath());
            _LogWidget->append("   to: " + DestFolder.canonicalPath() + "/" + filelist.at(i).fileName());

            QFile sourcefile(filelist.at(i).canonicalFilePath());
            QFile destfile(DestFolder.canonicalPath() + "/" + filelist.at(i).fileName());
            //If dest file exists, delete it
            if(destfile.exists() && destfile.remove() == false)
            {
                _LogWidget->append(" FAILED: Destination file already exists but could not be deleted ("
                                       + destfile.errorString()
                                       +")");
            }

            bool result = sourcefile.copy(destfile.fileName());
            if(result == false)
            {
                _LogWidget->append("     FAILED: " + sourcefile.errorString());
            }
        }
    }

    return 0;
}
