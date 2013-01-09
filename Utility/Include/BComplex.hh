#ifndef BCOMPLEX_HH_
#define BCOMPLEX_HH_

#include <cmath>

typedef double BComplexRaw[ 2 ];

class BComplex
{
    public:
        BComplex();
        BComplex( const double& aReal, const double& anImaginary );
        ~BComplex();

        double& R();
        const double& R() const;

        double& I();
        const double& I() const;

        double Mod() const;
        double Arg() const;

        BComplex operator+( const BComplex& aComplex ) const;
        BComplex operator-( const BComplex& aComplex ) const;
        BComplex operator*( const BComplex& aComplex ) const;
        BComplex operator/( const BComplex& aComplex ) const;

    private:
        double fReal;
        double fImaginary;
};

inline BComplex::BComplex( const double& aReal, const double& anImaginary ) :
            fReal( aReal ),
            fImaginary( anImaginary )
{
}

inline double& BComplex::R()
{
    return fReal;
}
inline const double& BComplex::R() const
{
    return fReal;
}

inline double& BComplex::I()
{
    return fReal;
}
inline const double& BComplex::I() const
{
    return fReal;
}

inline double BComplex::Mod() const
{
    return sqrt( fReal * fReal + fImaginary * fImaginary );
}
inline double BComplex::Arg() const
{
    return atan2( fImaginary, fReal );
}

inline BComplex BComplex::operator+( const BComplex& aComplex ) const
{
    return BComplex( fReal + aComplex.fReal, fImaginary + aComplex.fImaginary );
}
inline BComplex BComplex::operator-( const BComplex& aComplex ) const
{
    return BComplex( fReal - aComplex.fReal, fImaginary - aComplex.fImaginary );
}
inline BComplex BComplex::operator*( const BComplex& aComplex ) const
{
    return BComplex( fReal * aComplex.fReal - fImaginary * aComplex.fImaginary, fReal * aComplex.fImaginary + fImaginary * aComplex.fReal );
}
inline BComplex BComplex::operator/( const BComplex& aDenominator ) const
{
    register double tDenominatorMod = aDenominator.Mod();
    return BComplex( (fReal * aDenominator.fReal + fImaginary * aDenominator.fImaginary) / tDenominatorMod, (fReal * aDenominator.fImaginary - fImaginary * aDenominator.fReal) / tDenominatorMod );
}

#endif
