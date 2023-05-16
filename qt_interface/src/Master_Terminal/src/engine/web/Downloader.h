#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QUrl>
#include <QDebug>
#include "../../app_settings.h"

class Downloader : public QObject{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = 0);
    ~Downloader() {};

    const QString &DownloadPath() const;
    void setDownloadPath(const QString &newDownloadPath);

    QString popErrorString();

signals:
    void onReady();
    void onError();

public slots:
    void getData(QString _url);
    void onResult(QNetworkReply *reply);
private:
    QNetworkAccessManager *m_pManager;
    QString m_DownloadPath = "";
    QString m_ErrorString = "";
};

#endif // DOWNLOADER_H
