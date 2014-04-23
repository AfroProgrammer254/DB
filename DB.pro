#-------------------------------------------------
#
# Project created by QtCreator 2014-02-08T12:01:17
#
#-------------------------------------------------

QT       += core gui sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DB
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    memberdetails.cpp \
    login_form.cpp \
    panel.cpp \
    settings.cpp \
    year_deposits.cpp \
    members.cpp \
    prevdeposits.cpp \
    employees.cpp \
    loans.cpp

HEADERS  += login.h \
    memberdetails.h \
    login_form.h \
    panel.h \
    settings.h \
    year_deposits.h \
    members.h \
    prevdeposits.h \
    employees.h \
    loans.h

FORMS    += login.ui \
    memberdetails.ui \
    login_form.ui \
    panel.ui \
    settings.ui \
    year_deposits.ui \
    members.ui \
    prevdeposits.ui \
    employees.ui \
    loans.ui

RESOURCES += \
    Resources.qrc
