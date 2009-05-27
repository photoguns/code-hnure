# -------------------------------------------------
# Project created by QtCreator 2009-05-24T22:08:58
# -------------------------------------------------
TARGET = QtGUI
TEMPLATE = app
INCLUDEPATH +=           \
    headers              \
    ../SCoder            \
    ../SCoder/coders     \
    ../SCoder/containers \
    ../SCoder/keys       \
    ../easybmp           \
    ../libsndfile        \
    ../MD5

unix {
    LIBS += L/usr/lib/ -libsndfile
}

win32 {
    LIBS += ../libsndfile/libsndfile-1.lib
}

SOURCES += 
    sources/main.cpp                   \
    sources/textpage.cpp               \
    sources/soundalgorithm.cpp         \
    sources/scoderwizard.cpp           \
    sources/savecontainerpage.cpp      \
    sources/opencontainerpage.cpp      \
    sources/intropage.cpp              \
    sources/imagealgorithm.cpp         \
    sources/entertextpage.cpp          \
    sources/enterkeypage.cpp           \
    sources/choosealgorithmpage.cpp    \
    sources/viewtextpage.cpp           \
    sources/hidepage.cpp               \
                                       \
    ../easybmp/EasyBMP.cpp             \
    ../MD5/md5.cpp                     \
    ../MD5/md5wrapper.cpp              \
    ../SCoder/coders/prscoder.cpp      \
    ../SCoder/coders/pricoder.cpp      \
    ../SCoder/coders/lsbsoundcoder.cpp \
    ../SCoder/coders/lsbcoder.cpp      \
    ../SCoder/coders/kochzhaocoder.cpp \
    ../SCoder/coders/echocoder.cpp     \
    ../SCoder/coders/crosscoder.cpp       \
    ../SCoder/coders/coder.cpp            \
    ../SCoder/coders/blockcoder.cpp       \
    ../SCoder/coders/quantcoder.cpp       \
    ../SCoder/containers/container.cpp    \
    ../SCoder/containers/bmpcontainer.cpp \
    ../SCoder/containers/wavcontainer.cpp \
    ../SCoder/keys/prskey.cpp             \
    ../SCoder/keys/prikey.cpp             \
    ../SCoder/keys/kochzhaokey.cpp        \
    ../SCoder/keys/key.cpp                \
    ../SCoder/keys/blockkey.cpp           \
    ../SCoder/keys/quantkey.cpp           \
    ../SCoder/scoder.cpp                  \
    ../SCoder/keys/echokey.cpp

HEADERS += 
    headers/scoderwizard.h                   \
    headers/textpage.h                       \
    headers/soundalgorithm.h                 \
    headers/savecontainerpage.h              \
    headers/opencontainerpage.h              \
    headers/intropage.h                      \
    headers/imagealgorithm.h                 \
    headers/entertextpage.h                  \
    headers/enterkeypage.h                   \
    headers/choosealgorithmpage.h            \
    headers/viewtextpage.h                   \
    headers/hidepage.h                       \
                                             \
    ../SCoder/scoder.h                       \
    ../easybmp/EasyBMP_VariousBMPutilities.h \
    ../easybmp/EasyBMP_DataStructures.h      \
    ../easybmp/EasyBMP_BMP.h                 \
    ../easybmp/EasyBMP.h                     \
    ../libsndfile/sndfile.h                  \
    ../libsndfile/sndfile.hh                 \
    ../MD5/md5wrapper.h                      \
    ../MD5/md5.h                             \
    ../SCoder/coders/quantcoder.h            \
    ../SCoder/coders/prscoder.h              \
    ../SCoder/coders/pricoder.h              \
    ../SCoder/coders/lsbsoundcoder.h         \
    ../SCoder/coders/lsbcoder.h              \
    ../SCoder/coders/kochzhaocoder.h         \
    ../SCoder/coders/echocoder.h             \
    ../SCoder/coders/crosscoder.h            \
    ../SCoder/coders/coder.h                 \
    ../SCoder/coders/blockcoder.h            \
    ../SCoder/containers/wavcontainer.h      \
    ../SCoder/containers/container.h         \
    ../SCoder/containers/bmpcontainer.h      \
    ../SCoder/keys/quantkey.h                \
    ../SCoder/keys/prskey.h                  \
    ../SCoder/keys/prikey.h                  \
    ../SCoder/keys/kochzhaokey.h             \
    ../SCoder/keys/key.h                     \
    ../SCoder/keys/blockkey.h                \
    ../SCoder/keys/echokey.h
