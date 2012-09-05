#ifndef BFILEWRITER_HH_
#define BFILEWRITER_HH_

#include "Monarch.hpp"

#include <string>
using std::string;

class BFileWriter
{
    public:
        BFileWriter();
        virtual ~BFileWriter();

        void SetFileName( const string& aFileName );
        void SetRecordSize( const size_t& aSize );
        void SetInputOne( double* anInput );
        void SetInputTwo( double* anInput);

        bool Initialize();
        bool Execute();

    private:
        string fFileName;
        size_t fRecordSize;

        Monarch* fMonarch;
        MonarchHeader* fMonarchHeader;

        MonarchRecord* fMonarchRecordOne;
        char* fRecordPointerOne;

        MonarchRecord* fMonarchRecordTwo;
        char* fRecordPointerTwo;

        double* fInputOne;
        double* fInputPointerOne;

        double* fInputTwo;
        double* fInputPointerTwo;

        static const double sConversionFromVolts;
};

#endif
