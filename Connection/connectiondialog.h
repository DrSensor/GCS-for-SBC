#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>
#include <QTcpSocket>
#include "GCS_SBC_Data.h"

class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QCheckBox;
class QTcpSocket;
class QNetworkSession;

class ConnectionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConnectionDialog(QWidget *parent = 0);
    
signals:
    void dataAvailable(const QByteArray &);

public slots:
    void setData(const GCS_StructData &data);

private slots:
    void requestNewConnection();
    void readData();
    void displayError(QAbstractSocket::SocketError socketError);
    void enableConnectButton();
    void sessionOpened();

private:
    QLabel *hostLabel;
    QLabel *portLabel;
    QLineEdit *hostLineEdit;
    QLineEdit *portLineEdit;
    QLabel *statusLabel;
    QPushButton *connectButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
    QCheckBox *writeCheck;

    QTcpSocket *tcpSocket;
    QByteArray currentData;
    QByteArray sendData;
    quint16 blockSize;

    QNetworkSession *networkSession;
};

#endif // CONNECTIONDIALOG_H
