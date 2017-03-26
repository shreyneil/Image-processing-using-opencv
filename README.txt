First install opencv in your system in your preferred partition.
I am installing it in the c drive

Steps to Set up Environmental Variable


- Right click on 'My Computer' and click 'Properties' in the drop down menu. 

If the system type is 64 bit operating system, the system architecture is x64.
If the system type is 32 bit operating system, the system architecture is x86.

 There are different builds for each version of Microsoft's Visual Studio compiler.

vc14: The compiler packaged with Visual Studio 2015
vc12: The compiler packaged with Visual Studio 2013
vc11: The compiler packaged with Visual Studio 2012
vc10: The compiler packaged with Visual Studio 2010
 
 I am going to use vc11 as the compiler type. You can find supporting compiler types of OpenCV, if you go to C:\opencv\build\x86 or C:\opencv\build\x64 according to your system architecture.

- Right click on 'My Computer' and click 'Properties' in the drop down menu.

- Click 'Advance System Settings' in the above window

- Then click 'Environment Variables

- Then click 'New' button at the bottom of the window

Type OPENCV_DIR against Variable name:. And type the location C:\opencv\build\ against the Variable value

Then press OK
Now you have added a new environment variable to the system.

Now you are going to edit a system variable.
click 'Path' or 'PATH' inside the list of System variables and then click 'Edit' button at the bottom of the window 

Then add a ; to the end of the line and add the following %OPENCV_DIR%\x86\vc11\bin  after the semicolon. x86 is your system architecture and vc11 is the compiler type. How to find your system architecture and compiler type is explained at the beginning of the post. (Don't delete anything. Just append it at the end of the line.)

You have completed the installation of OpenCV. Next thing you have to do is configuring Visual Studio.

Configure Visual Studio Express
Start Microsoft Visual Studio
Go to File>New Project...

now ,

- Go to templates and select visual c++ and select win32 type application out of the given options
- give an appropriate name to your project and set the desired location
- click ok 

a new window will appear
- select next and then check on empty project(select it)
- click finish 

Press 'Ctrl' key and then 'W' while holding the 'Ctrl' key in your keyboard. Release both keys. Then press 'S' in your keyboard. Then you will see the 'Solution Explorer' pane in your right or left side of the Visual Studio window. In my case, it is in the right side.

- select your project from the solution explorer
- double click on it and select resource files and right click on it
- a new window appears, select c++ header out of the options and select add


- Then right click on the project name (you have entered this name in a previous step) and then click 'Properties

- Choose Debug as the configuration and set platform as x86 or x64 depending on your system you can do this by opening the configuration manager. 
- select configuration properties,then select c/c++ and then select general. 
- Then copy and paste $(OPENCV_DIR)\include against the 'Additional Include Directories

- select linker and then select general
- then copy and paste $(OPENCV_DIR)\x86\vc11\lib against the 'Additional Library Directories' 

- select linker and then select input
- select the drop down button on additional dependencies and click on edit
After you click the <Edit...> . dialog box will appear and you have to copy and paste following library file names. If you are using a different version of OpenCV other than 2.4.9, please check the 'C:\opencv\build\x86\vc11\lib' location for respective file names.
opencv_calib3d245d.lib
opencv_contrib245d.lib
opencv_core245d.lib
opencv_features2d245d.lib
opencv_flann245d.lib
opencv_gpu245d.lib
opencv_haartraining_engined.lib
opencv_highgui245d.lib
opencv_imgproc245d.lib
opencv_legacy245d.lib
opencv_ml245d.lib
opencv_nonfree245d.lib
opencv_objdetect245d.lib
opencv_photo245d.lib
opencv_stitching245d.lib
opencv_superres245d.lib
opencv_ts245d.lib
opencv_video245d.lib
opencv_videostab245d.lib

These are some of the file names, you can find in the 'C:\opencv\build\x86\vc11' location.
Now click OK

use f7 to build and ctrl+f5 for running the debugger.



