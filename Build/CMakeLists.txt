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

dmake_dependency( Monarch 0 1 0 )

################
# bees library #
################

dmake_library_declare( Core . )
dmake_library_headers( Core
    BAnalyticAssociate.hh
)
dmake_library_sources( Core
    BAnalyticAssociate.cc
)

####################
# bees executables #
####################

dmake_executable_declare( Test . )
dmake_executable_sources( Test
    BeesTest.cc
)

#####################
# bees installation #
#####################

dmake_project_end()
