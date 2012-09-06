##################
# get that gravy #
##################

cmake_minimum_required( VERSION 2.8 )
include( $ENV{HOME}/.dmake/dmake.cmake )

#########
# setup #
#########

dmake_project_begin( Bees 0 1 0 )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g" )

#####################
# bees dependencies #
#####################

dmake_dependency_declare( Monarch 0 1 0 )
dmake_dependency_foreign_declare( Boost 1 52 0 )
dmake_dependency_foreign_declare( FFTW3 1 0 0 )

################
# bees library #
################

dmake_library_declare( BeesCore . )
dmake_library_headers( BeesCore
    BFileWriter.hh
    BToneGenerator.hh
    BLinearChirpGenerator.hh
    BWhiteNoiseGenerator.hh
    BFileReader.hh
    BFourierTransform.hh
)
dmake_library_sources( BeesCore
    BFileWriter.cc
    BToneGenerator.cc
    BLinearChirpGenerator.cc
    BWhiteNoiseGenerator.cc
    BFileReader.cc
    BFourierTransform.cc
)

####################
# bees executables #
####################

dmake_executable_declare( BeesSynthesis . )
dmake_executable_sources( BeesSynthesis
    BeesSynthesis.cc
)

dmake_executable_declare( BeesAnalysis . )
dmake_executable_sources( BeesAnalysis
    BeesAnalysis.cc
)

dmake_executable_declare( BeesDirect . )
dmake_executable_sources( BeesDirect
    BeesDirect.cc
)

#####################
# bees installation #
#####################

dmake_project_end()
