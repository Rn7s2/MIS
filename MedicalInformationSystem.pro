QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    doctormodifyprescriptiondialog.cpp \
    doctornewprescriptiondialog.cpp \
    doctorviewprescriptiondialog.cpp \
    doctorwindow.cpp \
    logindialog.cpp \
    main.cpp \
    quicksearchdialog.cpp \
    stockeraddexistingdialog.cpp \
    stockeraddnewdialog.cpp \
    stockermedicinedetaildialog.cpp \
    stockermodifydialog.cpp \
    stockeroverviewdialog.cpp \
    stockerwindow.cpp \
    stockoutconfirmdialog.cpp \
    stockrecordviewdialog.cpp

HEADERS += \
    doctormodifyprescriptiondialog.h \
    doctornewprescriptiondialog.h \
    doctorviewprescriptiondialog.h \
    doctorwindow.h \
    logindialog.h \
    quicksearchdialog.h \
    stockeraddexistingdialog.h \
    stockeraddnewdialog.h \
    stockermedicinedetaildialog.h \
    stockermodifydialog.h \
    stockeroverviewdialog.h \
    stockerwindow.h \
    stockoutconfirmdialog.h \
    stockrecordviewdialog.h

FORMS += \
    doctormodifyprescriptiondialog.ui \
    doctornewprescriptiondialog.ui \
    doctorviewprescriptiondialog.ui \
    doctorwindow.ui \
    logindialog.ui \
    quicksearchdialog.ui \
    stockeraddexistingdialog.ui \
    stockeraddnewdialog.ui \
    stockermedicinedetaildialog.ui \
    stockermodifydialog.ui \
    stockeroverviewdialog.ui \
    stockerwindow.ui \
    stockoutconfirmdialog.ui \
    stockrecordviewdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
