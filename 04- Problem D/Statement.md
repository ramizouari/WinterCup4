# Problem D : Decrypting the password

Yessine was trying to log into his email when he realized that he forgot his password. Fortunately, he wrote it in a text file and saved it just in case. However, when he opened the file, he didn't find the password but rather a very long string of digits. He then remembered that he didn't write the password but rather an encryption of it. As a matter of fact, the password is the number of substrings divisible by 11 in the string. Yessine wants to open his email, help him decrypt the password. \
A string **a** is a substring of a string **b** if **a** can be obtained from **b** by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

## Input :
The first and only line of the input contains a string **S** consisting of decimal digits  (2 <= |S| <= 10^6)
## Output :
Print one line containing the answer — The number of substrings divisible by 11

## Example:
Input:  

```
121  
```

Output:  

```
1
```

Input:  

```
1122334455
```

Output:  

```
15
```
