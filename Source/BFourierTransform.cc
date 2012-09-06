#include "BFourierTransform.hh"

#include <cstring>
#include <cmath>

#include <iostream>
using std::cout;
using std::endl;

BFourierTransform::BFourierTransform()
{
}
BFourierTransform::~BFourierTransform()
{
    fftw_destroy_plan( fPlanOne );
    fftw_free( fInOne );
    fftw_free( fOutOne );

    fftw_destroy_plan( fPlanTwo );
    fftw_free( fInTwo );
    fftw_free( fOutTwo );

    delete[] fOutputOne;
    delete[] fOutputTwo;
}

void BFourierTransform::SetLength( const size_t& aLength )
{
    fLength = aLength;
    return;
}

void BFourierTransform::SetSize( const size_t& aSize )
{
    fSize = aSize;
    return;
}
void BFourierTransform::SetPeriod( const double& aPeriod )
{
    fPeriod = aPeriod;
    return;
}
void BFourierTransform::SetInputOne( double* anArray )
{
    fInputOne = anArray;
    return;
}
void BFourierTransform::SetInputTwo( double* anArray )
{
    fInputTwo = anArray;
    return;
}

double* BFourierTransform::OutputOne()
{
    return fOutputOne;
}
double* BFourierTransform::OutputTwo()
{
    return fOutputTwo;
}

bool BFourierTransform::Initialize()
{
    fInOne = (fftw_complex*) fftw_malloc( sizeof(fftw_complex) * fLength );
    fOutOne = (fftw_complex*) fftw_malloc( sizeof(fftw_complex) * fLength );
    fPlanOne = fftw_plan_dft_1d( fLength, fInOne, fOutOne, FFTW_FORWARD, FFTW_MEASURE );

    fInTwo = (fftw_complex*) fftw_malloc( sizeof(fftw_complex) * fLength );
    fOutTwo = (fftw_complex*) fftw_malloc( sizeof(fftw_complex) * fLength );
    fPlanTwo = fftw_plan_dft_1d( fLength, fInTwo, fOutTwo, FFTW_FORWARD, FFTW_MEASURE );

    fOutputOne = new double[fLength];
    memset( fOutputOne, 0, sizeof(double) * fLength );

    fOutputTwo = new double[fLength];
    memset( fOutputTwo, 0, sizeof(double) * fLength );

    return true;
}

bool BFourierTransform::Execute()
{
    register size_t tIndex;
    register size_t tBlock;
    register size_t tFold = floor( fSize / fLength );
    register double* tInputOnePtr = fInputOne;
    register double* tInputTwoPtr = fInputTwo;

    for( tBlock = 0; tBlock < tFold; tBlock++ )
    {
        for( tIndex = 0; tIndex < fLength; tIndex++ )
        {
            fInOne[tIndex][0] = *tInputOnePtr;
            fInOne[tIndex][1] = 0.;
            fInTwo[tIndex][0] = *tInputTwoPtr;
            fInTwo[tIndex][1] = 0.;
            tInputOnePtr++;
            tInputTwoPtr++;
        }

        fftw_execute( fPlanOne );
        fftw_execute( fPlanTwo );

        for( tIndex = 0; tIndex < fLength; tIndex++ )
        {
            fOutputOne[tIndex] += (fOutOne[tIndex][0] * fOutOne[tIndex][0] + fOutOne[tIndex][1] * fOutOne[tIndex][1]) / (tFold);
            fOutputTwo[tIndex] += (fOutTwo[tIndex][0] * fOutTwo[tIndex][0] + fOutTwo[tIndex][1] * fOutTwo[tIndex][1]) / (tFold);
        }
    }

    return true;
}

