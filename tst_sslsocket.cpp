#include <QtCore>
#include <QtNetwork>
#include <QtTest>

class tst_sslsocket : public QObject
{
    Q_OBJECT
private slots:
    void top100_data();
    void top100();
};

void tst_sslsocket::top100_data()
{
    QTest::addColumn<QString>("host");
    QFile file(QFINDTESTDATA("top100.txt"));
    if (file.open(QFile::ReadOnly)) {
        QTextStream stream(&file);
        while (!stream.atEnd()) {
            const QString host = stream.readLine();
            QTest::newRow(qPrintable(host)) << host;
        }
        file.close();
    } else {
        qWarning() << file.errorString();
    }
}

void tst_sslsocket::top100()
{
    QFETCH(QString, host);
    QSslSocket socket;
    connect(&socket, QOverload<const QList<QSslError> &>::of(&QSslSocket::sslErrors), this, [&](const QList<QSslError> errors) {
        for (const auto &e : errors) {
            QFAIL(qUtf8Printable(e.errorString()));
        }
    });
    socket.connectToHostEncrypted(host, 443);
    QVERIFY(socket.waitForConnected());
    QVERIFY(socket.waitForEncrypted());
}

QTEST_GUILESS_MAIN(tst_sslsocket)

#include "tst_sslsocket.moc"
