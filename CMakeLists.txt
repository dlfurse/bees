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
    BFileStreamer.hh
    BAnalyticAssociate.hh
)
dmake_library_sources( BeesCore
    BFileStreamer.cc
    BAnalyticAssociate.cc
)

####################
# bees executables #
####################

dmake_executable_declare( Bees . )
dmake_executable_sources( Bees
    Bees.cc
)

#####################
# bees installation #
#####################

dmake_project_end()
