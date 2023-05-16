#ifndef WEBMANAGER_H
#define WEBMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QUrl>
#include <QDebug>
#include "../../core/Console.h"
#include "../../core/VersionManager.h"
#include "../../app_settings.h"
#include "../../engine/command_manager/CommandManager.h"
#include "WebConfig.h"
#include "Downloader.h"


class WebManager : public QObject{
    Q_OBJECT

public:
    explicit WebManager(QObject *parent = 0);
    ~WebManager() {};

    enum RequestTarget {
        DefaultValue = 0,
        DeviceVersionInfo = 1,
        DeviceUpdate = 2,
        DeviceCodeOverride = 3
    };

   Q_INVOKABLE bool put_up_download(int _rq_target_value);

    bool isDownloaderBusy(){return (static_cast<RequestTarget>(m_RequestTarget) != DefaultValue);}

    Console *pConsole() const;
    void setConsole(Console *newPConsole);
    WebConfig *pWebConfig() const;
    void setWebConfig(WebConfig *newPWebConfig);
    VersionManager *pVersionManager() const;
    void setVersionManager(VersionManager *newPVersionManager);
    CommandManager *pCommandManager() const;
    void setCommandManager(CommandManager *newCommandManager);

signals:
    void deviceVersionInfoDownloaded();
    void deviceUpdateDownloaded(const QString &_string);
    void deviceCodeOverrideDownloaded();

public slots:
    void resetOnError();
    void downloadFinished();

private:
    Console *m_pConsole;
    WebConfig *m_pWebConfig;
    Downloader *m_pDownloader;
    VersionManager *m_pVersionManager;
    CommandManager *m_pCommandManager;

    RequestTarget m_RequestTarget = DefaultValue;
};

#endif // WEBMANAGER_H
