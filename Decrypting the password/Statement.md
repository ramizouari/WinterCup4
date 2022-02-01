# Problem D : Decrypting the password

Yessine was trying to log into his email when he realized that he forgot his password. Fortunately, he wrote it in a text file and saved it just in case. However, when he opened the file, he didn't find the password but rather a very long string of digits. He then remembered that he didn't write the password but rather an encryption of it. As a matter of fact, the password is the number of substrings divisible by 11 in the string. Yessine wants to open his email, help him decrypt the password. \
A string **a** is a substring of a string **b** if **a** can be obtained from **b** by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

## Input :
The first line contains one integer **t (1≤t≤1000)** — the number of test cases. \
The first line of each test case contains one integer **n (1≤n≤10^6)** — the length of the string **s**. \
The second line of each test case contains a string consisting of **n** decimal digits. \
It is guaranteed that the sum of **n** over all test cases does not exceed **10^6**
## Output :
Print one line containing the answer — The number of substrings divisible by 11

## Example:
Input:  

```
4
3
121
4
1111
6
123456
8
20654301
```

Output:  

```
1
4
0
3
```
