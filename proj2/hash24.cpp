
#include "hash24.h"

#include <iostream>
#include <string>

static bool initialized = false;

Hash24::Hash24() {

    if ( !initialized ) {
        srand(time(0));
        initialized = true ;
    }
    // generate and store some random values
    random_a = rand() % (int)(prime2-1) + 1 ;   // 1 <= random_a < prime2
    random_b = rand() % (int)(prime2) ;         // 0 <= randomo_b < prime2
    random_c = rand() % (int)(prime1-1) + 1 ;   // 1 <= random_c < prime1
}

int Hash24::hash(long x) {
    if (x >= prime2) throw std::runtime_error( "Input is greater than prime number!!" ); ;
    return (int) ( ( random_a * x + random_b ) % prime2 ) ;
}

int Hash24::hash(std::string str) {
    long result = 0 ;
    for (int i = 0 ; i < str.length() ; i++) {
        result = ( random_c * result + str.at(i) ) % prime1 ;
    }
    return hash(result) ;  // call long to int hash() 
}

void Hash24::dump() {
    std::cout<<"*** Hash24 dump ***"<<std::endl ;
    std::cout<<"prime1 = " << prime1<<std::endl ;
    std::cout<<"prime2 = " << prime2<<std::endl ;
    std::cout<<"random_a = " << random_a<<std::endl ;
    std::cout<<"random_b = " << random_b<<std::endl ;
    std::cout<<"random_c = " << random_c<<std::endl ;
}