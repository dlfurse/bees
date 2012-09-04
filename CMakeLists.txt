##################
# get that gravy #
##################

cmake_minimum_required( VERSION 2.8 )
include( $ENV{HOME}/.dmake/dmake.cmake )

#########
# setup #
#########

dmake_project_begin( Bees 0 1 0 )

#####################
# bees dependencies #
#####################

dmake_dependency_declare( Monarch 0 1 0 )
dmake_dependency_foreign_declare( Boost 1 52 0 )

################
# bees library #
################

dmake_library_declare( BeesCore . )
dmake_library_headers( BeesCore
    BFileReader.hh
)
dmake_library_sources( BeesCore
    BFileReader.cc
)

####################
# bees executables #
####################

dmake_executable_declare( TestBFileReader . )
dmake_executable_sources( TestBFileReader
    TestBFileReader.cc
)

#####################
# bees installation #
#####################

dmake_project_end()
