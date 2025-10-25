Spearkill is a versatile, command-line-based tool designed to perform a wide range of file operations, including file analysis, data hiding, and password cracking. Its modular design and functionality make it suitable for cybersecurity tasks, steganography, and digital forensics. 

1. File Analysis 

    Purpose: Provides detailed insights into the file's structure and content. 

    Workflow: 

    File Type Detection: Identifies the type of file based on magic bytes. 

    ASCII String Extraction: Scans files for readable ASCII characters and outputs the results, which can help detect hidden or readable data. 

    Hex Dump: Generates a hex representation of the file, which can be used to identify patterns, hidden data, or anomalies. 

2. Data Hiding and Retrieval 

    Standard LSB Decryption: 

    Retrieves data in the least significant bits of image pixels, ensuring the hidden data remains imperceptible to the naked eye. 

    Custom LSB Encryption/Decryption: 

    Provides advanced options for data hiding and retrieval: 

    User specifies pixel skipping intervals, a column start, and a Caesar cipher shift. 

    Encrypts the input data (e.g., text from a file) using the Caesar cipher before embedding it into an image. 

    Retrieves the data by reversing the process with the specified parameters. 

3. Password Cracking 

    Purpose: Break password-protected files by identifying passwords from hashed values. 

    Workflow: 

    Utilizes John the Ripper for brute-forcing hashed passwords. 

    Takes a hash file and a wordlist as input to perform the cracking operation. 

 

Below is the way on how to use the spearkill command on Linux: 

Usage: spearkill [OPTIONS] Options:  

-a, Perform file analysis.  

-x, Perform hexdump.  

-l, Perform LSB data decryption.  

-p, Perform password cracking. 

 -e, Encrypt data into an image. 

Args: <img_File> <output_img> <data_to_hide> <pixels_to_skip> <column_start> <caesar_shift> 

-d, Decrypt data from an image.  

Args: <output_img> <output.txt> <pixels_to_skip> <column_start> <caesar_shift> 

-h, --help Display this help message. 

Examples: spearkill -a file Analyze a file.  

spearkill -x file Makes hexdump.  

spearkill -l image.png output.txt Perform LSB data decryption on an image. spearkill -p hashes.txt Crack passwords from a hash file.  

spearkill -e img.png out.png secret.txt 2 10 3 Encrypt data into an image. spearkill -d img.png output.txt 2 10 3 Decrypt data from an image. 
