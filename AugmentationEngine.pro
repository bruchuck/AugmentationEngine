#-------------------------------------------------
#
# Project created by QtCreator 2016-04-17T00:32:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AugmentationEngine
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Graphics/graphicsscene.cpp \
    augmentationtree.cpp \
    augmentationnode.cpp \
    logmanager.cpp \
    Graphics/graphicnode.cpp \
    Graphics/graphicedge.cpp \
    Nodes/affineRotation.cpp \
    Nodes/flipimage.cpp \
    dialog_newtree.cpp \
    dialog_parameters.cpp \
    Nodes/translation.cpp \
    Nodes/scaleimage.cpp \
    Nodes/blurimage.cpp \
    Nodes/noiseimage.cpp \
    Nodes/warpimage.cpp \
    Nodes/brightnessimage.cpp \
    Nodes/contrastimage.cpp

HEADERS  += mainwindow.h \
    Graphics/graphicsscene.h \
    augmentationtree.h \
    augmentationnode.h \
    logmanager.h \
    defenums.h \
    Graphics/graphicnode.h \
    Graphics/graphicedge.h \
    Nodes/affineRotation.h \
    Nodes/flipimage.h \
    dialog_newtree.h \
    dialog_parameters.h \
    Nodes/translation.h \
    Nodes/scaleimage.h \
    Nodes/blurimage.h \
    Nodes/noiseimage.h \
    Nodes/warpimage.h \
    Nodes/brightnessimage.h \
    Nodes/contrastimage.h

FORMS    += mainwindow.ui \
    dialog_newtree.ui \
    dialog_parameters.ui

#win32:CONFIG(release, debug|release): LIBS += -L$$(OPENCV_DIR)/lib/ -lopencv_world310
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$(OPENCV_DIR)/lib/ -lopencv_world310d
win32:CONFIG(release, debug|release): LIBS += -LC:/opencv/build/x64/vc14/lib -lopencv_world310
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/opencv/build/x64/vc14/lib -lopencv_world310d

unix:CONFIG(release, debug|release): LIBS += -L/usr/lib/x86_64-linux-gnu -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab

#unix:CONFIG(release, debug|release): LIBS += 'pkg-config --cflags --libs opencv'


win32:INCLUDEPATH += C:/opencv/build/include
#unix:INCLUDEPATH +=/home/badmarques/aug/AugmentationEngine/opencv/release/include
unix:INCLUDEPATH +=/usr/include
win32:DEPENDPATH += C:/opencv/build/include
#unix:DEPENDPATH +=/home/badmarques/aug/AugmentationEngine/opencv/release/include
unix:DEPENDPATH += /usr/include/opencv

win32:CONFIG(release, debug|release): LIBS += -LC:\OGDF\x64\Release -logdf
else:win32:CONFIG(debug, debug|release){
LIBS += -LC:\OGDF\x64\Release -logdf
DEFINES += OGDF_DEBUG;
}
unix:CONFIG(release, debug|release): LIBS += -L/home/badmarques/libs/OGDF/_release -lOGDF -lCOIN -pthread



win32:INCLUDEPATH += C:/OGDF/include
unix:INCLUDEPATH +=/home/badmarques/libs/OGDF/include

win32:DEPENDPATH += C:/OGDF/include
unix:DEPENDPATH +=/home/badmarques/libs/OGDF/include


