# CH32V00x-X-SSD1306 library guide
## Information 
This library is provided for MountRiver studio IDE. You can use it where and when even you want.  
The code has been developped for CH32V00x range that include :  
* CH32V002  
* CH32V003  
* CH32V006  
* CH32V007  

Please, if you use it, do not remove my credits.

## Install
In order to install this library, just put the source files into your MountRiver studio project.  
You can both put the headers ```( .h )``` and the sources ```( .c )``` into the "User" sub-directory.  

## Hardware specifications

You can find the datasheet there : https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf  

## Use 

In order to use this library, you have to include the header at the beginnig of the c file where you want to use it.  

/!\ Warning : The CH32V00x series µC has only 1 I2C device.  
That's mean you have to connect your display on the PC1 ```( SDA )``` and PC2 screen ```( SCK )```.    

/!\ Warning : Most of the SSD1306 have the ```I2C``` address ```0x3C``` or ```0x3D```.  

### Documentation  

Have to be write 

## Tools 

In order to enhance my library's ergonomics, I made a python application that provide multiple solutions to make font and create image for the display. 

This application should be released in the same time as the version 1.2 of my library.  

You can find the [repo here](https://github.com/Ign555/SSD1306-convert-tool).  

## Changelog

18/04/2025 : Add multiple bit format ( multiple font size )  

17/04/2025 : End the test font  

05/04/2025 : Add a writer function and started to implement a text font  

04/04/2025 : Add ```LICENSE.md```   

02/04/2025 : CH32V003F4P6-X-SSD1306 v1.1 release  
* The driver can now be use with SSD1306 128*64 format

01/04/2025 : Make the readme

31/03/2025 : CH32V003F4P6-X-SSD1306 v1.0 release  
* Add basic functions for SSD1306 128*32

## To do list

* Test multiple font size
* Make tool for image

### License

This library is provided under BSD 3-Clause License. 
For more information, please look in LICENSE.md 

Please, if you have any suggest/question contact me on contact@ingeno.fr
