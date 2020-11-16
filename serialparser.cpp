#include <QDebug>

#include "serialparser.h"

SerialParser::SerialParser(QObject *parent) : QObject(parent)
{
}

void SerialParser::parsePacket(QByteArray packet)
{
    QString qline = qUtf8Printable(QString::fromUtf8(packet));
    if (qline.compare("") != 0) {
        // (Ax: -10 | Ay: -9 | Az: 2038) (Gx: 0 | Gy: 0 | Gz: 0)
        qDebug() << qline;

        QRegExp rx("([-0-9]+)");
        int pos = 0;
        int angle[6];
        unsigned int i = 0;
        while ((pos = rx.indexIn(qline, pos)) != -1) {
            angle[i++] = rx.cap(0).toInt();
            pos += rx.matchedLength();
        }

        emit xRotDataArrived(angle[4] * -16);
        emit yRotDataArrived(angle[5] * 16);
        emit zRotDataArrived(angle[3] * -16);
    }
}
