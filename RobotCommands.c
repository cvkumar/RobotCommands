#include <stdio.h>
#include <string.h>
#include "MyroC.h"
#include "scale-notes.h" 
#include <stdlib.h>

// Define the Functions

//Preconditions: duration is a real, positive, value.
//Postconditions: Robot moves forward for given duration at a speed of 1.
void goForward (double duration) 
{
  rForward(1.0, duration);
}

//Preconditions: duration is a real, positive, value.
//Postconditions: Robot moves forward for given duration at a speed of 1.
void goBackward (double duration)
{
  rBackward(1.0, duration);
}

//Preconditions: speed is a real, positive, value between 1 & 2.
//Postconditions: Robot turns right for given speed for one second.
void goRight (double speed) 
{
  rTurnRight (speed, 1);
}

//Preconditions: speed is a real, positive, value between 1 & 2.
//Postconditions: Robot turns left for given speed for one second.
void goLeft (double speed)
{
  rTurnLeft (speed, 1);
}
//Preconditions: duration is a real, positive, value.
//Postconditions: Robot travels in a triangle at a speed of one
// and the given duration represents the triangle's side length.
void triangle (double duration) 
{
  rForward(1.0, duration);
  rTurnRight(1.0, 1.15);
  rForward(1.0, duration);
  rTurnRight(1.0, 1.15);
  rForward(1.0, duration);
}

//Preconditions: NONE
//Postconditions: Robot sings "I want it that way" ~ Backstreet Boys.
void sing ()
{
  /*I want it that way Intro */
  rBeep (0.3, pitchFs5); 
  rBeep (0.3, pitchCs6);
  rBeep (0.3, pitchA5) ;
  rBeep (0.3, pitchFs5);
  rBeep (0.3, pitchD6);
  rBeep (0.3, pitchCs6) ;
  rBeep (0.3, pitchFs5);
 
  rBeep (0.3, 100);  /* eigth break (our eights are 0.3 instead of 0.25) */
 
  rBeep (0.3, pitchFs5);
  rBeep (0.3, pitchD6);
  rBeep (0.3, pitchE5);
  rBeep (0.3, pitchA5);
  rBeep (0.3, pitchE6);
  rBeep (0.3, pitchA5);

  rBeep (0.3, 100); /* eigth break */

  rBeep (0.3, pitchFs5);
  rBeep (0.3, pitchCs6);
  rBeep (0.3, pitchA5);
  rBeep (0.3, pitchFs5);
  rBeep (0.3, pitchD6);
  rBeep (0.3, pitchCs6);
  rBeep (0.3, pitchFs5);

  rBeep (0.3, 100); /* eigth break */

  rBeep (0.3, pitchFs5);
  rBeep (0.3, pitchD6);

  rBeep (0.3, 100); /* eigth break */

  rBeep (0.3, pitchE5);
  rBeep (0.3, pitchA5);

  rBeep (0.3, 100); /* eigth break */
  
  /* Verse beginning : You are my fire */
  rBeep (0.3, pitchFs5);
  rBeep (1.5, pitchA5);
  rBeep (0.6, pitchCs6);
  rBeep (0.9, pitchFs5);
  rBeep (.9, pitchE5);

  /* The one */
  rBeep (0.3, pitchFs5);
  rBeep (1.5, pitchA5);

  /* Desire */
  rBeep (0.6, pitchCs6);
  rBeep (0.9, pitchFs5);
  rBeep (0.3, pitchB5);

  /* Believe */
  rBeep (0.6, pitchA5);
  rBeep (0.3, pitchFs5);

  /* When I say */ 
  rBeep (2.1, pitchA5);
  rBeep (0.6, pitchCs6);
  rBeep (0.9, pitchFs5);

  /* I want it that way */
  rBeep (0.9, pitchE5);
  rBeep (0.3, pitchFs5);
  rBeep (0.9, pitchFs5);
  rBeep (0.9, pitchA5);
  rBeep (0.6, pitchCs6);
  rBeep (0.9, pitchB5);
  rBeep (0.9, pitchA5);

  /*Tell me why */
  rBeep (0.3, pitchCs6);
  rBeep (0.3, pitchE6);
  rBeep (0.3, pitchE6);
  rBeep (0.3, pitchFs6);

  /* Aint nothing but a */
  rBeep (0.6, pitchE6);
  rBeep (0.3, pitchD6);
  rBeep (0.3, pitchCs6);
  rBeep (0.3, pitchB5);
  rBeep (0.3, pitchA5);

  /* Heartache */
  rBeep (1.2, pitchGs5);
  rBeep (1.2, pitchA5);
  
}

//Preconditions: repetitions is a positive integer.
//Postconditions:Robot dances by shuffling for the given amount of repetitions.
void dance (int repetitions)
{
  int k;
  for (k = 0; k < repetitions; k++)
    {
      rTurnRight (1, 0.25);
      rTurnLeft (1, 0.25);
    }
}

//Preconditions: None
//Postconditions: Robot takes picture and then shows it.
void picture()
{  
  Picture * pic;
  pic = rTakePicture();
  rShowPicture (pic);
}
//Preconditions: None
//Postconditions: The robot's battery voltage is printed.
void battery ()
{
  printf("Battery voltage is =  %lf \n", rGetBattery());
}

//Preconditions: None
//Postconditions:Program's tasks are completed and the robot is disconnected
void quit ()
{
  printf("Tasks completed \n");
  rDisconnect ();
}


int main(int argc, char *argv [])
{
  //Declarations
  rConnect("/dev/rfcomm0"); // Connect to robot
  int i;
  int j;
  int readMode = 0;
  int writeMode = 0;
  FILE * filer; //read file
  FILE * filew; //write file
  int k = 1;
  char fileName[20]=""; //set filename to empty spaces
  char fileNameW[20];
  char input[10]; // The Input string
  double parameter; // Duration used in several functions
  char line[10]; // The string to be read from

  //Check if any arguments on the command line were -r or -w, if they are
  //then set their respective mode
  for (i=1 ; i < argc; i++)
    {
      if (strcmp (argv[i], "-r") == 0)
        {
          readMode = 1; // to set readMode
        }
      else if (strcmp (argv[i], "-w") == 0)
        {
          writeMode = 1; // to set writeMode
        }
    } // end loop

  //If neither readMode or writeMode specified then quit program with an error
  if (readMode == 0 && writeMode == 0)
    {
      printf("Please choose either -w or -r for processing \n");
      return 0;
    }

  //If either readMode and writeMode specified, find the filename specified
  if (readMode == 1 || writeMode == 1)
    {
  
      for (i=1 ; i < argc; i++)
        {
          if (strcmp (argv[i], "-r") != 0 && argv[i] != NULL && 
              strcmp (argv[i], "-w") != 0)
            {
              strcpy(fileName, argv[i]);
            }
        } // end loop
    }

  //If no filename specified, ask for one from user
  if (strcmp (fileName, "") == 0)
    {
      printf("Please enter a fileName \n");
      printf("File Name =");
      scanf("%s",&fileName);
      printf("\n");
    }


  // For Both ReadMode AND/OR WriteMode
  if (readMode == 1)
    {
      filer = fopen(fileName, "r"); //open specified filename
      //if writeMode too, then ask user for filename to write on
      if(writeMode == 1)
        {
          printf("Please Enter a filename to write \n"); 
          printf("Filename =");
          scanf("%s",&fileNameW);
          printf("\n");
          filew = fopen(fileNameW, "w");
        }

      //Stop running commands when file is empty
      //otherwise run each command given through the file
      while(fgets(line, 10, filer))
        {
          fscanf(filer,"%lf", &parameter); // receive parameter for procedures
          printf("Parameter = %lf \n", parameter);
          while (fgetc(filer) != '\n'); // Ignore rest of the line
          
          // Get rid of the empty spaces
          j=0;
          while(line[j] != ' ')
            {
              printf("For Line = %c, j = %d \n", line[j], j);
              j++;
            }
          line[j] = '\0'; // given an NULL char to end of command string

          //Do the given Command with the specified parameter, 
          //while writing down the commands if also in writeMode
          //command if also in writeMode
          //Go Forward
          if (strcmp(line,"Forward")==0)
            {
              goForward(parameter);
              if (writeMode == 1)
                fprintf(filew, "%s  %lf\n", line, parameter);
            }  
          // Go backwards
          else if (strcmp(line,"Backward")==0)
            {
              goBackward(parameter);
              if (writeMode == 1)
                fprintf(filew, "%s  %lf\n", line, parameter);
            }
          // Turn Right
          else if (strcmp(line,"Right")==0)
            {
              goRight(parameter);
              if (writeMode == 1)
                fprintf(filew, "%s  %lf\n", line, parameter);
 
            }
          // Turn left
          else if (strcmp(line,"Left")==0)
            {
              goLeft(parameter);
              if (writeMode == 1)
                fprintf(filew, "%s  %lf\n", line, parameter);
            }
          // Sing
          else if (strcmp(line,"Sing")==0)
            {
              sing(); //Sing "I Want It That Way" by Backstreet Boys
              if (writeMode == 1)
                fprintf(filew, "%s  %lf\n", line, parameter);
            }
          //Dance for given repetitions
          else if (strcmp(line,"Dance")==0) 
            {
              dance(parameter);
              if (writeMode == 1)
                fprintf(filew, "%s  %lf\n", line, parameter);
            }
          //Move in a triangle with given side-length = duration
          else if (strcmp(line,"Triangle")==0) 
            {      
              triangle(parameter); 
              if (writeMode == 1)
                fprintf(filew, "%s  %lf\n", line, parameter);
            }

          //Take and display a picture
          else if (strcmp(line,"Picture")==0) 
            { 
              picture(); 
              if (writeMode == 1)
                fprintf(filew, "%s  %lf\n", line, parameter);
            }

          //Display Battery Voltage
          else if (strcmp(line,"Battery")==0) 
            { 
              battery(); 
              if (writeMode == 1)
                fprintf(filew, "%s  %lf\n", line, parameter);
            }
          //Disconnect from robot, end the loop through "k"
          else if (strcmp(line,"Quit")==0) 
            { 
              quit();
              if (writeMode == 1)
                fprintf(filew, "%s  %lf\n", line, parameter);
              k = 0;
            }
          // If the input does not match menu options.
          else 
            {
              printf("Please choose a menu option and try again\n");
            }

        } // end while loop because all lines from file read
      return 0; //end program when tasks completed
    } // end outer if statement

  // For just Write Mode
  if (writeMode == 1)
    {
      filew = fopen(fileName, "w"); // open file to write on
      while (k) // It is one, unless the Quit function is executed
        {
          parameter = 0;
          // Print the menu
          printf ("Menu Options\n");
          printf ("  Forward - Go Forward\n");
          printf ("  Backward - Go Backwards\n");
          printf ("  Right - Turn Right\n");
          printf ("  Left - Turn Left\n");
          printf ("  Sing - Sing \n");
          printf ("  Dance - Dance\n");
          printf ("  Triangle - Move in triangle\n");
          printf ("  Picture - Take a picture \n");
          printf ("  Battery - Get battery status\n");
          printf ("  Quit - Quit Program\n");
          printf ("What is your command? ");
          scanf ("%s", &line);

          // Compare the input with the menu options
          // Go Forward
          //Write down the specified commands and parameters in the given file
          if (strcmp(line,"Forward")==0)
            {
              printf ("Enter the duration \n");
              scanf ("%lf", &parameter); //how long should robot move forward?
              goForward(parameter);
              fprintf(filew, "%s  %lf\n", line, parameter);
            }  
          // Go backwards
          else if (strcmp(line,"Backward")==0)
            {
              printf ("Enter the duration \n");
              scanf ("%lf", &parameter); //how long should robot move backward?
              goBackward(parameter);
              fprintf(filew, "%s  %lf\n", line, parameter);
            }
          // Turn Right
          else if (strcmp(line,"Right")==0)
            {
              printf ("Enter the speed (a value between 0 and 1)\n");
              scanf ("%lf", &parameter); //how fast should robot turn right?
              goRight(parameter);
              fprintf(filew, "%s  %lf\n", line, parameter);
            }
          // Turn left
          else if (strcmp(line,"Left")==0)
            {
              //how fast should robot turn right?
              printf ("Enter the speed (a value between 0 and 1)\n");
              scanf ("%lf", &parameter);
              goLeft(parameter);
              fprintf(filew, "%s  %lf\n", line, parameter);
            }
          // Sing
          else if (strcmp(line,"Sing")==0)
            {
              sing(); //Sing "I Want It That Way" by Backstreet Boys
              fprintf(filew, "%s  %lf\n", line, parameter);
            }
          //Dance for given repetitions
          else if (strcmp(line,"Dance")==0) 
            {
              printf ("Enter an integer number of repetitions\n");
              scanf ("%d", &parameter);
              dance(parameter);
              fprintf(filew, "%s  %lf\n", line, parameter);
            }
          //Move in a triangle with given side-length = duration
          else if (strcmp(line,"Triangle")==0) 
            {      
              printf ("Enter the duration\n");
              scanf ("%lf", &parameter);
              triangle(parameter); 
              fprintf(filew, "%s  %lf\n", line, parameter);
            }

          //Take and display a picture
          else if (strcmp(line,"Picture")==0) 
            { 
              picture();
              fprintf(filew, "%s  %lf\n", line, parameter);
            }

          //Display Battery Voltage
          else if (strcmp(line,"Battery")==0) 
            { 
              battery();
              fprintf(filew, "%s  %lf\n", line, parameter);
            }
          //Disconnect from robot, end the loop through "k" 
          else if (strcmp(line,"Quit")==0) 
            { 
              quit();
              k = 0;
              fprintf(filew, "%s  %lf\n", line, parameter);
            }
          // If the input does not match menu options.
          else 
            {
              printf("Please choose a menu option and try again\n");
            }
        } // End the while loop
 
    } // End of outer if statement
  return 0; // end Program
} // end Main





