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

dmake_library_declare( BeesUtility Utility )
dmake_library_headers( BeesUtility
    BComplex.hh
    BException.hh
)
dmake_library_sources( BeesUtility
    BComplex.cc
    BException.cc
)

dmake_library_declare( BeesBase Base )
dmake_library_headers( BeesBase
    BComponent.hh
    BData.hh
    BProcessor.hh
)
dmake_library_sources( BeesBase
    BComponent.cc
    BData.cc
)

####################
# bees executables #
####################

dmake_executable_declare( TestException Executables/Validation )
dmake_executable_sources( TestException
    TestException.cc
)

#####################
# bees installation #
#####################

dmake_project_end()
