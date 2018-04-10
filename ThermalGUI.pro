#-------------------------------------------------
#
# Project created by QtCreator 2018-03-21T15:20:34
#
#-------------------------------------------------

QT       += core gui
QT       += core
QT       += widgets

TARGET = ThermalGUI
CONFIG   += c++11

INCLUDEPATH += /usr/local/include/opencv2
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui

TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    main2.cpp \
    Third-Party/Lepton/Lepton_I2C.cpp \
    Third-Party/Lepton/LeptonThread.cpp \
    Third-Party/Lepton/MyLabel.cpp \
    Third-Party/Lepton/Palettes.cpp \
    Third-Party/Lepton/SPI.cpp \
    Third-Party/Lepton/leptonSDKEmb32PUB/bbb_I2C.c \
    Third-Party/Lepton/leptonSDKEmb32PUB/crc16fast.c \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_AGC.c \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_I2C_Protocol.c \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_I2C_Service.c \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_SDK.c \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_SYS.c \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_VID.c \
    Third-Party/RS-232/rs232.c \
    Modules/Retriever.cpp \
    Modules/Stitcher.cpp \
    Drivers/Display.cpp \
    Drivers/Imager.cpp \
    Drivers/PanTilt.cpp

HEADERS  += mainwindow.h \
    Third-Party/Lepton/Lepton_I2C.h \
    Third-Party/Lepton/LeptonThread.h \
    Third-Party/Lepton/MyLabel.h \
    Third-Party/Lepton/Palettes.h \
    Third-Party/Lepton/SPI.h \
    Third-Party/Lepton/leptonSDKEmb32PUB/bbb_I2C.h \
    Third-Party/Lepton/leptonSDKEmb32PUB/crc16.h \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_AGC.h \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_ErrorCodes.h \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_I2C_Protocol.h \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_I2C_Reg.h \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_I2C_Service.h \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_Macros.h \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_SDK.h \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_SDKConfig.h \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_SYS.h \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_Types.h \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_VID.h \
    Third-Party/RS-232/rs232.h \
    Modules/Retriever.h \
    Modules/Stitcher.h \
    Drivers/Display.h \
    Drivers/Imager.h \
    Drivers/PanTilt.h

FORMS    += mainwindow.ui

SUBDIRS += \
    Third-Party/Lepton/raspberrypi_video.pro

OTHER_FILES += \
    Third-Party/Lepton/README.md \
    Third-Party/Lepton/leptonSDKEmb32PUB/Makefile
