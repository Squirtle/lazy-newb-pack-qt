System Requirements
-------------------
Currently, the only operating system supported is Linux, but support for OS X and Windows are planned in the future. You can try compiling and running the GUI on Windows or OS X, but things may break.

Dependencies
------------
The only dependency for the qt Lazy Newb Pack GUI is qt 4.8, though Dwarf Fortress itself requires GTK+ 2+, SDL 1.2+, and SDL_image. Since you will need to compile the qt LNP GUI, you will need the qt headers as well. If you are using a distribution which separates these from the main package, such as Ubuntu or Debian, this means installing the dev package.

Install
-------
To install the qt Lazy Newb Pack GUI, you will first need a copy of the Windows version of the LNP, which you can grab at http://dffd.wimbli.com/file.php?id=2801 or http://www.mediafire.com/?hwcjhh5j4jyus.

Once you have downloaded and extracted the Windows version of the LNP, delete the Dwarf Fortress folder and replace it with a folder with the linux version of DF. The name of the folder has to contain the string 'Dwarf Fortress' (without quotes) to work.

Then use the qmake && make && make clean command to compile the GUI, and copy the Lazy Newb Pack executable to the folder of the windows version of the LNP.

Goals
-----
The primary goal of this project is to provide a cross-platform version of the LNP which is functionally equivalent to the Windows version. When this goal is reached, additional functionality will be considered.

Progress
--------
GUI (Partially complete)
  Bottom buttons (Completed)
    Init editor (Completed)
  Tabs (Partially complete)
    Options tab (Completed)
    Graphics tab (Partially complete)
    Utilities tab (Not yet begun)
    Advanced tab (Completed)
  Menu (Partially complete)
OS X Compatibility (Not yet tested)
Windows Compatibility (Not yet tested)
Packaging (Not yet begun)
