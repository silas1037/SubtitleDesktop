QT += widgets


DEFINES+=DLLFLAG
TEMPLATE = lib
TARGET=LocalSub
HEADERS       = LocalSub.h
SOURCES       = LocalSub.cpp \
                LocalSubImpl.cpp


HEADERS       = wigglywidget.h \
                dialog.h
SOURCES       = wigglywidget.cpp \
                dialog.cpp \
                main.cpp

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/wiggly
#INSTALLS += target

RESOURCES += \
    rc.qrc
