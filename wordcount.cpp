/*  CS570 - A2
    Professor Roche
    Maxx King, David Heintz
    25 February 2021
*/


//Header Files:
//For reading from file
#include <fstream>
//For cout
#include <iostream>
//For threads
#include <stdio.h>
#include <pthread.h>
//For filesize
#include <sys/stat.h>

using namespace std;

//Data structure for thread progress
struct status {
long * CurrentStatus;
long InitialValue = 0;
long TerminationValue;
} PROGRESS_STATUS;

struct stat buffer;

void * progress_monitor(void *) 
{
    /*
    increment progress bar based on currentvalue and terminationvalue
    if > 1/50 progress has been made since currtick value, add more ticks
    once currtick = 50, finish progress bar, end thread
    */
    int currtick = 0;
    long curval = 0;
    long fval = PROGRESS_STATUS.TerminationValue;
    int ticks = 0;
    while (currtick < 50) 
    {
	    curval = *PROGRESS_STATUS.CurrentStatus;
	    if(curval >= fval) //if terminationvalue reached
	    {
		    ticks = 50 - currtick; //ticks becomes amount to reach 50 from currtick
	    }
	    else
	    {
		    ticks = curval / (fval / 50) - currtick; //get number of ticks needed to draw each time
	    }
	    while(ticks > 0)
	    {
            //print the number of ticks needed to get to currtick = curval / (fval / 50) <- current progress
            //print "+" every 10 ticks (10,20,30,40,50) and "-" for every other
            currtick++;
	        if (currtick % 10 == 0)
            {
                cout << "+" << flush; 
            }
            else
            {
                cout << "-" << flush;
            }
	        ticks--;        
	    }
    }
    std::cout << "\n"; //newline
    return NULL;
}

long wordcount(string argv)
{
    PROGRESS_STATUS.CurrentStatus = new long; //initialize pointer
    
    //using stat to set TerminationValue to size of file
    stat(argv.c_str(), &buffer);
    long fcount = (long) buffer.st_size; 
    PROGRESS_STATUS.TerminationValue = fcount;
    //Variables for wordcount
    fstream file;
    long wcount = 0;
    long ccount = 0;
    char ch;
    bool ct = false; //ct is false if currently in white space and true if currently in word

    //Set up data structure for progress monitor
    void * pVoid = &PROGRESS_STATUS;
    pthread_t thread1;
    
    //Open parameter, only 1 file
    file.open(argv.c_str());
    file.unsetf(ios_base::skipws); //dont skip white space characters
    //Verify file was able to be opened
    if(file)
    {

        //Spawn progress monitor thread
        int r = pthread_create(&thread1, NULL, progress_monitor, pVoid);
        //count every character in file
        while (file >> ch)
        {	
		    ccount++;
		    *PROGRESS_STATUS.CurrentStatus = ccount;
            //if whitespace and previously wasnt, increment wordcounter
            if (std::iswspace(ch) != 0 && ct == true)
            {
                wcount++;
                ct = false;       		
		    }
            else
	    	{
                //if not whitespace and previously was, set boolean to true (meaning currently within a word)       
                if (std::iswspace(ch) == 0 && ct == false)
			    {
                    ct = true;
			    }
	    	}
        }
        //handle for possible uncounted word
        if (ct == true)
        {
            wcount++;
        }
        //if progress_monitor hasnt finished (wordcounter went too quickly)
        //then set to currentstate to terminationvalue so it will draw rest of bar
	    *PROGRESS_STATUS.CurrentStatus = PROGRESS_STATUS.TerminationValue;
        //Clean up
        file.close();
    }
    else    
    {
        //if not file, draw progress bar and return -1
	    *PROGRESS_STATUS.CurrentStatus = PROGRESS_STATUS.TerminationValue;
        pthread_join(thread1, NULL);
        return -1;
    }

    //Wait until thread is complete to return value
    pthread_join(thread1, NULL);
    return wcount;
}

int main(int argc, char *argv[]) 
{
    //Verify an arguement was given
    if(argc == 1)
    {
        cout << "No file specified";
        return -1;
    }


    //Call to function, will spawn new thread
    long wcount = wordcount(argv[1]);


    //Final output of wordcount, progress_monitor already complete
    //Error messgae if file could not be opened
    if(wcount != -1)
    {
        cout << "There are " << wcount << " words in " << argv[1] << ".\n";
    }
    else    
    {
        cout << "Could not open file \n";
    }
}