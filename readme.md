# Fritzing-PK2-Cc5x

![Fritzing PIC](img/fritzing_pic16.gif)

## Toolchain environment

![Toolchain folders](img/toolchain_folders.gif)

The toolchain for programming and downloading code to midrange PIC-processors consists of a C-compiler and a PK2-downloader. These programs must be downloaded from external sources.

A batfile `pk2cc5x.bat` will execute the programs `CC5X.EXE` and `pk2cmd.exe` in sequence.


## Cc5x Compiler

![Cc5x - folder](img/cc5x_folder.gif)

[Visit Cc5x homepage](http://www.bknd.com/cc5x/)

Download page [http://www.bknd.com/cc5x/downl-stud.shml](http://www.bknd.com/cc5x/downl-stud.shml)

Download  `cc5xfree.zip`  and unzip all (300) files to folder `Cc5x`.

The executable file is `CC5X.EXE`.

## PK2Cmd folder

![PK2Cmd - folder](img/pk2_folder.gif)

Download page [http://ww1.microchip.com/downloads/en/DeviceDoc/pk2cmdv1-20.zip](http://ww1.microchip.com/downloads/en/DeviceDoc/pk2cmdv1-20.zip)

Download `pk2cmdv1-20.zip` and unzip all (4) files to this folder. The executable file is `pk2cmd.exe`.

## Toolchain setup in Fritzing

![Edit - Preferences - Path to toolchain](img/edit_preferences.gif)

In Fritzing you have to Browse to the toolchain folder. In **Edit** Menu choose **Preferences**. In **preferences** choose **Code View** tab and Browse to the location of the toolchain. Select the file  `pk2cc5x.bat`. Click on **OK**.

## Work folder optional 

![Work - folder](img/work_folder.gif)

This folder is optional and can be used for your sourcefiles. Or you store them somewhere else.
