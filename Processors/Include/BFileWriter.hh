#ifndef BFILEWRITER_HH_
#define BFILEWRITER_HH_

#include "BProcessor.hh"

#include "Monarch.hpp"

class BFileWriter :
    public BProcessor< 2, 0 >
{
    public:
        BFileWriter();
        virtual ~BFileWriter();

        B_SET_GET( string, FileName )
        B_SET_GET( size_t, Size )
        B_SET_GET( double, Period )

        void Initialize();
        void Execute();
        void Finalize();

    private:
        Monarch* fMonarch;
        MonarchHeader* fMonarchHeader;
        MonarchRecord* fMonarchRecordInterleaved;

        static const double sConversionFromVolts;
};

#endif
