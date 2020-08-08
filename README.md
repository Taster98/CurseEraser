# Curse Word Eraser

## Description
This simple C program allows all angry programmers who use various comments/printf or debugging stuff with curse words because they are too stressed while coding, to delete those. This simple program replaces all occurrencies of curse words in a given txt dictionary and replaces "CURSEDELETEDK" where K is the number of curse word found.

## Usage
In order to use it you have to download this tarball file:
~~~
wget https://raw.githubusercontent.com/Taster98/CurseEraser/master/CurseEraser.tar.gz
~~~

Then you have to extract the folder, open the extracted folder into terminal and type:

```
make install
```
There you are! Now here is an example of usage:
~~~
curseEraser --input sourcefile.py --dict dictionary.txt
~~~

### Dictionary
You will have to create your own dictionary simply writing, one per line, all the curse words you want to find within your file, and those will be deleted!
~~~
word1
word2
word3
~~~

You can use --help or -h command to know more!

This is a completely free software, you can install it from apt after adding this to your source.list:

~~~
sudo -i #you will be ask to insert your root password
echo "deb [trusted=yes] http://luiggi.altervista.org/packages/debian ./" | tee -a /etc/apt/sources.list > /dev/null
sudo apt update
sudo apt install curseEraser
~~~
