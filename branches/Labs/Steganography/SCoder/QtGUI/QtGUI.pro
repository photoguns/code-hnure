# -------------------------------------------------
# Project created by QtCreator 2009-05-24T22:08:58
# -------------------------------------------------
TARGET = QtGUI
TEMPLATE = app
INCLUDEPATH += ../SCoder \
    ../SCoder/coders \
    ../SCoder/containers \
    ../SCoder/keys \
    ../easybmp \
    ../libsndfile \
    ../md5
LIBS += ../libsndfile/libsndfile-1.lib
SOURCES += main.cpp \
    mainwindow.cpp \
    ../easybmp/EasyBMP.cpp \
    ../MD5/md5wrapper.cpp \
    ../MD5/md5.cpp \
    ../SCoder/scoder.cpp \
    ../SCoder/coders/lsbsoundcoder.cpp \
    ../SCoder/coders/lsbcoder.cpp \
    ../SCoder/coders/kochzhaocoder.cpp \
    ../SCoder/coders/echocoder.cpp \
    ../SCoder/coders/crosscoder.cpp \
    ../SCoder/coders/coder.cpp \
    ../SCoder/coders/blockcoder.cpp \
    ../SCoder/coders/quantcoder.cpp \
    ../SCoder/coders/prscoder.cpp \
    ../SCoder/coders/pricoder.cpp \
    ../SCoder/containers/wavcontainer.cpp \
    ../SCoder/containers/container.cpp \
    ../SCoder/containers/bmpcontainer.cpp \
    ../SCoder/keys/quantkey.cpp \
    ../SCoder/keys/prskey.cpp \
    ../SCoder/keys/prikey.cpp \
    ../SCoder/keys/kochzhaokey.cpp \
    ../SCoder/keys/key.cpp \
    ../SCoder/keys/blockkey.cpp
HEADERS += mainwindow.h \
    ../easybmp/EasyBMP_VariousBMPutilities.h \
    ../easybmp/EasyBMP_DataStructures.h \
    ../easybmp/EasyBMP_BMP.h \
    ../easybmp/EasyBMP.h \
    ../MD5/md5wrapper.h \
    ../MD5/md5.h \
    ../libsndfile/sndfile.hh \
    ../libsndfile/sndfile.h \
    ../SCoder/scoder.h \
    ../SCoder/coders/lsbsoundcoder.h \
    ../SCoder/coders/lsbcoder.h \
    ../SCoder/coders/kochzhaocoder.h \
    ../SCoder/coders/echocoder.h \
    ../SCoder/coders/crosscoder.h \
    ../SCoder/coders/coder.h \
    ../SCoder/coders/blockcoder.h \
    ../SCoder/coders/quantcoder.h \
    ../SCoder/coders/prscoder.h \
    ../SCoder/coders/pricoder.h \
    ../SCoder/containers/wavcontainer.h \
    ../SCoder/containers/container.h \
    ../SCoder/containers/bmpcontainer.h \
    ../SCoder/keys/quantkey.h \
    ../SCoder/keys/prskey.h \
    ../SCoder/keys/prikey.h \
    ../SCoder/keys/kochzhaokey.h \
    ../SCoder/keys/key.h \
    ../SCoder/keys/blockkey.h
FORMS += mainwindow.ui
