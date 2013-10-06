#ifndef UTIL_H
#define UTIL_H

#include <QApplication>
#include <QDir>

#define PLATFORM_UNKNOWN 0
#define PLATFORM_LINUX 1
#define PLATFORM_OSX 2
#define PLATFORM_WINDOWS 3

class Util
{
public:
    Util();

public:
    static int GetPlatform() {
        #if defined(Q_OS_LINUX)
            return PLATFORM_LINUX;
        #elif defined(Q_OS_MAC)
              return PLATFORM_OSX;
        #elif defined(Q_OS_WIN32)
               return PLATFORM_WINDOWS;
        #else
            return PLATFORM_UNKNOWN;
        #endif
    }

    static QString GetLocalDir(QString dirName) {
        QString dirPath = QApplication::applicationDirPath() + QDir::separator() + dirName;
        QDir dir(dirPath);
        if(!dir.exists()) dir.mkdir(dirPath);
        return dirPath;
    }

    static QString GetLocalFile(QString dirName, QString fileName) {
        QString filePath = Util::GetLocalDir(dirName) + QDir::separator() + fileName;
        return filePath;
    }
};

#endif // UTIL_H
