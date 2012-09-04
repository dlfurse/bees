#include <cmath>

#include "BAnalyticAssociate.hh"

const double BAnalyticAssociate::sPi = 3.1415926535898;

BAnalyticAssociate::BAnalyticAssociate() :
    fWindow( 0 ),
    fInput( NULL ),
    fOutput( NULL ),
    fCoefficients( NULL )
{
}
BAnalyticAssociate::~BAnalyticAssociate()
{
    if( fCoefficients != NULL )
    {
        delete[] fCoefficients;
        fCoefficients = NULL;
    }
}

void BAnalyticAssociate::SetSegment( const size_t& aSegment )
{
    fSegment = aSegment;
    return;
}
void BAnalyticAssociate::SetWindow( const size_t& aWindow )
{
    fWindow = aWindow;
    return;
}
void BAnalyticAssociate::SetInput( const double* anInput )
{
    fInput = anInput;
    return;
}
void BAnalyticAssociate::SetOutput( double* anOutput )
{
    fOutput = anOutput;
    return;
}

bool BAnalyticAssociate::Initialize()
{
    fCoefficients = new double[fWindow];
    double tMax = (double) (fWindow);

    size_t tIndex;
    for( tIndex = 0; tIndex < fWindow; tIndex++ )
    {
        fCoefficients[fWindow - tIndex - 1] = (2. / tMax) * sin( sPi * tIndex / 2. ) * sin( sPi * tIndex / 2. ) / tan( sPi * tIndex / tMax );
    }

    return true;
}
bool BAnalyticAssociate::Execute()
{
    fInputPointer = fInput;
    fOutputRealPointer = fOutput;
    fOutputImaginaryPointer = fOutput + 1;

    size_t tWindowIndex;
    size_t tIndex;
    register double tValue;

    for( tIndex = 0; tIndex < fSegment; tIndex++ )
    {
        fWindowPointer = fInputPointer;

        tValue = 0;
        for( tWindowIndex = 0; tWindowIndex < fWindow; tWindowIndex++ )
        {
            tValue += fCoefficients[tWindowIndex] * (*fWindowPointer);
            fWindowPointer++;
        }

        *fOutputImaginaryPointer = tValue;
        *fOutputRealPointer = *(fInputPointer + fWindow / 2);

        fInputPointer++;
        fOutputRealPointer += 2;
        fOutputImaginaryPointer += 2;
    }

    return true;
}
