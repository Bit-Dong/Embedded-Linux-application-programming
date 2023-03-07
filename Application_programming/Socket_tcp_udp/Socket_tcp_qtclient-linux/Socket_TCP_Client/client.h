#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include<QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui {
class client;
}
QT_END_NAMESPACE

class client : public QWidget
{
    Q_OBJECT

public:
    client(QWidget *parent = nullptr);
    ~client();

private slots:
    void on_buttonconnect_clicked();

    void on_buttonsend_clicked();

    void on_buttonclose_clicked();

private:
    Ui::client *ui;
    QTcpSocket *tcpsocket;//声明套接字 客户端只有一个通信套接字
};

#endif // CLIENT_H
