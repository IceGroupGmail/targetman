# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = lib
TARGET = target_com
QT += core network widgets serialport
CONFIG += debug
DEFINES += WIN64 QT_DLL QT_NETWORK_LIB TARGET_COM_LIB
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/Debug 
    
INCLUDEPATH += 	$(WDH_ROOT)/inc .. 
DESTDIR     += 	$(WDH_ROOT)/bin
LIBPATH     +=  $(WDH_ROOT)/lib 

DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/debug
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles

HEADERS += $$(WDH_ROOT)/inc/qtargetcomm.h \
           ../power_crc.h \
           ../power_modbus.h \
           ../qtargetclient.h \
           ../qtargetserial.h \
					 ../qtargetserver.h
           
SOURCES += ../qtargetcomm.cpp \
           ../tp_communication_if.cpp \
           ../power_crc.cpp \
           ../power_modbus.cpp \
           ../qtargetclient.cpp \
           ../qtargetserial.cpp \
           ../qtargetserver.cpp
