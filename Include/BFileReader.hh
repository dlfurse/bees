#ifndef BFILEREADER_HH_
#define BFILEREADER_HH_

#include "Monarch.hpp"

#include <boost/property_tree/ptree.hpp>
using boost::property_tree::ptree;

#include <string>
using std::string;

class BFileReader
{
    public:
        BFileReader();
        virtual ~BFileReader();

        static BFileReader* Construct( const ptree& aPropertyTree );

        void SetFileName( const string& aFileName );
        void SetSegment( const size_t& aSegmentSize );
        void SetStep( const size_t& aStepSize );
        void SetOutputOne( double* aBuffer );
        void SetOutputTwo( double* aBuffer );

        bool Initialize();
        bool Execute();

    private:
        string fFileName;
        size_t fSegmentSize;
        size_t fStepSize;

        const Monarch* fMonarch;
        const MonarchHeader* fMonarchHeader;

        size_t fRecordSize;

        const MonarchRecord* fMonarchRecordOne;
        const char* fRecordPointerOne;

        const MonarchRecord* fMonarchRecordTwo;
        const char* fRecordPointerTwo;

        double* fOutputOne;
        double* fOutputPointerOne;

        double* fOutputTwo;
        double* fOutputPointerTwo;

        size_t fRecordRead;

        static const double sConversionToVolts;
};

#endif
