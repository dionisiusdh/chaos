# chaOS
> A Simple 16-Bit Operating System Made with C Simulated Using Bochs

## Authors
| Name | NIM |
| --- | --- |
| Dionisius Darryl Hermansyah | 13519058 |
| Joel Triwira | 13519073 | 
| James Chandra | 13519078 |

## Current Features
* Disk image
* Bootloader
* Simple kernel
* File system
* System call functions
* File and sector operations
* Shell (cd, ls, cat, ln, mkdir, mv, cp, rm)
* Scripts
* Libraries (String, Math, IO, Boolean)
* Execute external program

## How to Run
1. Make sure you're in the `root` directory
2. Run `chmod +x *.sh`
3. If you're running the OS for the first time, make sure that you have all the tools needed or simply run `./get-tools.sh`
4. To create file system or `fs` in `other`bfolder, run `make filesystemcreator`
5. To compile, link, and run the OS, execute `./build-run.sh`
6. To run the program, execute `./run.sh`
8. Enter `c` to the Bochs' console
9. Your OS should be running in a new window 

## Shell command
* mv (memindahkan file/folder) : `mv <filename> <dirname>`
* cp (mengcopy file/folder) : `cp <src> <dest>`
* mkdir (membuat directory) : `mkdir <dirname>`
* rm (menghapus file/folder) : `rm <name>`
* cat (mencetak isi file) : `cat <filename>`
* ln (membuat symbolic link) : `ln [-s] <target> <linkname>`
* cd (memindahkan path) : `cd <path>`
* ls (mengoutput daftar file/folder) : `ls`
* ./ program (menjalankan program) : `./ <programname>` (dengan spasi)

## Script
* `all.sh` : Execute build, load test files, dan run
* `build.sh` : Build and compile OS
* `load.sh` : Load test files
* `run.sh` : Run OS without compiling it

## Our Thanks to
**Kelompok Mangga - K04** for kindly providing their milestone 2 result. Most of the code is modified from their work.
| Name | NIM |
| --- | --- |
| Gregorius Dimas Baskara | 13519190 |
| Christian Gunawan | 13519199 | 
| Tanur Rizaldi Rahardjo | 13519214 |

