# Linux TAR Command Implementation
The Linux TAR stands for tape archive, it is used to create Archive, extract the Archive files and list files present in Archive.

### Syntax
```sh 
./tar [mode] [absolute path]
```

### Modes of TAR Command
![Tar_command_flowchart](https://user-images.githubusercontent.com/87142754/173245644-d58cb71d-d826-48e4-9392-ff56e6259d44.png)


### Example of all commands
* Create an Archive for a folder
```sh
./tar -c /home/prernatulsiani/Desktop/Datasets
```
Note : After this commands two tar files are created. Datasets.tar is original tar file whereas Datasets_c.tar is compressed tar file (With upto 45% reduction in size)

* Compress a file
```sh
./tar -c /home/prernatulsiani/Desktop/Datasets/part3.txt
```

* List all files present in an Archive
```sh
./tar -t /home/prernatulsiani/Desktop/Prerna/DSA2/DSA_Project/Datasets_c.tar
```

* Extract files present in an Archive
```sh
./tar -x /home/prernatulsiani/Desktop/Prerna/DSA2/DSA_Project/Datasets_c.tar
```

* Decode a compressed file
```sh
./tar -d /home/prernatulsiani/Desktop/Prerna/DSA2/DSA_Project/part3
```

### Steps to implement the command on Linux OS
1. Clone the repository
```sh
git clone "https://github.com/pt3002/TAR_command"
```
2. At the project root run:
```sh
make
```
3. Then as per your requirements run the commands given above !

### Drive Link for Large Datasets
[Dataset](https://drive.google.com/drive/folders/142LVHxQQoVIInrvH2FWPlvL3XeDL51QS?usp=sharing)

### References 
1. [Linux Man Pages](https://man7.org/linux/man-pages/man1/tar.1.html)
2. [Ubuntu Man Pages](http://manpages.ubuntu.com/manpages/bionic/man5/tar.5.html)
3. [LZ77 Data Compression Technique](https://towardsdatascience.com/how-data-compression-works-exploring-lz77-3a2c2e06c097)


