# CPSC 380 Assignment 6: Virtual Address Manager

## Gillian Canicosa, Sharon Chang, & Michael Woodward
## April 28, 2023

### Known Bugs/Errors
* The physical addresses and signed bytes do not come out right at all.
* The fault and hit rates will always output 0 and I don't know why.

### References
* Working w/ files in C
  * https://www.tutorialspoint.com/c_standard_library/c_function_fgets.htm
  * https://www.tutorialspoint.com/c_standard_library/c_function_fopen.htm
  * https://www.tutorialspoint.com/c_standard_library/c_function_fseek.htm

### Source File(s)
* vmmgr.c

### Build Instructions
1. gcc vmmgr.c -o vmmgr
2. ./vmmgr \<Text File of Addresses\>

### Sample Output
(Last few lines of output only)
```
Virtual Address: 8940   Physical Addresss: 94911639981536   Signed Byte: 1452674528
Virtual Address: 9929   Physical Addresss: 94911639513824   Signed Byte: 1452206816
Virtual Address: 45563   Physical Addresss: 94911639854304   Signed Byte: 1452547296
Virtual Address: 12107   Physical Addresss: 94911628733664   Signed Byte: 1441426656
TLB Hit Rate: 0.000000
Page Fault Rate: 0.000000
```