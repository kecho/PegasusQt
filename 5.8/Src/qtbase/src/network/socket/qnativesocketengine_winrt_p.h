/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtNetwork module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QNATIVESOCKETENGINE_WINRT_P_H
#define QNATIVESOCKETENGINE_WINRT_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of the QLibrary class.  This header file may change from
// version to version without notice, or even be removed.
//
// We mean it.
//

#include <QtNetwork/private/qtnetworkglobal_p.h>
#include <QtCore/QEventLoop>
#include <QtCore/QBuffer>
#include <QtCore/QMutex>
#include <QtCore/QAtomicInteger>
#include "QtNetwork/qhostaddress.h"
#include "private/qabstractsocketengine_p.h"
#include <wrl.h>
#include <windows.networking.sockets.h>

QT_BEGIN_NAMESPACE

class QNativeSocketEnginePrivate;
class SocketEngineWorker;

struct WinRtDatagram {
    QByteArray data;
    QIpPacketHeader header;
};

class Q_AUTOTEST_EXPORT QNativeSocketEngine : public QAbstractSocketEngine
{
    Q_OBJECT
public:
    QNativeSocketEngine(QObject *parent = 0);
    ~QNativeSocketEngine();

    bool initialize(QAbstractSocket::SocketType type, QAbstractSocket::NetworkLayerProtocol protocol = QAbstractSocket::IPv4Protocol);
    bool initialize(qintptr socketDescriptor, QAbstractSocket::SocketState socketState = QAbstractSocket::ConnectedState);

    qintptr socketDescriptor() const;

    bool isValid() const;

    bool connectToHost(const QHostAddress &address, quint16 port);
    bool connectToHostByName(const QString &name, quint16 port);
    bool bind(const QHostAddress &address, quint16 port);
    bool listen();
    int accept();
    void close();

#ifndef QT_NO_NETWORKINTERFACE
    bool joinMulticastGroup(const QHostAddress &groupAddress,
                            const QNetworkInterface &iface);
    bool leaveMulticastGroup(const QHostAddress &groupAddress,
                             const QNetworkInterface &iface);
    QNetworkInterface multicastInterface() const;
    bool setMulticastInterface(const QNetworkInterface &iface);
#endif

    qint64 bytesAvailable() const;

    qint64 read(char *data, qint64 maxlen);
    qint64 write(const char *data, qint64 len);

    qint64 readDatagram(char *data, qint64 maxlen, QIpPacketHeader * = 0, PacketHeaderOptions = WantNone);
    qint64 writeDatagram(const char *data, qint64 len, const QIpPacketHeader &header);
    bool hasPendingDatagrams() const;
    qint64 pendingDatagramSize() const;

    qint64 bytesToWrite() const;

    qint64 receiveBufferSize() const;
    void setReceiveBufferSize(qint64 bufferSize);

    qint64 sendBufferSize() const;
    void setSendBufferSize(qint64 bufferSize);

    int option(SocketOption option) const;
    bool setOption(SocketOption option, int value);

    bool waitForRead(int msecs = 30000, bool *timedOut = 0);
    bool waitForWrite(int msecs = 30000, bool *timedOut = 0);
    bool waitForReadOrWrite(bool *readyToRead, bool *readyToWrite,
                            bool checkRead, bool checkWrite,
                            int msecs = 30000, bool *timedOut = 0);

    bool isReadNotificationEnabled() const;
    void setReadNotificationEnabled(bool enable);
    bool isWriteNotificationEnabled() const;
    void setWriteNotificationEnabled(bool enable);
    bool isExceptionNotificationEnabled() const;
    void setExceptionNotificationEnabled(bool enable);

signals:
    void connectionReady();
    void readReady();
    void writeReady();
    void newDatagramReceived(const WinRtDatagram &datagram);

private slots:
    void establishRead();
    void handleNewDatagrams(const QList<WinRtDatagram> &datagram);
    void handleNewData(const QVector<QByteArray> &data);
    void handleTcpError(QAbstractSocket::SocketError error);

private:
    Q_INVOKABLE void putIntoPendingDatagramsList(const QList<WinRtDatagram> &datagrams);
    Q_INVOKABLE void putIntoPendingData(const QVector<QByteArray> &data);

    Q_DECLARE_PRIVATE(QNativeSocketEngine)
    Q_DISABLE_COPY(QNativeSocketEngine)
};

class QNativeSocketEnginePrivate : public QAbstractSocketEnginePrivate
{
    Q_DECLARE_PUBLIC(QNativeSocketEngine)
public:
    QNativeSocketEnginePrivate();
    ~QNativeSocketEnginePrivate();

    qintptr socketDescriptor;
    SocketEngineWorker *worker;

    bool notifyOnRead, notifyOnWrite, notifyOnException;
    QAtomicInt closingDown;

    enum ErrorString {
        NonBlockingInitFailedErrorString,
        BroadcastingInitFailedErrorString,
        NoIpV6ErrorString,
        RemoteHostClosedErrorString,
        TimeOutErrorString,
        ResourceErrorString,
        OperationUnsupportedErrorString,
        ProtocolUnsupportedErrorString,
        InvalidSocketErrorString,
        HostUnreachableErrorString,
        NetworkUnreachableErrorString,
        AccessErrorString,
        ConnectionTimeOutErrorString,
        ConnectionRefusedErrorString,
        AddressInuseErrorString,
        AddressNotAvailableErrorString,
        AddressProtectedErrorString,
        DatagramTooLargeErrorString,
        SendDatagramErrorString,
        ReceiveDatagramErrorString,
        WriteErrorString,
        ReadErrorString,
        PortInuseErrorString,
        NotSocketErrorString,
        InvalidProxyTypeString,
        TemporaryErrorString,

        UnknownSocketErrorString = -1
    };

    void setError(QAbstractSocket::SocketError error, ErrorString errorString) const;

    // native functions
    int option(QNativeSocketEngine::SocketOption option) const;
    bool setOption(QNativeSocketEngine::SocketOption option, int value);

    bool createNewSocket(QAbstractSocket::SocketType type, QAbstractSocket::NetworkLayerProtocol &protocol);

    bool checkProxy(const QHostAddress &address);
    bool fetchConnectionParameters();

private:
    inline ABI::Windows::Networking::Sockets::IStreamSocket *tcpSocket() const
        { return reinterpret_cast<ABI::Windows::Networking::Sockets::IStreamSocket *>(socketDescriptor); }
    inline ABI::Windows::Networking::Sockets::IDatagramSocket *udpSocket() const
        { return reinterpret_cast<ABI::Windows::Networking::Sockets::IDatagramSocket *>(socketDescriptor); }
    Microsoft::WRL::ComPtr<ABI::Windows::Networking::Sockets::IStreamSocketListener> tcpListener;
    Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IAsyncAction> connectOp;

    // In case of TCP readMutex protects readBytes and bytesAvailable. In case of UDP it is
    // pendingDatagrams. They are written inside native callbacks (handleReadyRead and
    // handleNewDatagrams/putIntoPendingDatagramsList)
    mutable QMutex readMutex;

    // Protected by readMutex. Written in handleReadyRead (native callback)
    QAtomicInteger<int> bytesAvailable;

    // Protected by readMutex. Written in handleNewData/putIntoPendingData (native callback)
    QVector<QByteArray> pendingData;

    // Protected by readMutex. Written in handleNewDatagrams/putIntoPendingDatagramsList
    QList<WinRtDatagram> pendingDatagrams;

    QList<ABI::Windows::Networking::Sockets::IStreamSocket *> pendingConnections;
    QList<ABI::Windows::Networking::Sockets::IStreamSocket *> currentConnections;
    QEventLoop eventLoop;
    QAbstractSocket *sslSocket;
    EventRegistrationToken connectionToken;

    HRESULT handleNewDatagram(ABI::Windows::Networking::Sockets::IDatagramSocket *socket,
                              ABI::Windows::Networking::Sockets::IDatagramSocketMessageReceivedEventArgs *args);
    HRESULT handleClientConnection(ABI::Windows::Networking::Sockets::IStreamSocketListener *tcpListener,
                                   ABI::Windows::Networking::Sockets::IStreamSocketListenerConnectionReceivedEventArgs *args);
    HRESULT handleConnectOpFinished(ABI::Windows::Foundation::IAsyncAction *, ABI::Windows::Foundation::AsyncStatus);
};

QT_END_NAMESPACE

Q_DECLARE_METATYPE(WinRtDatagram)

#endif // QNATIVESOCKETENGINE_WINRT_P_H
