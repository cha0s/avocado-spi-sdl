TARGET = GraphicsService-sdl

include(../../../core/Graphics/Graphics.pri)

SOURCES += \
	\
	SdlGraphicsService.cpp \
	\
	SdlCanvas.cpp SdlImage.cpp SdlWindow.cpp

HEADERS += \
	\
	SdlGraphicsService.h \
	\
	SdlCanvas.h SdlImage.h SdlWindow.h

win32:LIBS += -lSDLmain -lws2_32 -lwsock32
LIBS += -lSDL -lSDL_gfx -lSDL_image
