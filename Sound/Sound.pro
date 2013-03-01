TARGET = SoundService-sdl

include(../../Abstract/Sound/Sound.pri)

SOURCES += \
	\
	SdlSoundService.cpp \
	\
	SdlSample.cpp SdlMusic.cpp

HEADERS += \
	\
	SdlSoundService.h \
	\
	SdlSample.h SdlMusic.h

#win32:LIBS += -lSDLmain -lws2_32 -lwsock32
LIBS += -lSDL -lSDL_mixer 
