#include "BException.hh"

#include <iostream>
using std::cout;
using std::endl;

int main()
{
    cout << "now testing BException..." << endl;


    cout << "creating an exception within a try-catch block..." << endl;

    try
    {
        throw BException() << "this exception should be explicitly caught";
    }
    catch( exception& aStandardException )
    {
        cout << "got an exception with content <" << aStandardException.what() << ">" << endl;
    }

    cout << "creating an exception outside a try-catch block..." << endl;

    throw BException() << "this exception should not be explicitly caught";

    return 0;
}




