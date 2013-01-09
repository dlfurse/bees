#ifndef BEXCEPTION_HH_
#define BEXCEPTION_HH_

#include <exception>
using std::exception;

#include <sstream>
using std::stringstream;

class BException :
    public exception
{
    public:
        BException();
        BException( const BException& anException );
        virtual ~BException() throw();

        virtual const char* what() const throw();

        template< class XType >
        BException& operator<< ( const XType& anArgument )
        {
            fStream << anArgument;
            return *this;
        }

    private:
        stringstream fStream;
};

#endif
