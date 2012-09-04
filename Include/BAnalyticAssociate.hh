#ifndef BANALYTICASSOCIATE_HH_
#define BANALYTICASSOCIATE_HH_

#include <cstddef>

class BAnalyticAssociate
{
    public:
        BAnalyticAssociate();
        ~BAnalyticAssociate();

        void SetSegment( const size_t& aSegment );
        void SetWindow( const size_t& aWindow );
        void SetInput( const double* anInput );
        void SetOutput( double* anOutput );

        bool Initialize();
        bool Execute();

    private:
        size_t fSegment;
        size_t fWindow;
        const double* fInput;
        double* fOutput;

        double* fCoefficients;
        const double* fInputPointer;
        const double* fWindowPointer;
        double* fOutputRealPointer;
        double* fOutputImaginaryPointer;
        static const double sPi;
};

#endif
