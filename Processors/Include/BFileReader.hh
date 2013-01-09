#ifndef BFILEREADER_HH_
#define BFILEREADER_HH_

#include "BProcessor.hh"

#include "Monarch.hpp"

class BFileReader :
    public BProcessor< 0, 2 >
{
    public:
        BFileReader();
        virtual ~BFileReader();

        B_SET_GET( string, FileName );

        B_GET( double, AcquisitionFrequency );
        B_GET( size_t,  AcquisitionLength );

        virtual void Initialize();
        virtual void Execute();
        virtual void Reset();
        virtual void Finalize();

    private:
        const Monarch* fMonarch;
        const MonarchHeader* fMonarchHeader;
        const MonarchRecord* fMonarchRecordOne;
        const MonarchRecord* fMonarchRecordTwo;
};

#endif
