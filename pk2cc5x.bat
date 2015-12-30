: REM BAT-file name pk2cc5x.bat
: REM %1=C:\PK2proj\                     path to the tool-chain
: REM %2=PIC16f690                       pic device name
: REM %3=C:\PK2proj\Work\                path to work directory
: REM %4=hello_blink.c                   File name
: REM %5=hello_blink                     File name without extension

@ECHO.
@ECHO -NOW COMPILING WITH CC5X

"%~1Cc5x\Cc5x.exe" "%~3%~4" -I"%~1Cc5x" -O%3 -a

@ECHO OFF
IF errorlevel 1 (
    exit %errorlevel%
)
@ECHO ON

@ECHO.
@ECHO -NOW DOWNLOADING CODE WITH PK2CMD

"%~1PK2Cmd\pk2cmd" -b"%~1PK2Cmd" -p%2 -f"%~3%~5.hex" -a4.5 -m -r -t -jn

@ECHO OFF
IF errorlevel 1 (
    exit %errorlevel%
)
@ECHO ON
