#include "BException.hh"

BException::BException() :
            exception(),
            fStream()
{
}
BException::BException( const BException& anException ) :
            exception( anException ),
            fStream( anException.fStream.str() )
{
}
BException::~BException() throw ()
{
}

const char* BException::what() const throw ()
{
    return fStream.str().c_str();
}

