#ifndef SERIALPARSER_H
#define SERIALPARSER_H

#include <QObject>

class SerialParser : public QObject
{
    Q_OBJECT
public:
    explicit SerialParser(QObject *parent = nullptr);

public slots:
    void parsePacket(QByteArray packet);

signals:
    void xRotDataArrived(int angle);
    void yRotDataArrived(int angle);
    void zRotDataArrived(int angle);
};

#endif // SERIALPARSER_H
