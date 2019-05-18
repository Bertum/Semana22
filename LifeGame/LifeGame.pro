QT          += widgets

HEADERS     = glwidget.h \
              cell.h \
              helper.h \
              widget.h \
              window.h
SOURCES     = glwidget.cpp \
              cell.cpp \
              helper.cpp \
              main.cpp \
              widget.cpp \
              window.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/2dpainting
INSTALLS += target
