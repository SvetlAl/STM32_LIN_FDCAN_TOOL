#include "QASerialPortinfo.h"
#include "../../app_settings.h"

#ifdef ANDROID_V
static char UsbSerial_jniClassName[] {"org/qtproject/jniusbserial/JniUsbSerial"};

QASerialPortInfo::QASerialPortInfo()
{

}

QASerialPortInfo::QASerialPortInfo(const QASerialPortInfo &other)
{
    _portName = other._portName;
    _device = other._device;
    _manufacturer = other._manufacturer;
    _productIdentifier = other._productIdentifier;
    _hasProductIdentifier = other._hasProductIdentifier;
    _vendorIdentifier = other._vendorIdentifier;
    _hasVendorIdentifier = other._hasVendorIdentifier;
}

QASerialPortInfo &QASerialPortInfo::operator=(const QASerialPortInfo &other)
{
    _portName = other._portName;
    _device = other._device;
    _manufacturer = other._manufacturer;
    _productIdentifier = other._productIdentifier;
    _hasProductIdentifier = other._hasProductIdentifier;
    _vendorIdentifier = other._vendorIdentifier;
    _hasVendorIdentifier = other._hasVendorIdentifier;
    return *this;
}

QList<QASerialPortInfo> QASerialPortInfo::availablePorts()
{
    QList<QASerialPortInfo> serialPortInfoList;

    QJniObject resultL = QJniObject::callStaticObjectMethod(UsbSerial_jniClassName,
                                                                          "availableDevicesInfo",
                                                                          "()[Ljava/lang/String;");

    if (!resultL.isValid())
        return serialPortInfoList;

    QJniEnvironment envL;
    jobjectArray objArrayL = resultL.object<jobjectArray>();
    int countL = envL->GetArrayLength(objArrayL);

    for (int iL=0; iL<countL; iL++)
    {
        QASerialPortInfo infoL;
        jstring stringL = (jstring)(envL->GetObjectArrayElement(objArrayL, iL));
        const char *rawStringL = envL->GetStringUTFChars(stringL, 0);
        QStringList strListL = QString::fromUtf8(rawStringL).split(QStringLiteral(":"));
        envL->ReleaseStringUTFChars(stringL, rawStringL);

        infoL._portName = strListL[0];
        infoL._device = strListL[1];
        infoL._manufacturer = strListL[2];
        infoL._productIdentifier = strListL[3].toInt();
        infoL._hasProductIdentifier = (infoL._productIdentifier != 0)? true: false;
        infoL._vendorIdentifier = strListL[4].toInt();
        infoL._hasVendorIdentifier = (infoL._vendorIdentifier != 0)? true: false;

        serialPortInfoList.append(infoL);
    }

    return serialPortInfoList;
}

QString QASerialPortInfo::portName() const
{
    return _portName;
}
#endif

