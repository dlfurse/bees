#ifndef BANALYTICASSOCIATE_HH_
#define BANALYTICASSOCIATE_HH_

#include <cstddef>

class BAnalyticAssociate
{
    public:
        BAnalyticAssociate();
        ~BAnalyticAssociate();
        
        void SetLength( const size_t& aLength );
        void SetPeriod( const double& aPeriod );
        
        void Initialize();
        void Execute( const double* aRealSignal, const double* anAssociateSignal );
        
    private:
        typedef enum
        {
            eUninitialized,
            eInitialized
        } State;
        State fState;
};    

#endif
