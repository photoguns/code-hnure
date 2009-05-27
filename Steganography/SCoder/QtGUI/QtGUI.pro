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
    scoderwizard.cpp \
    textpage.cpp \
    soundalgorithm.cpp \
    scoderwizard.cpp \
    savecontainerpage.cpp \
    opencontainerpage.cpp \
    intropage.cpp \
    imagealgorithm.cpp \
    entertextpage.cpp \
    enterkeypage.cpp \
    choosealgorithmpage.cpp \
    viewtextpage.cpp \
    hidepage.cpp \
    ../easybmp/EasyBMP.cpp \
    ../MD5/md5.cpp \
    ../MD5/md5wrapper.cpp \
    ../SCoder/coders/prscoder.cpp \
    ../SCoder/coders/pricoder.cpp \
    ../SCoder/coders/lsbsoundcoder.cpp \
    ../SCoder/coders/lsbcoder.cpp \
    ../SCoder/coders/kochzhaocoder.cpp \
    ../SCoder/coders/echocoder.cpp \
    ../SCoder/coders/crosscoder.cpp \
    ../SCoder/coders/coder.cpp \
    ../SCoder/coders/blockcoder.cpp \
    ../SCoder/coders/quantcoder.cpp \
    ../SCoder/containers/container.cpp \
    ../SCoder/containers/bmpcontainer.cpp \
    ../SCoder/containers/wavcontainer.cpp \
    ../SCoder/keys/prskey.cpp \
    ../SCoder/keys/prikey.cpp \
    ../SCoder/keys/kochzhaokey.cpp \
    ../SCoder/keys/key.cpp \
    ../SCoder/keys/blockkey.cpp \
    ../SCoder/keys/quantkey.cpp \
    ../SCoder/scoder.cpp
HEADERS += scoderwizard.h \
    textpage.h \
    soundalgorithm.h \
    savecontainerpage.h \
    opencontainerpage.h \
    intropage.h \
    imagealgorithm.h \
    entertextpage.h \
    enterkeypage.h \
    choosealgorithmpage.h \
    viewtextpage.h \
    hidepage.h \
    ../SCoder/scoder.h \
    ../easybmp/EasyBMP_VariousBMPutilities.h \
    ../easybmp/EasyBMP_DataStructures.h \
    ../easybmp/EasyBMP_BMP.h \
    ../easybmp/EasyBMP.h \
    ../libsndfile/sndfile.h \
    ../libsndfile/sndfile.hh \
    ../MD5/md5wrapper.h \
    ../MD5/md5.h \
    ../SCoder/coders/quantcoder.h \
    ../SCoder/coders/prscoder.h \
    ../SCoder/coders/pricoder.h \
    ../SCoder/coders/lsbsoundcoder.h \
    ../SCoder/coders/lsbcoder.h \
    ../SCoder/coders/kochzhaocoder.h \
    ../SCoder/coders/echocoder.h \
    ../SCoder/coders/crosscoder.h \
    ../SCoder/coders/coder.h \
    ../SCoder/coders/blockcoder.h \
    ../SCoder/containers/wavcontainer.h \
    ../SCoder/containers/container.h \
    ../SCoder/containers/bmpcontainer.h \
    ../SCoder/keys/quantkey.h \
    ../SCoder/keys/prskey.h \
    ../SCoder/keys/prikey.h \
    ../SCoder/keys/kochzhaokey.h \
    ../SCoder/keys/key.h \
    ../SCoder/keys/blockkey.h
