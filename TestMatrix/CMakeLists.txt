# \author Zachary Wartell
#
# \brief This is not yet tested

# Mostly, students will need to only adjust the "set(SOURCES ..."
# command.

# IMPLEMENTATION DETAILS:
# Initially generated via vcproj2cmake.rb from
#
# svn://linux01.uncc.edu:3690/zwartell-public/ITCS 6120-8120/OpenGLTrainer/trunk/make/VS08 
#
# See svn log for more details on progress in getting this file working.  
# TODOS:
# [T2] - how do I add non-source files to the IDE's build scripts?
#

project( "Test" )

##
## find libraries 
##

if(NOT DEFINED ENV{UNCC_ITCS_GRAPHICS_SVN})
    message(FATAL "The required environment variable UNCC_ITCS_GRAPHICS_SVN is undefined.\n"
	       "   Please set it to the SVN URL of your SVN repository direction.  You may \n"
	       "   need to restart your IDE or re-open a new command shell for the change \n"
	       "   to take effect."
	) 	
endif(NOT DEFINED ENV{UNCC_ITCS_GRAPHICS_SVN})

if(NOT DEFINED ENV{UNCC_ITCS_GRAPHICS})
    message(FATAL "The required environment variable UNCC_ITCS_GRAPHICS is undefined.\n"
	       "   Please set it to the file path of your SVN repository directories working copy.\n"	
	       "   You may need to restart your IDE or re-open a new command shell for the change\n"
	       "   to take effect."
	) 	
endif(NOT DEFINED ENV{UNCC_ITCS_GRAPHICS})

# find libraries available through standard Cmake mechanisms...
#   -NONE

# find libraries available through zjw_find_package mechanism... 
#

# Use the local Math2D installation if we are compiling example code distriute with Math2D,
# otherwise get path from environment variable
get_filename_component(Math2D_DIR "../../" ABSOLUTE)
get_filename_component(DIR ${Math2D_DIR} NAME)
if(NOT DIR STREQUAL "Math2D")
    set(Math2D_DIR "$ENV{UNCC_ITCS_GRAPHICS}/Libraries")
else(NOT DIR STREQUAL "Math2D")
    get_filename_component(Math2D_DIR "${Math2D_DIR}/.." ABSOLUTE)
endif(NOT DIR STREQUAL "Math2D")
#message(STATUS "1: ${Math2D_DIR}")
zjw_find_package(Math2D Latest 
    "$ENV{UNCC_ITCS_GRAPHICS_SVN}/Libraries/Math2D"
    ${TARGET_CONFIG_PATH_SUFFIX} 
    STATIC 
    ${Math2D_DIR}
    )

## hacks for libraries that are not yet supported by standard CMake find_package
## (nor or have I had time to go the zjw_find_package route.)
# none


##
## set source code files for this project
##
set(SOURCES 
  Main.cpp
  #ITCS4120.vssettings  # \todo see [T2]
)

##
## set include directories, link directories, etc.
##
include_directories( 
   "${Math2D_INCLUDE_DIR}/."

   # For now, I list every TPL I've every used for any class project.
   # These have not been converted into the zjw_find_package convention
   # so must be installed and listed independently....
   #"$ENV{UNCC_ITCS_GRAPHICS}/Third Party Libraries/glew/include"
)

link_directories( 
       "${Math2D_LIBRARY_DIR}/."
	)  

##
## set compiler's pre-set macro definitions
##
add_definitions( 
	"${Math2D_DEFINITIONS}"
	)
if (CMAKE_HOST_WIN32)
    add_definitions( 
      -DWIN32
      -D_CONSOLE
      -D_DEBUG	    # \todo I'm suspicious of this. Its from vcproj2cmake.rb
    )
else(CMAKE_HOST_WIN32)
    # \todo add requirements for other OS's
endif(CMAKE_HOST_WIN32)

##
## add executable target to project
##
if (CMAKE_HOST_WIN32)
   # target .exe with spaces breaks the manifest file arguement
   # to the MSVS linker, so...
   set(TARGET_NAME "Test")
   add_executable(${TARGET_NAME} ${SOURCES} )

   # but this is ok...
   set_target_properties (${TARGET_NAME}
	PROPERTIES PROJECT_LABEL "Test"
	)
else(CMAKE_HOST_WIN32)
   set(TARGET_NAME "Test")
   add_executable(${TARGET_NAME} ${SOURCES} )
endif(CMAKE_HOST_WIN32)


##
## add dependent libraries
##

# for IDE/native build scripts
add_dependencies(${TARGET_NAME}
    	${Math2D_DEPENDENCY_TARGET} 
	)

# for linker
target_link_libraries( ${TARGET_NAME}
    ${Math2D_LIBRARIES}
    )
