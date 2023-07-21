#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "../../app_settings.h"
#ifdef QT_IN_USE
#include <QDebug>
#include <QDir>
#endif

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <stdio.h>

namespace fs = std::filesystem;

using namespace std;

template <typename STRING_TYPE>
class FileManager{

public:
    FileManager(){
        DEBUG_OUT("FileManager()");
    };
    ~FileManager(){
        DEBUG_OUT("~FileManager()");
    };

    static bool assertFileExist(STRING_TYPE filename);
    static bool deleteFile(STRING_TYPE filename);

    //============= Find all the files with a certain extension and put them into list ================
    static QStringList find_files_in_qdir(QString dir_name, QString ext_name, bool crop_extension){
        QDir directory(qgetFullPath() + dir_name);
        QStringList filters;
        filters << "*" + ext_name;
        directory.setNameFilters(filters);
        QStringList fileList = directory.entryList();

        if(crop_extension){
            QStringList cropped_fileList;
            foreach(const auto &item, fileList){
                QString filename = item;
                filename.chop(ext_name.length());
                cropped_fileList << filename;
            }
            return cropped_fileList;
        }
        return fileList;
    };

    static QString qgetFullPath(){
        QDir dir;
        QString dirPath = dir.absolutePath();
        return dirPath;
    }

protected:
};


template <typename STRING_TYPE>
bool FileManager<STRING_TYPE>::assertFileExist(STRING_TYPE filename){
    string _filename;

    if constexpr(std::is_same<STRING_TYPE, QString>::value) _filename = qgetFullPath().toStdString() + filename.toStdString();
    else _filename = qgetFullPath().toStdString() + filename;

    fstream fileStream;
    fileStream.open(_filename);

    if (fileStream.fail()) {
        if(fileStream.is_open()) fileStream.close();
        return false;
    }
    else{
        if(fileStream.is_open()) fileStream.close();
        return true;
    }
}

template <typename STRING_TYPE>
bool FileManager<STRING_TYPE>::deleteFile(STRING_TYPE filename){
    string _filename;
    if constexpr(std::is_same<STRING_TYPE, QString>::value) _filename = qgetFullPath().toStdString() + filename.toStdString();

    else _filename = qgetFullPath().toStdString() +  filename;
    if(!FileManager<STRING_TYPE>::assertFileExist(filename)){
        DEBUG_OUT("file to delete doesn't exist");
        return false;
    }

    if(remove(_filename.c_str())){
        return false;
    }
    else return true;

}

#endif // FILEMANAGER_H
