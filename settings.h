#include <QString>
#include <QApplication>
#include <QDir>

class Settings
{
public:
    Settings();

    static Settings *getInstance();
    static Settings *getInstance(QStringList);

    static QString DitamapFilePath;
    static QDir ImageLibraryRoot;
    static QDir ImageDest;

private:
    static void ParseCommandLine();
    static Settings *_instance;

    static QStringList _args;


};

