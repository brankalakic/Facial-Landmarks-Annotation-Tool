# About This Fork

This fork integrates libfacedetection landmark detection (https://github.com/ShiqiYu/libfacedetection) into the tool. The binary is provided by the author under MIT license.

# Dependencies

The tool depends on Qt and the libfacedetect library that is used to initialize the annotations depends on Opencv 3.4.3. You should not have to install any of these because the precompiled libraries have been added to the folders of the flat.exe and libfacelandmark.exe respectively.

# Using the prebuilt version of the tool

You should be able to run the prebuilt flat.exe in Release-prebuilt folder by clicking on it or calling it from the command line. Once you have the tool running, you can use libfacedetection facial landmarks detection for initial estimate of the landmark locations. Just go to Tools in the menu of the Facial Annotation Tool and add the path to libfacelandmark (it is in fit-face-exe/libfacelandmark) first. More specifically, go to Tools->libfacedetection landmarks->Configure and choose YOUR_PATH/Facial-Landmarks-Annotation-Tool/fit-face-exe/libfacelandmark. You need to do this at most once with each start of the tool. After that for each image, go to Tools->libfacedetection landmarks->Fit Landmarks.

You also have the option of install Qt and building the tool from scratch. This is described in the next section.

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
