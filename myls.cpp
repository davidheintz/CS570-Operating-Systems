/*  CS570 - Assignment 1
    Professor Roche
    Maxx King, David Heintz
    2 February 2021

    This project is our own version of the ls command, which lists files in a directory. 
    Basic functionality: list files in current directory when no argument is provided. If the -h flag is present
    as an arguement, list all files in the directory. If no -h flag is present, only list the files that do not
    start with (.).
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <iostream>
#include <array>

int main(int argc, char **argv) 
{
    using namespace std;
    string arg1 = argv[1];
    bool hidden;
    if (argc == 1)                                      //if no command given, terminate program
    {
        std::cout << "No Command Given";
        terminate();
    }
    if(arg1.compare("myls") == 0)                       //First arg is function name
    {                                                   
        if(argc == 2)                                   //Check if command line arguements given
        {                                                   
            DIR *currdir = opendir("/");
            struct dirent *line1;                           //When no args given,
            while((line1 = readdir(currdir)) != NULL)       //Set working directory to current directory
            {
                std::string str1;
                str1 = line1 -> d_name;
                char f1 = str1.at(0);                   
                if(f1 != '.')                               //Check first char of filename to see if it 
                {                                           //is a hidden file.
                    std::cout << str1 << '\n';              //List all non hidden files
                }
            }
            closedir(currdir); 
            terminate();
        }

        int h;                                                                                                             
        string arg2 = argv[2];                          //-h flag will only show up in this position.
        if(arg2.compare("-h") == 0)                     //set boolean and starting position for loop
        {                                               //accordingly.
            h = 3;
            hidden = true;
        }
        else
        {
            h = 2;
            hidden = false;
        }

        for(int i = h; i < argc; i++)                   //For each command line arg:
        {
            std::cout << argv[i];
            std::cout << '\n';
            const char* path = argv[i];
            DIR *dir = opendir(path);                       //Set working directory to argument 
            if(dir != NULL)                                 //As long as the name is valid proceed
            {
                struct dirent *line;
                while((line = readdir(dir)) != NULL)            //Loop through current working directory
                {
                    std::string str;
                    str = line -> d_name;
                    char f = str.at(0);
                    if(hidden)                                      //If -h flag is present, print out everything
                    {
                        std::cout << str << '\n';
                    }
                    else                                            //Else only print files that dont start with (.)
                    {
                        if(f != '.')
                        {
                            std::cout << str << '\n';
                        }
                    }
                }
            }
            else                                            //If the argument is not a valid directory
            {                                               //Print out error message
                std::cout << "Cannot access " << argv[i] << '\n';
            }
            closedir(dir);                                  //Close directory before opening the next
            std::cout << '\n';                              //Additional newline for readability
        }
    }
}