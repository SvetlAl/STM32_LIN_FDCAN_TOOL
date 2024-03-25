#include "QASerialPort.h"

#ifdef ANDROID_V
static char UsbSerial_jniClassName[] {"org/qtproject/jniusbserial/JniUsbSerial"};

static void jniDeviceNewData(JNIEnv *envA, jobject thizA, jint classPoint, jbyteArray dataA)
{
    Q_UNUSED(thizA);

    if (classPoint != 0)
    {
        jbyte *bytesL = envA->GetByteArrayElements(dataA, NULL);
        jsize lenL = envA->GetArrayLength(dataA);
        ((QASerialPort *)classPoint)->newDataArrived((char *)bytesL, lenL);
        envA->ReleaseByteArrayElements(dataA, bytesL, JNI_ABORT);
    }
}

static void jniDeviceException(JNIEnv *envA, jobject thizA, jint classPoint, jstring messageA)
{
    Q_UNUSED(thizA);

    if (classPoint != 0)
    {
        const char *stringL = envA->GetStringUTFChars(messageA, NULL);
        QString strL = QString::fromUtf8(stringL);
        envA->ReleaseStringUTFChars(messageA, stringL);
        if (envA->ExceptionCheck())
            envA->ExceptionClear();
        ((QASerialPort *)classPoint)->exceptionArrived(strL);
    }
}


QASerialPort::QASerialPort()
{
    readBufferMaxSize = 16384;

    isConnected = false;
    m_portName = "";
    m_baudRate = Baud115200;
    m_dataBits = Data8;
    m_parity = NoParity;
    m_stopBits = OneStop;

    JNINativeMethod methodsL[] {{"nativeDeviceNewData", "(I[B)V", reinterpret_cast<void *>(jniDeviceNewData)},
                                        {"nativeDeviceException", "(ILjava/lang/String;)V", reinterpret_cast<void *>(jniDeviceException)}};

    QJniEnvironment envL;
    QJniObject javaClassL(UsbSerial_jniClassName);
    jclass objectClassL = envL->GetObjectClass(javaClassL.object<jobject>());

    jint valL = envL->RegisterNatives(objectClassL, methodsL, sizeof(methodsL) / sizeof(methodsL[0]));
    envL->DeleteLocalRef(objectClassL);

    if (envL->ExceptionCheck())
        envL->ExceptionClear();

//    if (valL < 0)
//        return false;
    Q_UNUSED(valL);
}

bool QASerialPort::setBaudRate(qint32 baudRate)
{
    m_baudRate = baudRate;

    return setParameters();
}

void QASerialPort::newDataArrived(char *bytesA, int lengthA)
{
    int bytesToReadL = lengthA;

    if (readBufferMaxSize && (bytesToReadL > (readBufferMaxSize - readBuffer.size()))) {
        bytesToReadL = readBufferMaxSize - readBuffer.size();
        if (bytesToReadL <= 0) {
            stopReadThread();
            return;
        }
    }

    readBuffer.open(QIODevice::ReadWrite);
    readBuffer.seek(readBuffer.size());
    readBuffer.write(bytesA, bytesToReadL);
    readBuffer.close();

    emit readyRead();
}

void QASerialPort::exceptionArrived(QString strA)
{
    Q_UNUSED(strA);
    emit errorOccurred(ResourceError);
}

void QASerialPort::stopReadThread()
{
    QJniObject java_portName = QJniObject::fromString(m_portName);
    QJniObject::callStaticMethod<void>(UsbSerial_jniClassName,
                                              "stopIoManager",
                                              "(Ljava/lang/String;)V",
                                              java_portName.object<jstring>());
}

void QASerialPort::startReadThread()
{
    QJniObject java_portName = QJniObject::fromString(m_portName);
    QJniObject::callStaticMethod<void>(UsbSerial_jniClassName,
                                              "startIoManager",
                                              "(Ljava/lang/String;I)V",
                                              java_portName.object<jstring>(),
                                       (jint)this);
}

qint64 QASerialPort::bytesAvailable()
{
    return readBuffer.size();
}

QByteArray QASerialPort::read(qint64 maxlen)
{
    if (maxlen > readBuffer.size())
    {
        return readAll();
    }

    readBuffer.open(QIODevice::ReadWrite);
    const QByteArray &data = readBuffer.data();
    const QByteArray firstNBytes = data.left(maxlen);
    readBuffer.buffer().remove(0, maxlen);
    readBuffer.close();

    return firstNBytes;
}

QByteArray QASerialPort::readAll()
{
    readBuffer.open(QIODevice::ReadWrite);
    const QByteArray data = readBuffer.data();
    readBuffer.buffer().clear();
    readBuffer.close();

    return data;
}

QByteArray QASerialPort::readLine()
{
    readBuffer.open(QIODevice::ReadWrite);
    const QByteArray data = readBuffer.readLine();
    readBuffer.buffer().remove(0, data.length());
    readBuffer.close();

    return data;
}

bool QASerialPort::isOpen()
{
    return isConnected;
}

void QASerialPort::close()
{
    if (m_portName == "")
    {
        isConnected = false;
        return;
    }

    QJniObject java_portName = QJniObject::fromString(m_portName);
    jboolean resultL = QJniObject::callStaticMethod<jboolean>(UsbSerial_jniClassName,
                                                                         "close",
                                                                         "(Ljava/lang/String;)Z",
                                                                         java_portName.object<jstring>());

    if (resultL)
    {
        isConnected = false;
    }
}

bool QASerialPort::open(QIODeviceBase::OpenMode mode)
{
    Q_UNUSED(mode);
    if (m_portName == "")
    {
        return false;
    }

    QJniObject java_portName = QJniObject::fromString(m_portName);
    jint resultL = QJniObject::callStaticMethod<jint>(UsbSerial_jniClassName,
                                                                         "open",
                                                                         "(Ljava/lang/String;I)I",
                                                                         java_portName.object<jstring>(),
                                                              (jint)this);

    if (resultL == 0)
    {
        return false;
    }
    else
    {
        isConnected = true;
        if (!setParameters())
        {
            isConnected = false;
            return false;
        }
        return true;
    }
}

qint64 QASerialPort::write(const char *data, qint64 maxSize)
{
    if (m_portName == "")
    {
        emit errorOccurred(QASerialPort::NotOpenError);
        return 0;
    }

    if (!isConnected)
    {
        emit errorOccurred(QASerialPort::NotOpenError);
        return 0;
    }

    QJniEnvironment envL;
    QJniObject java_portName = QJniObject::fromString(m_portName);
    jbyteArray jarrayL = envL->NewByteArray(maxSize);
    envL->SetByteArrayRegion(jarrayL, 0, maxSize, (jbyte *)data);
    int resultL = QJniObject::callStaticMethod<jint>(UsbSerial_jniClassName,
                                                            "write",
                                                            "(Ljava/lang/String;[BI)I",
                                                            java_portName.object<jstring>(),
                                                            jarrayL,
                                                            2000);

    if (envL->ExceptionCheck())
    {
        envL->ExceptionClear();
        emit errorOccurred(QASerialPort::UnknownError);
        envL->DeleteLocalRef(jarrayL);
        return 0;
    }

    envL->DeleteLocalRef(jarrayL);

    if (resultL == 0)
    {
        emit errorOccurred(QASerialPort::WriteError);
        return 0;
    }

    return maxSize;
}

void QASerialPort::setPortName(const QString &name)
{
    m_portName = name;
}

QString QASerialPort::portName() const
{
    return m_portName;
}

bool QASerialPort::setParameters()
{
    if (isConnected == true)
    {
        QJniObject java_portName = QJniObject::fromString(m_portName);

        jboolean resultL = QJniObject::callStaticMethod<jboolean>(UsbSerial_jniClassName,
                                           "setParameters",
                                           "(Ljava/lang/String;IIII)Z",
                                            java_portName.object<jstring>(),
                                               m_baudRate,
                                               m_dataBits,
                                               m_stopBits,
                                               m_parity);

        return resultL;
    }

    return true;
}
#endif

