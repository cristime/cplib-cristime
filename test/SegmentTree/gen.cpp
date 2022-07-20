#include "../Testlib/testlib.h"
#include <iostream>
#include <fstream>
#include <vector>

int *origin, n, m;
std::vector < std::vector< int > > ops;
const int MAXADD = 100;     // Maximum add value

void GenerateArray()
{
    // Generate an array with random numbers
    origin = new int[ n ];
    
    // std::cerr << "Generated array: ";

    for ( int i = 0; i < n; i++ )
    {
        origin[ i ] = rnd.next( -MAXADD, MAXADD );
        // std::cerr << origin[ i ] << " ";
    }

    // std::cerr << std::endl;
}

void GenerateOps()
{
    // Generate the operations
    // std::cerr << "Operations: ";
    std::vector< int > tmp; // Store the operation

    for ( int i = 0; i < m; i++ )
    {
        tmp.clear();
        int op = rnd.next( 1, 2 );
        tmp.push_back( op );
        
        if ( op == 1 ) {
            int left = rnd.next( 1, n ),
                right = rnd.next( left, n ),
                addnum = rnd.next( -MAXADD, MAXADD );
            tmp.push_back( left );
            tmp.push_back( right );
            tmp.push_back( addnum );

            // std::cerr << "add " << left << " " << right << " " << addnum << std::endl;
        } else {
            int left = rnd.next( 1, n ),
                right = rnd.next( left, n );
            tmp.push_back( left );
            tmp.push_back( right );
            
            // std::cerr << "query " << left << " " << right << std::endl;
        }

        ops.push_back( tmp );
    }
}

void WriteToFile( char *filename )
{
    // Write to file
    std::ofstream outfile;
    outfile.open( filename );
    outfile << n << " " << m << std::endl;
    for ( int i = 0; i < n; i++ )
        outfile << origin[ i ] << " ";
    outfile << std::endl;
    for ( int i = 0; i < m; i++ )
    {
        for ( auto &el : ops[ i ] )
            outfile << el << " ";
        outfile << std::endl;
    }
    outfile.close();
}

int main( int argc, char *argv[] )
{
    registerGen( argc, argv, 1 );  // Register the generator function
    
    n = atoi( argv[ 1 ] );  // Length of the array
    m = atoi( argv[ 2 ] );  // Number of queries

    GenerateArray();
    GenerateOps();
    WriteToFile( argv[ 3 ] );

    return 0;
}
