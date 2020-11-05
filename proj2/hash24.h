#ifndef HASH24_H
#define HASH24_H

#include <string>

// Helper class for calculating hash values using universal randomly selected hash functions.
class Hash24 {

private:
   // some prime numbers of suitable size
   static long const prime1 = 16890581L ;   // prime number ~ 2^24 = 16777216
   static long const prime2 = 17027399L ;   // larger prime ~ 2^24 = 16777216

   // random values for the hash function
   long random_a ;
   long random_b ;
   long random_c ;

public:
    Hash24();
    int hash(long x);
    int hash(std::string str);
    void dump();
};

#endif

