# Goatware - Systems II Final Project

This project was created by Ben Clarke, Ryan Liu, and Evan Farrell.

The purpose of this project is to create some sort of virus software that 1. performs some sort of malicious activity to a user, and 2. uses network communication to send information to a remote server. Goatware is a malware which steals files and information from a user, and also subtly records a users keystrokes. Some of the main features of the malware include: 

The virus is implemented by using multiple c files that each cover one of these features of the malware, and then having a main c file (main.c) which combines all these methods into one operational virus file which is run. These files include:

- changeFiles.c: Makes copies of all the user’s files, and place these copies into the Goatware file folder. All of the user’s original files are then replaced by useless (goat-themed) files of the same type
- keylogger.c: Keylogger determines keys that the user pressed, held, and released
- renameProcess.c: Process name changed repeatedly to hide presence
- client.c and server.c: All information received from this Virtual Machine will be sent to another IP address using socket programming

###How to run the demonstration Goatware virus:
- In header.h and server.c changed the definition of SRV_IP to equal the ip of the machine used as the server "stealing" the files
- compile and run server.c on the "attacking" machine

- Go to the address of the malware on the "victim" machine
- Next, the user must type the command `make` into the terminal to run the makefile needed to compile the code.
- the user must then type the command `sudo ./main.c` into the terminal to run the actual virus.

###How to stop the PID Changin
-enter 'cntl+C'
-enter 'ps aux'
-enter 'kill -9 [PID]' using the PID that the malware is currently set to


###Team Roles
- Ben Clarke created the keylogger, and wrote the final report, as well as the “ransom” message in the project. 
- Ryan worked on making the malware's presence hidden/subtle by creating a method to constantly change the name and PID of the malware process, as well as the changing of the original files.
- Evan Harrell completed the network communication aspect of the project, and the copying of files required for this.
