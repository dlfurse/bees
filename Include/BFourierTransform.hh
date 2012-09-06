#ifndef BFOURIERTRANSFORM_HH_
#define BFOURIERTRANSFORM_HH_

#include "fftw3.h"

class BFourierTransform
{
    public:
        BFourierTransform();
        virtual ~BFourierTransform();

        void SetLength( const size_t& aLength );

        void SetSize( const size_t& aSize );
        void SetPeriod( const double& aPeriod );
        void SetInputOne( double* anArray );
        void SetInputTwo( double* anArray );

        bool Initialize();
        bool Execute();

        double* OutputOne();
        double* OutputTwo();

    private:
        size_t fLength;

        size_t fSize;
        double fPeriod;
        double* fInputOne;
        double* fInputTwo;
        double* fOutputOne;
        double* fOutputTwo;

        fftw_plan fPlanOne;
        fftw_complex* fInOne;
        fftw_complex* fOutOne;

        fftw_plan fPlanTwo;
        fftw_complex* fInTwo;
        fftw_complex* fOutTwo;
};

#endif
