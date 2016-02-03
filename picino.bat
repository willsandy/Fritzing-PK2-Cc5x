@ECHO OFF
: REM BAT-file name picino.bat
: REM PIC C-code wrapped inside FRITZING platform ARDUINO
: REM %6 parameter will be the total path to the sourcefile <name>.ino

: REM path to this bat file directory
set current=%~dp0

: REM derive different parts of path to sourcefile
Set pathname=%6
For %%a in ("%pathname%") do (
    set filename=%%~nxa
    set filepath=%%~dpa
)

set cfile=%filename:.ino=.c%
set ctarget=%filepath%%cfile%
set hexfile=%filename:.ino=.hex%
set hextarget=%filepath%%hexfile%

@ECHO.
@ECHO -NOW COPYING C-SOURCE

copy /y %6 %ctarget%

@ECHO OFF
IF errorlevel 1 (
    exit %errorlevel%
)

@ECHO.
@ECHO -NOW COMPILING WITH CC5X

%current%Cc5x\Cc5x.exe %ctarget% -O%filepath% -a

@ECHO OFF
IF errorlevel 1 (
    exit %errorlevel%
)

@ECHO.
@ECHO -NOW DOWNLOADING HEX-CODE WITH PK2CMD

%current%PK2Cmd\pk2cmd.exe -b%current%PK2Cmd\ -pPIC16f690 -f%hextarget% -a4.5 -m -r -t -jn





