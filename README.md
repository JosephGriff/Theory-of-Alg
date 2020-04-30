# ToA MD5 Hashing Algorithm 

## What is Md5?
- MD5 or Message-digest algorithm is a widely used hash function which produces a 128-bit hash value
- MD5 is part of the Secure Hash Algorithm family which are a bunch of cryptographic hash function published by the National Institute of Standards and Technology - NIST for short.
- MD5 was designed by Ronald Rivest in 1991 to replace an earlier hash function MD4, and was specified in 1992 as RFC 1321
- One basic requirement of any cryptographic hash function is that it should be computationally infeasible to find two distinct messages that hash to the same value. MD5 fails this requirement catastrophically; such collisions can be found in seconds on an ordinary home computer.
- The weaknesses of MD5 have been exploited in the field, most infamously by the Flame malware in 2012. The CMU Software Engineering Institute considers MD5 essentially "cryptographically broken and unsuitable for further use".

## How to Run the project:

- Open up a command prompt then type git clone https://github.com/JosephGriff/Theory-of-Alg.git
- Once cloned the user must then cd to the working directory cd Theory-of-Alg
- From there the user must then type "make finalMd5"
- Finally type " ./finalMd5"
