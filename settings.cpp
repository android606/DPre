#include "settings.h"
#include <QCommandLineParser>
#include <QFileInfo>
#include <QDebug>

// Initialize static members here
Settings * Settings::_instance = 0;
QStringList Settings::_args = {};
QString Settings::DitamapFilePath(""); // ex "/Users/andrew/map12345/booklet.ditamap
QDir Settings::ImageLibraryRoot(""); // ex. "/Users/andrew/Image_Library"
QDir Settings::ImageDest(""); // ex. "/Users/andrew/map12345/images"

Settings::Settings(){}

Settings* Settings::getInstance()
{
    if(!_instance) {_instance = new Settings;}

    return _instance;
}

Settings* Settings::getInstance(QStringList args)
{
    _args = args;

    ParseCommandLine();

    return getInstance();
}

void Settings::ParseCommandLine()
{
    QCommandLineOption ditamap_opt("ditamap","Required: Full path to the DITA map file, images, and topics.","path_and_filename");
    QCommandLineOption imagesroot_opt("images","Specifies where your ditamap expects to find images. Default is to use folder where .ditamap file is located.","path");
    QCommandLineOption imglibroot_opt("image-libraries-root","Specifies the full path to the folder containing image libraries.","path");
    QCommandLineParser parser;
    parser.setApplicationDescription("Multi-tool for processing DITA before transforming it into final output.");
    parser.addVersionOption();
    parser.addHelpOption();
    parser.addOption(ditamap_opt);
    parser.addOption(imagesroot_opt);
    parser.addOption(imglibroot_opt);
    parser.process(_args);

    //--ditamap
    //Get path to ditamap file
    if(!parser.isSet(ditamap_opt))
    {
        qDebug("\n --ditamap option is required!\n");
        parser.showHelp();
    }
    else
    {
        DitamapFilePath = QFileInfo(parser.value(ditamap_opt)).absoluteFilePath();
        if(parser.isSet(imagesroot_opt))
        {
            ImageDest = QDir(parser.value(imagesroot_opt));
        }
        else
        {
            ImageDest = QFileInfo(parser.value(ditamap_opt)).absoluteDir();
        }
    }

    //One of the options that enables filters/features is necessary
    //Print a message if none of them are selected
    if(!parser.isSet(imglibroot_opt))
    {
        qDebug("\n --image-libraries-root option is required!\n");
        parser.showHelp();
    }


    //--images
    //Get path to where the ditamap expects the images to be
    if(parser.isSet(imagesroot_opt))
    {
        ImageDest = QDir(parser.value(imagesroot_opt));
    }

    //--image-libraries-root
    //Get path to image libraries
    if(parser.isSet(imglibroot_opt))
    {
        ImageLibraryRoot = QDir(parser.value(imglibroot_opt));
    }


}
