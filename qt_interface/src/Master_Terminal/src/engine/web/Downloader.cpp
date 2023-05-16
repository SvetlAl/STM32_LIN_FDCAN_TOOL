#include "Downloader.h"
#include <QDir>

Downloader::Downloader(QObject *parent) : QObject(parent){
    m_pManager = new QNetworkAccessManager();
    connect(m_pManager, &QNetworkAccessManager::finished, this, &Downloader::onResult);
}

void Downloader::getData(QString _url){
    if(m_DownloadPath == "") return;
    QUrl url(_url);
    QNetworkRequest request;
    request.setUrl(url);
    m_pManager->get(request);
}

void Downloader::onResult(QNetworkReply *reply){
    if(reply->error()){
        m_ErrorString = reply->errorString();
        emit onError();
    } else {
        QFile *file = new QFile(m_DownloadPath);
        if(file->open(QFile::WriteOnly)){
            file->write(reply->readAll());
            file->close();
        m_DownloadPath = "";
        emit onReady();
        }
    }
}

QString Downloader::popErrorString() {
    QString errorString = m_ErrorString;
    m_ErrorString.clear();
    return errorString;
}

const QString &Downloader::DownloadPath() const{
    return m_DownloadPath;
}

void Downloader::setDownloadPath(const QString &newDownloadPath){
/*
#ifdef ANDROID_V
    QDir dir;
    QString fullpath = dir.absolutePath();
#endif
#ifndef ANDROID_V
    QString fullpath = "";
#endif */
    m_DownloadPath = newDownloadPath;
}
