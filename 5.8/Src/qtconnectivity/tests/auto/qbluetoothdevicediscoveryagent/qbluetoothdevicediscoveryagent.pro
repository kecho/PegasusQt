SOURCES += tst_qbluetoothdevicediscoveryagent.cpp
TARGET=tst_qbluetoothdevicediscoveryagent
CONFIG += testcase

QT = core concurrent bluetooth-private testlib
osx:QT += widgets

qtConfig(bluez):qtHaveModule(dbus) {
    DEFINES += QT_BLUEZ_BLUETOOTH
}
