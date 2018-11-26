# About This Fork

This fork integrates libfacedetection landmark detection (https://github.com/ShiqiYu/libfacedetection) into the tool. The binary is provided by the author under MIT license.

# Dependencies

You need to install Qt to make the tool work on your machine. You will have to set so the Qt bin folder in your environment variables or copy the needed dlls into the folder with the tool executable.

# Using the prebuilt version of the tool

Once you install Qt you should be able to run the prebuilt flat.exe in Release-prebuilt folder. Once you have the tool running, you can use libfacedetection facial landmarks detection for initial estimate of the landmark locations. Just go to Tools in the menu of the Facial Annotation Tool and add the path to libfacelandmark (it is in fit-face-exe/libfacelandmark). 

In some cases, this does not work and you will need to build the tool yourself. You can find more information on how to do that in the next section.

# FLAT - Facial Landmarks Annotation Tool

A visual editor for manually annotating facial landmarks in images of human faces.

![Screenshot](screenshot.png)

## Usage

Create a new face annotation dataset (files with extension `.fad`) and add the face images. Then, add the facial features and connect then as desired using either the program menus or the context menu. The zoom level can be controlled either from the widget control on the image properties tool window or by holding CTRL and scrolling the mouse wheel. While zoomed, an image can also be side scrolled by holding SHIFT and scrolling the mouse wheel. All images in the same face annotation dataset share the same model, that is they have the same amount of face landmarks (even though they can be differently positioned for each image). Automatically fitting of 66 face landmarks can be performed via the "Fit Landmarks" option if the utility is available (see details bellow). If the automatic fitting succeeds, the 66 landmarks will be positioned as best as possible in the face image. Otherwise, a status bar message will indicate the error.

## Dependencies

The application has been developed and tested with:

- [CMake](https://cmake.org/) 3.5.0-rc3
- [Qt](http://www.qt.io/) 5.5.1 32-bit

In order to use libfacedetection facial landmarks, go to Tools in the menu of the Facial Annotation Tool and add the path to 
libfacelandmark (it is in fit-face-exe/libfacelandmark). 

## Building

1. Use CMake to configure and generate the environment. I suggest using the folder `build`, since it is the one ignored by gitignore.
2. In Windows, open the Visual Studio solution and build with the desired build type (*debug*, *release*, etc).
3. In Linux, use type `make` to let the Makefile produce the binary in the build type configured by CMake.
4. The code produces only a single executable named `flat(.exe)`, that depends only on Qt. 

## Credits

Copyright (C) 2016 [Luiz Carlos Vieira](http://www.luiz.vieira.nom.br). Available under GPL (see details in the license file).

The application icons and images are either from or based on the Oxygen Icons Set, downloaded as [PNGs from Felipe Azevedo (pasnox)](https://github.com/pasnox/oxygen-icons-png) and [licensed under LGPL from KDE](https://techbase.kde.org/Projects/Oxygen/Licensing), and the [Farm-Fresh Web Icons Set](http://www.fatcow.com/free-icons), licensed under [Creative Commons (CC BY 4.0)](http://creativecommons.org/licenses/by/4.0/).
