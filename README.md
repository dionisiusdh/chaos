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
* Read and write string
* Read and write sector
* Read, write, and load file
* Simple shell with cd, ls, cat, ln command
* Scripts

## How to Run
1. Make sure you're in the ```./src``` directory
2. Run ```chmod +x *.sh```
3. Make a system.img by executing  ```sh make_system.sh``` on your terminal
4. Generate map.img, files.img, and sectors.img using ```sh make_filesystem.sh``` on your terminal and proceed to 5 before entering anything
5. Change the content of ```map.img``` with ```hexedit map.img``` referring to the instruction printed by the script
6. Compile loadFile.c with ```sh loadFile.sh```
7. Compile the kernel and run the OS all at once using ```check.sh```
8. Enter ```c``` to the Bochs' console
9. Your OS should be running in a new window 

## Scripts
How to use scripts:<br/>
    ```chmod +x script.sh```<br/>
    ```sh script.sh``` 

**List of scripts:**
* ```check.sh``` : Running operating system (including compile_kernel.sh)
* ```compile_kernel.sh``` : Compiling kernel.c
* ```compile_loadFile.sh``` : Compiling loadFile.c
* ```make_system.sh``` : Initialize system.img
* ```make_filesystem.sh``` : Initialize file system images including map.img, files.img, and sectors.img

## Folder structure
```
chaOS
│
├── src                     [Source code]
│   └── kernel /            
│       └── kernel.c
│       └── kernel.asm
│       └── math.c  
│       └── sector.c
│       └── string.c  
│   └── loadFile /        
│       └── loadFile.c 
│   └── test /              [ Test files ]
│       └── test.txt
│   └── *.sh                [ Scripts ]  
│   └── if2230.config       [ Configuration file ]  
│
├── MILESTONE1.MD        
│
└── README.md
```

