#include <iostream>
#include <cassert>

//First function
void pattern(unsigned int n) {

    //print the top
    for ( unsigned int row{n}; row >= 1; --row ) {
        //print spaces
        for ( unsigned int space{0}; space < (n - row); ++space ) {
            std::cout << " ";
        }
        //print asterisks
        for ( unsigned int col{0}; col < (2*row + 1); ++col ) {
            std::cout << "*";
        }
        std::cout << std::endl;
    }
    //print the middle line
    for (unsigned int space{0}; space < n; ++space ) {
        std::cout << " ";
    }
    std::cout << "*";
    std::cout << std::endl;

    //print the bottom
    for (unsigned int row{1}; row <= n; ++row ) {
        //print spaces
        for (unsigned int space(0); space < (n - row); ++space ) {
            std::cout << " ";
        }
        //print asterisks
        for (unsigned int col(0); col < (2*row + 1); ++col ){
            std::cout << "*";
        }
        std::cout << std::endl;
    }
}






//Second Function:
unsigned int log10( unsigned int n ) {

    assert( n != 0 );

    unsigned int count{0};
    unsigned int value{1};

    while ( value <= (n/10) ) {
        value *= 10;
        ++count;
    }
    return count;
}



//Third function
unsigned int count( unsigned int n, unsigned int bit ) {
    assert (bit == 0 || bit == 1); //bit is either 0 or 1.
    unsigned int count_1{0};
    unsigned int count_0{0};   
    if ( bit == 1 ) {

        for ( unsigned int k{1}; k != 0; k <<= 1 ){
            if ( (n & k) != 0u ) {
                ++count_1;
            }
        }
        return count_1;
    } else {
        for ( unsigned int k{1}; k != 0; k <<= 1 ){
            if ( (n & k) == 0u ) {
                ++count_0;
            }
        }
        return count_0;
    }
}




//Fourth function:
void swap( unsigned int &m, unsigned int &n ){

    m = m^n;
    n = m^n;
    m = m^n;

}

void clear_byte( unsigned int &i, unsigned int j ) {
    i &= ~( 0xFFu << (8u*j) );
}


unsigned int swap_bytes( unsigned int n, unsigned int b0, unsigned int b1 ) {
    assert( (b1 < 4) && ( b0 < 4 ) );

    if ( b0 == b1 ) {

        return n; 

    } else {        

        unsigned int only_b1;
        unsigned int only_b0;
        only_b1 = (n >> (8u*b1)) & 0xFFu;
        only_b0 = (n >> (8u*b0)) & 0xFFu;
        swap( only_b1, only_b0 ); 
        //Now b1 has original b0 value. Done swapping.


        //Clear the target byte on b1 and b0 to zero;
        clear_byte( n, b1 );
        clear_byte( n, b0 );
        //n has its b1 b0 bits cleared

        unsigned int rep_b1;
        unsigned int rep_b0;
        rep_b1 = (only_b1 << 8*b1);
        rep_b0 = (only_b0 << 8*b0);

        //combine cleared n with b1 and b0;
        return n | (rep_b1) | (rep_b0);
    }  
}

//Test




