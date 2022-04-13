TEMPLATE = app
QT = testlib network
CONFIG += cmdline warn_on depend_includepath testcase

SOURCES = tst_sslsocket.cpp
TESTDATA = top100.txt
DEFINES += SRCDIR=\\\"$$PWD/\\\"
