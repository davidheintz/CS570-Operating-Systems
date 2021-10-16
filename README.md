# CS570-Operating-Systems

This repository contains assignments completed for the San Diego State University Operating Systems course (Computer Science 570).
The purpose of these assignments are to replicate functions performed by an operating system. 
These assignments were completed by myself and my partner Maxx King (github: Maxx-king) in Spring 2021. 

The first assignment (wordcount.cpp) reads in a file and counts the number of words. We also created a progress bar which recognizes the percent completion of the wordcount function, and depicts the progress accordingly. Once the progress bar is full, the function is complete and the word count is output

The second assignment (myls.cpp) lists the files in the directory input by the user. This program, along with the first, can be called in the terminal. This command is a result of the related makefiles 

The two makefiles are used to compile each program with the command "make" in the terminal so each can be run. The makefile for "myls" was renamed "makefile2"

The file "log.txt" contains the output of the myls.cpp program being run on my computer to test and show the directory listing capabilities 
