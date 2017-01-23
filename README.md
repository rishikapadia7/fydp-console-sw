# fydp-console-sw

This is a visual studio community 2015 project.  Download visual studio community 2015 from:

https://imagine.microsoft.com/en-us/Catalog/Product/101

http://www.kunal-chowdhury.com/2015/07/download-visualstudio-2015.html#F2rapsBJjshsO9zx.97


The visual studio project has been set up with ANSI C compatibility, therefore double slash comments
would generate compile errors as expected on the TI C6748 board compiler in Code Composer Studio. 

The only application file is main.c.  All other development is done within header files
to simplify the process of not having to create a complicated makefile and so that
or can even easily work by compiling via command line without the need of visual studio.
There are no other .c files in this repo.






