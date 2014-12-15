### This Makefile was written for nmake. ###
CC       = cl
RM       = del /F
MACROS   = /D_CRT_SECURE_NO_WARNINGS /DNDEBUG
CFLAGS   = /nologo /O2 /W4 /c $(MACROS)
LDFLAGS  = /nologo /O2
TARGET   = minesweeper.exe
OBJ      = $(TARGET:.exe=.obj)
SRC      = $(TARGET:.exe=.c)


.SUFFIXES: .c .obj .exe
.obj.exe:
	$(CC) $(LDFLAGS) $** /Fe$@ $(LDLIBS)
.c.obj:
	$(CC) $(CFLAGS) $** /Fo$@


all: $(TARGET)

$(TARGET): $(OBJ)

$(OBJ): $(SRC)


clean:
	$(RM) $(TARGET) $(OBJ)
cleanobj:
	$(RM) $(OBJ)
