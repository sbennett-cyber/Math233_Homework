TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


## Stuff for running in parallel
macx:
{
QMAKE_CXXFLAGS += -Xpreprocessor -fopenmp -lomp -I/usr/local/include
}
macx:
{
QMAKE_LFLAGS += -lomp
}
macx:
{
LIBS += -L /usr/local/lib /usr/local/lib/libomp.dylib
}



SOURCES += \
        ../Important_Files/grid2d.cpp \
        ../Important_Files/math_tools.cpp \
        ../Important_Files/setup.cpp \
        ../Important_Files/sl_method.cpp \
        main.cpp

HEADERS += \
    ../Important_Files/cf_2.h \
    ../Important_Files/grid2d.h \
    ../Important_Files/math_tools.h \
    ../Important_Files/setup.h \
    ../Important_Files/sl_method.h
