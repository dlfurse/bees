#ifndef BDATA_HH_
#define BDATA_HH_

#include "BComponent.hh"

#include "BComplex.hh"

class BData :
    public BComponent
{
    public:
        BData();
        ~BData();

        //properties

        B_SET_GET( size_t, Size )

        //component

    public:
        virtual void Initialize();
        virtual void Execute();
        virtual void Reset();
        virtual void Finalize();

        //self

    public:
        BComplex& operator[]( size_t anIndex );
        const BComplex& operator[]( size_t anIndex ) const;

    private:
        BComplex* fData;
};

#endif
