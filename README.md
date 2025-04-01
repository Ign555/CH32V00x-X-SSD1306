# CH32V003F4P6-X-SSD1306 library guide
## Information 
This library is provided for MountRiver studio IDE. You can use it where and when even you want.  
Please, if you use it, do not remove my credits.

## Install
In order to install this library, just put the source files into your MountRiver studio project.  
You can both put the headers ```( .h )``` and the sources ```( .c )``` into the "User" sub-directory.  

## Hardware specification

You can find the datasheet there : https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf  

## Use 

In order to use this library, you have to include the header at the begginnig of the c file where you want to use it.  

/!\ Warning : The CH32V003F4P6 have only 1 I2C device.  
That's mean you have to connect your display on the PC1 ```( SDA )``` and PC2 screen ```( SCK )```.    

/!\ Warning : Most of the SSD1306 have the ```I2C``` address ```0x3C``` or ```0x3D```.  

### Documentation  

Have to be write 

## Changelog


01/04/2025 : Make the readme

31/03/2025 : CH32V003F4P6-X-SSD1306 v1.0 release  
* Add basic functions for SSD1306 128*32

Please, if you have any suggest/question contact me on contact@ingeno.fr
