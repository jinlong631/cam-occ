######################################################################
# Automatically generated by qmake (2.01a) Tue May 18 20:38:03 2010
######################################################################

TEMPLATE = lib

CONFIG -= thread
CONFIG += opengl
CONFIG += x11
CONFIG += debug
CONFIG -= release

DEFINES += _OCC64 LIN LININTEL 
DEFINES += HAVE_CONFIG_H HAVE_IOSTREAM HAVE_FSTREAM HAVE_LIMITS

QMAKE_CXXFLAGS_DEBUG += -m64
QMAKE_CXXFLAGS_RELEASE += -m64

DEPENDPATH += . ../qocc
INCLUDEPATH += /opt/occ63/inc/ . ../qocc

LIBS += -L/opt/occ63/lib/ \
-lTKShHealing -lTKOffset -lTKBool -lTKSTEPBase -lTKSTEP \
-lTKService -lTKV3d -lTKernel -lTKIGES -lPTKernel -lTKSTL \
-lTKVRML -lTKTopAlgo -lTKBRep -lTKPShape -lTKShapeSchema

# Input
HEADERS += lnk.hh uio.hh
SOURCES += lnk.cc uio.cc


DESTDIR = ../../bin
TARGET = CommonOcc

OBJECTS_DIR = .obj/
UI_DIR = .ui/
MOC_DIR = .moc/
