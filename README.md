# fydp-console-sw

This is a visual studio express 2012 project.  Download visual studio express 2012 from (free registration key with MS account):

https://www.microsoft.com/en-ca/download/details.aspx?id=34673

The visual studio project has been set up with PARTIAL ANSI C compatibility (double slash comments still work),
but other C99 features do not.
Visual studio 2013 and higher begin to use C99, therefore this is the best for our purposes on windows.

Forum discussion: http://www.cplusplus.com/forum/general/145334/

The only application file is main.c.  All other development is done within header files
to not have a complicated makefile and to
be able to work outside of windows easily via command line.
There are no other .c files in this repo.


gcc main.c -ansi -o main


See below for helpful links to sw development with TI board:

https://docs.google.com/document/d/1k4nRw4o-ZgncXD56vZib3MPRxPhCtg2E16HcLDE5ESY/edit