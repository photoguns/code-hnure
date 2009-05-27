# -------------------------------------------------
# Project created by QtCreator 2009-05-24T22:08:58
# -------------------------------------------------
TARGET = LaunchSCoder
TEMPLATE = app
INCLUDEPATH +=        \
    QtGUI/headers     \
    SCoder            \
    SCoder/coders     \
    SCoder/containers \
    SCoder/keys       \
    easybmp           \
    libsndfile        \
    MD5

unix {
    LIBS += /usr/lib/libsndfile.so
}

win32 {
    LIBS += libsndfile/libsndfile-1.lib
}

SOURCES +=                                   \
    QtGUI/sources/main.cpp                   \
    QtGUI/sources/textpage.cpp               \
    QtGUI/sources/soundalgorithm.cpp         \
    QtGUI/sources/scoderwizard.cpp           \
    QtGUI/sources/savecontainerpage.cpp      \
    QtGUI/sources/opencontainerpage.cpp      \
    QtGUI/sources/intropage.cpp              \
    QtGUI/sources/imagealgorithm.cpp         \
    QtGUI/sources/entertextpage.cpp          \
    QtGUI/sources/enterkeypage.cpp           \
    QtGUI/sources/choosealgorithmpage.cpp    \
    QtGUI/sources/viewtextpage.cpp           \
    QtGUI/sources/hidepage.cpp               \
                                             \
    easybmp/EasyBMP.cpp             \
    MD5/md5.cpp                     \
    MD5/md5wrapper.cpp              \
    SCoder/coders/prscoder.cpp      \
    SCoder/coders/pricoder.cpp      \
    SCoder/coders/lsbsoundcoder.cpp \
    SCoder/coders/lsbcoder.cpp      \
    SCoder/coders/kochzhaocoder.cpp \
    SCoder/coders/echocoder.cpp     \
    SCoder/coders/crosscoder.cpp       \
    SCoder/coders/coder.cpp            \
    SCoder/coders/blockcoder.cpp       \
    SCoder/coders/quantcoder.cpp       \
    SCoder/containers/container.cpp    \
    SCoder/containers/bmpcontainer.cpp \
    SCoder/containers/wavcontainer.cpp \
    SCoder/keys/prskey.cpp             \
    SCoder/keys/prikey.cpp             \
    SCoder/keys/kochzhaokey.cpp        \
    SCoder/keys/key.cpp                \
    SCoder/keys/blockkey.cpp           \
    SCoder/keys/quantkey.cpp           \
    SCoder/scoder.cpp                  \
    SCoder/keys/echokey.cpp

HEADERS +=                                         \
    QtGUI/headers/scoderwizard.h                   \
    QtGUI/headers/textpage.h                       \
    QtGUI/headers/soundalgorithm.h                 \
    QtGUI/headers/savecontainerpage.h              \
    QtGUI/headers/opencontainerpage.h              \
    QtGUI/headers/intropage.h                      \
    QtGUI/headers/imagealgorithm.h                 \
    QtGUI/headers/entertextpage.h                  \
    QtGUI/headers/enterkeypage.h                   \
    QtGUI/headers/choosealgorithmpage.h            \
    QtGUI/headers/viewtextpage.h                   \
    QtGUI/headers/hidepage.h                       \
                                                   \
    SCoder/scoder.h                       \
    easybmp/EasyBMP_VariousBMPutilities.h \
    easybmp/EasyBMP_DataStructures.h      \
    easybmp/EasyBMP_BMP.h                 \
    easybmp/EasyBMP.h                     \
    libsndfile/sndfile.h                  \
    libsndfile/sndfile.hh                 \
    MD5/md5wrapper.h                      \
    MD5/md5.h                             \
    SCoder/coders/quantcoder.h            \
    SCoder/coders/prscoder.h              \
    SCoder/coders/pricoder.h              \
    SCoder/coders/lsbsoundcoder.h         \
    SCoder/coders/lsbcoder.h              \
    SCoder/coders/kochzhaocoder.h         \
    SCoder/coders/echocoder.h             \
    SCoder/coders/crosscoder.h            \
    SCoder/coders/coder.h                 \
    SCoder/coders/blockcoder.h            \
    SCoder/containers/wavcontainer.h      \
    SCoder/containers/container.h         \
    SCoder/containers/bmpcontainer.h      \
    SCoder/keys/quantkey.h                \
    SCoder/keys/prskey.h                  \
    SCoder/keys/prikey.h                  \
    SCoder/keys/kochzhaokey.h             \
    SCoder/keys/key.h                     \
    SCoder/keys/blockkey.h                \
    SCoder/keys/echokey.h
