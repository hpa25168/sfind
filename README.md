<h1>NAME of Program: sfind.c</h1>

---------------------------------------------------------------------
This program takes directory name and list all files and sub directories in the directory. It can also filter certain files and look for certain words in name of the file.
---------------------------------------------------------------------

CODER: Het Patel
CREDIT/Contributions:


How to compile:
    gcc -Wall -g sfindFunction.c sfind.c -o sfind
or
make -f Makefile

How to run:
    sfind <directory-where to start looking> -n substring-criteria -t <filetype>
