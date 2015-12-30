: REM BAT-file name pk2cc5x.bat
: REM %1=C:\PK2proj\                     path to the tool-chain
: REM %2=PIC16f690                       pic device name
: REM %3=C:\PK2proj\Work\hello_blink.c   path to c-sourcefile

@ECHO.
@ECHO -NOW COMPILING WITH CC5X


%1Cc5x\Cc5x.exe %3 -O%1Work\ -a

@ECHO.
@ECHO -NOW DOWNLOADING CODE WITH PK2CMD

: REM derive name of hex-file from path to c-file
@echo off
Set filename=%3
For %%A in ("%filename%") do (Set Name=%%~nxA)
set hexfile=%Name:.c=.hex%
echo on

%1PK2Cmd\pk2cmd -b%1PK2Cmd\ -p%2 -f%1Work\%hexfile% -a4.5 -m -r -t -jn
