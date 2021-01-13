Name: Ceilidh Torrance
Class: CSC 360 - Operating Systems

This is a Shell I wrote for a class I took in my third year of University. It has the ability to execute some basic,
built in commands such as change directory (cd), print current directory (pwd), set environment variable (set <var> <val>),
unset environment variable (unset <var>), and provide help to the user (help).The shell also has the ability to fork and
run a child process such as another program created by the user.

Comments are provided within the code to give a description of each function. 

During the creation of my shell I took inspiration and tips from the following sources:

Title: Tutorial - Write a Shell in C
Author: Stephan Brennan
Date: January 16, 2015
Type: Online shell code
Availability: https://brennan.io/2015/01/16/write-a-shell-in-c/

Title: What are Environment Variables, and how do I use them?
Author: Jacob Sorber
Date: February 15, 2019
Type: YouTube video with code
Availability: https://www.youtube.com/watch?v=ADh_OFBfdEE

Title: EOF, getc() and feof() in C
Author: Karthikeya Boyini
Date: November 5, 2018
Type: Code tutorial
Availability: https://www.tutorialspoint.com/eof-getc-and-feof-in-c

Some code tips and help were also taken from the tutorial slides posted on CourseSpaces.

Bugs:
I know that there is a problem with my code where if you hit enter without typing anything into the line it will exit the shell.
The reason this happens is that it sees it as the end of the file and I ran out of time to fix this.
After running numerous tests on my shell on my own computer and after ssh-ing into the school server I believe this is the only bug.
