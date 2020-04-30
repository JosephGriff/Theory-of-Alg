# MD5 Algorithm Project Report

In this project from the Theory of Algorithms Module I was tasked with developing a C program that will allow the user to perform the MD5(Message Digest Algorithm). The program must be able to calculate the MD5 hash digest (learn more here : https://tools.ietf.org/html/rfc1321 / https://en.wikipedia.org/wiki/MD5 ) of an input. The user will be tasked to enter either a filw or input a string which will be stored in the user-entry.txt file that is already created in te repository.

The Github Repository Contains the following:
- Md5Alg folder which contains a diagram of the algorithm accompanied by a short description of said diagram.
- refactor.c this is a c file that contains the code from the Sha256 algorithm that was supplied to us by our Lecturer from weekly videos to get us started.
- refs.txt this is a text file containing websites and videos I used while completing the project.
- .gitignore file to ignore specific files such as executables or already completed files such as unions.c / sha256 ect.
- GNU General Public License
- The finished project finalMd5
- user-entry.txt a file which stores the users inputs
- test/write/empty.txt are text files created for the user to test their inputs in.
- ReadME.md / report.md, The Readme brifly talks about the MD5 algorithm and teaches the user to clone and run te project while the report .md contains a report on the project going into slightly more detail than the original Readme.

# Starting up 
Part of the task given to us for this project was to used the Google Cloud Platform and create a VM instance and use Vim to develop our project, I felt this was a nice touch as it gave me insight into using linux commands and using Vim.

- Next I will walk you through step by step on how to start your virtual machine up to be code ready once created.
- Firstly run gcc --version to check if a C compiler is installed on the machine, Install if not.
- Secondly sudo apt install build-essentails we were also told that we may run sudo apt install gcc, however advised against it as apt did not allow the usage of "make" resulting in not being able to complete the project properly.
- Third check if the VM has git installed so that you may clone your existing repository if needed.
- This is done by typing sudo apt install git
- next type install wget to install wget.
- once everything is installed you can create a file by typing vi "filename"(finalMd5 in my case).c 
- once you have coded up some of the project and want to test your work you must press "esc, : , wq , enter" to go back to the command line.
- once their type make "filename"(finalMd5) this will check for errors and compile your code.
- finally type ./"filename"(finalMd5) to run your work.

# Tests / Cmd Line Arguments
- As part of the extended work for the project due to the COVID-19 virus pandemic we were tasked with adding tests and command line arguments. -h a help command line argument is what I implemented.

- the --help is implemented using getopt to allow the command line arguments to be part of the program #include<getopt.h>. 
- to use the -help cmd line argument the user must type in ./finalMd5 -h into the command line.
- Once entered the gui interface will give a prompt to the user on what they must enter to successfully run the project.
