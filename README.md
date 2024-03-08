# DIFO

DIFO (Directory Informaton) is a command-line utility written in C++, aimed at providing directory information, including displaying a tree view, directory sizes, and sorting options.  It serves as a tool for efficiently analyzing directory structures.

[See Documentation](https://sagar-bei031.github.io/difo/)

## Features
1. **Display Directory Tree:** The tool offers the functionality to display a hierarchical tree view of directories and files within a specified directory.
2. **Display Directory Sizes:** Users can view the sizes of directories and files contained
 within the current directory.
3. **Sorting Options:** difo.cpp provides various sorting options, allowing users to sort directory entries based on different criteria such as name, time, and size, in both ascending and descending orders.
4. **Hidden Files Support:** Users have the option to include hidden files and directories in the displayed results.
5. **Slide Speed Adjustment:** Additionally, the tool offers the flexibility to adjust the slide speed, controlling the rate at which information is displayed on the screen.

## Purpose
The purpose of difo is to aid users in efficiently navigating, analyzing, and managing directory structures, providing valuable insights into the organization and contents of their file systems.

## Integration
The tool returns specific exit codes to indicate the success or failure of operations, allowing for seamless integration into automated scripts and workflows.

## Help
```plaintext
Directory Information: display tree view, directory sizes and do sorting.

usage: difo.py [-h] [--tree] [--size] [--sort <type> <order>] [-a] [--slide <speed>] [directory]

positional arguments:
  directory                 Directory path (default: current directory)

options:
  --tree, -t                Display directory tree
  --size, -z                Display size of directories and files in current directory
  --sort [sorting options]  Sort by type in order (-asc or -desc)
  --slide, -l [speed]       Slide speed in seconds (default: 1.0 impled 1 character per 20ms)
  -a, --all                 Show hidden files and directories
  -h, --help                Show this help message and exit

sorting options:
  --sort-name, -n           Sort by name
  --sort-time, -d           Sort by time
  --sort-size, -s           Sort by size
  --ascending, -asc         Sort in ascending order
  --descending, -desc       Sort in descending order

slide speed:
  -f[speed]                 Adjust speed: 1.0 = one character per 20ms

return:
  0                         success
  1                         invalid argument
  2                         failure on opening accessing (file or directory)
```


## Guideline
### Setup
 ```bash
 git clone https://github.com/sagar-bei031/difo.git # clone project
 cd difo # get into the project directory
 mkdir build # create build directory
 cd build # get into build directory
 cmake .. # setup cmake files
 make # build project
 sudo cp src/difo /usr/local/bin # copy projrct binary to user bin
 sudo chmod +x /usr/local/bin/difo # make executable
 ```

### Tree View
**Tree** is the default view of difo. So using command `difo [--tree] [-a] <path/to/directory>` can be used for the analysis directory in tree view. 
```bash
difo # current directory
```
```bash
difo .. # its parent directory
```
```bash
difo ~ # home directory
```
```bash
difo -a # also show hidden in current directory
```
```bash
difo --tree # same as 'difo' or 'difo .'
```
```bash
difo -t # same as 'difo --tree'
```

### Size View
**Size view** is used to see the size of files and directories. It shows colums for relativel comparision in more convenient format. Use this command format: `difo --size [-a] <path/to/directory>`.
```bash
difo --size # size view in current directory
```
```bash
difo --size -a # also show hidden files
```
```bash
difo -z # use short hand option
```
```bash
difo -z .. # view parent directory
```

### Sorting
**Sorting** is the feature to show an algorithm that we leaened from **Data Structure and Algorithm**. Sorting can be done on the basis of name, size and time in ascending as well as descending order using the command format `difo --sort [sort-type] [sort-order] [-a] <path/to/directory>`. 
```bash
difo --sort # default name-type in ascending oder
```
```bash
 # sort accorfing to size in discending order, whih show hidden on parentt directories
 difo --sort-size -desc --all ..
```
```bash
difo --sort-time --descending # sort by time, latest first
```

### Slide
**Slide** is additional option to see the content of file in slide view. To use this, use this command: `difo --size [speed] <path/to/file>`. Speed 1.0 is equivalent to one character per twenty milliseconds.
```bash
# create a.txt
echo "Hello, nice to meet you." >> a.txt 
# see contents of a.txt in slide view with 1 character per 10 ms
difo --slide -f0.5 a.txt 
```

### Help
As usual, help option provide information about difo command to user.
```bash
difo --help
```
```bash
difo -h # use short-hand
```

### Remove
You can use regular command to remove it from `/usr/bin`.
```bash
sudo rm -f /usr/local/bin/difo
```

## About Us
We are students of Instittute of Engineering, Pulchowk Campus. At the time of its release, we were in fourth semester, Bachelor in Electronics, Communication and Information Engineering (BEI).

<p align="center">
Arun Chaudhary | Sagar Chaudhary | Saurav Chaudhary<br>
Bachelor in Electronics, Communication and Information Engineering<br>
Institute of Engineering, Pulchowk Campus
</p>
