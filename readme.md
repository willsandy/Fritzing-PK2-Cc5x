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

## Usage on linux

### Cc5x compiler
To run the Cc5x compiler you need wine. All major linux distributions
includes wine so install it using the package manager. On
ubuntu/debian:
```
sudo apt-get install wine
```

Now download and unpack the Cc5x compiler to the `Cc5x` directory as
described in the Windows instructions or from the command line issue
the following commands:

```
cd Cc5x
wget http://www.bknd.com/cc5xfree.zip
unzip cc5xfree.zip
```
(If you do this be sure that you agree with the
[terms of use](http://www.bknd.com/cc5x/downl-stud.shtml))

### PK2Cmd
To use with linux download
[PK2Cmd for linux from Microchip](http://ww1.microchip.com/downloads/en/DeviceDoc/pk2cmdv1-20Linux2-6.tar.gz)
into the `PK2Cmd` folder and unpack it into it. On the command line
this equals:

```
cd PK2Cmd
wget http://ww1.microchip.com/downloads/en/DeviceDoc/pk2cmdv1-20Linux2-6.tar.gz
tar zxf pk2cmdv1-20Linux2-6.tar.gz
```
