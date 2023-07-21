#include "Qmltranslator.h"
#include "../../app_settings.h"
#include <QApplication>
 
QmlTranslator::QmlTranslator(QObject *parent) : QObject(parent){
 
}
 
void QmlTranslator::setTranslation(QString translation){
    bool _load = m_translator.load(QString(App_settings::TRANSLATIONS_PATH).append(translation).append(".qm"), ".");
    if(_load){
        qApp->installTranslator(&m_translator);
        emit languageChanged();
    }
}
