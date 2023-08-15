#ifndef QCLASSLOADER_H
#define QCLASSLOADER_H

/***********************************************************************
 *
 *
 * QClassLoader is a temporary instance for save/load operations on a custom class
 *
 *
 *
 *
 ************************************************************************/

#include <QObject>
#include <QString>
#include <QStringList>
#include <QList>
#include <QFile>
#include <QDir>
#include <QDebug>
#include "FileManager.h"

template <typename T>
class QClassLoader{

public:
    QClassLoader(){
    }
     ~QClassLoader(){
    }

    bool assertFileExist(){
        return FileManager<QString>::assertFileExist(m_filename);
    }

    void setFilename(const QString &newFilename){m_filename = newFilename;};
    void setDirname(const QString &newDirname){m_dirname = newDirname;};

    T loadClassInstance(){
        T var;
        if(this->assertFileExist()){
            QDEBUG_OUT("OK: Opening file for reading. The file exists.");
            QDEBUG_OUT(this->m_filename);
         }
        else {
            QDEBUG_OUT("FAILED: Opening file for reading. The file doesn't exist. ")
            QDEBUG_OUT(this->m_filename);
            return var;
         }
        constructFile();

        if (!file.open(QIODevice::ReadOnly)) {
            DEBUG_OUT("FAILED: Open Error.");
            if(file.isOpen())file.close();
            return var;
        }

        QDataStream stream(&file);
        stream >> var;

        if (stream.status() != QDataStream::Ok) {
            DEBUG_OUT("FAILED: Read Error.");
            if(file.isOpen())file.close();
            return var;
        }
        else {
            DEBUG_OUT("OK: The file successfully read. ")
            if(file.isOpen())file.close();
            return var;
         }
        if(file.isOpen())file.close();
        return var;
    }

    bool saveClassInstance(T& var){
        constructFile();

        if(this->assertFileExist()){
            QDEBUG_OUT("OK: Opening file for writing. The file exists. ")
         }
        else {
            QDEBUG_OUT("Opening file for writing. The file doesn't exist. Creating a new one. " + file.fileName(););
         }

        if (!file.open(QIODevice::WriteOnly)) {
            DEBUG_OUT("FAILED: Failed to open for WRITE.");
            if(file.isOpen())file.close();
            return false;
        }
        QDataStream stream(&file);
        stream << var;

        if (stream.status() != QDataStream::Ok) {
            DEBUG_OUT("FAILED: Write error.");
            if(file.isOpen())file.close();
            return false;
        }
        else{
            DEBUG_OUT("OK: File successfully written.");
            if(file.isOpen())file.close();
            return true;
        }
    }



private:
    QFile file;

    QString m_filename = "";
    QString m_dirname = "";


    void constructFile(){
        file.setFileName(getFullPath() + this->m_filename);
    }

    QString getFullPath(){
        QDir dir;
        QString dirPath = dir.absolutePath();
        return dirPath;
    }

};


#endif
