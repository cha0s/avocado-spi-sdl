TARGET = TimingService-sdl

include(../../Abstract/Timing/Timing.pri)

SOURCES += \
	\
	SdlTimingService.cpp \
	\
	SdlCounter.cpp

HEADERS += \
	\
	SdlTimingService.h \
	\
	SdlCounter.h

win32:LIBS += -lSDLmain -lws2_32 -lwsock32
LIBS += -lSDL -lSDL_gfx -lSDL_image
	