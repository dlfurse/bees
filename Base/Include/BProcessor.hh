#ifndef BPROCESSOR_HH_
#define BPROCESSOR_HH_

#include "BComponent.hh"
#include "BData.hh"

#include <cassert>

template< int XInputs, int XOutputs >
class BProcessor :
    public BComponent
{
    public:
        BProcessor()
        {
            for( int tInputIndex = 0; tInputIndex < XInputs; tInputIndex++ )
            {
                fInputs[ tInputIndex ] = NULL;
            }

            for( int tOutputIndex = 0; tOutputIndex < XOutputs; tOutputIndex++ )
            {
                fOutputs[ tOutputIndex ] = NULL;
            }
        }
        virtual ~BProcessor()
        {
            for( int tInputIndex = 0; tInputIndex < XInputs; tInputIndex++ )
            {
                fInputs[ tInputIndex ] = NULL;
            }

            for( int tOutputIndex = 0; tOutputIndex < XOutputs; tOutputIndex++ )
            {
                fOutputs[ tOutputIndex ] = NULL;
            }
        }

        template< int XChannel >
        void SetInput( BData* anInput )
        {
            assert( XChannel < XInputs );
            fInputs[ XChannel ] = anInput;
            this->ConnectInput( anInput );
            anInput->ConnectOutput( this );
            return;
        }

        template< int XChannel >
        void SetOutput( BData* anOutput )
        {
            assert( XChannel < XOutputs );
            fOutputs[ XChannel ] = anOutput;
            this->ConnectOutput( anOutput );
            anOutput->ConnectInput( this );
            return;
        }

    protected:
        BData* fInputs[ XInputs ];
        BData* fOutputs[ XOutputs ];
};

template< int XOutputs >
class BProcessor< 0, XOutputs > :
    public BComponent
{
    public:
        BProcessor()
        {
            for( int tOutputIndex = 0; tOutputIndex < XOutputs; tOutputIndex++ )
            {
                fOutputs[ tOutputIndex ] = NULL;
            }
        }
        virtual ~BProcessor()
        {
            for( int tOutputIndex = 0; tOutputIndex < XOutputs; tOutputIndex++ )
            {
                fOutputs[ tOutputIndex ] = NULL;
            }
        }

        template< int XChannel >
        void SetOutput( BData* anOutput )
        {
            assert( XChannel < XOutputs );
            fOutputs[ XChannel ] = anOutput;
            this->ConnectOutput( anOutput );
            anOutput->ConnectInput( this );
            return;
        }

    protected:
        BData* fOutputs[ XOutputs ];
};

template< int XInputs >
class BProcessor< XInputs, 0 > :
    public BComponent
{
    public:
        BProcessor()
        {
            for( int tInputIndex = 0; tInputIndex < XInputs; tInputIndex++ )
            {
                fInputs[ tInputIndex ] = NULL;
            }
        }
        virtual ~BProcessor()
        {
            for( int tInputIndex = 0; tInputIndex < XInputs; tInputIndex++ )
            {
                fInputs[ tInputIndex ] = NULL;
            }
        }

        template< int XChannel >
        void SetInput( BData* anInput )
        {
            assert( XChannel < XInputs );
            fInputs[ XChannel ] = anInput;
            this->ConnectInput( anInput );
            anInput->ConnectOutput( this );
            return;
        }

    protected:
        BData* fInputs[ XInputs ];
};

#endif
