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

project( "PlanetMobile" )

##
## find libraries 
##

# find libraries available through standard Cmake mechanisms...
#   -NONE

# find libraries available through zjw_find_package mechanism... 
get_filename_component(TPL_DIR_FULL_PATH "$ENV{UNCC_ITCS_GRAPHICS}/Third Party Libraries"
	ABSOLUTE)
message(STATUS "${TPL_DIR_FULL_PATH}")

zjw_find_package(Math2D Latest
    "$ENV{UNCC_ITCS_GRAPHICS_SVN}/Libraries/Math2D"
    ${TARGET_CONFIG_PATH_SUFFIX} 
    STATIC 
    "$ENV{UNCC_ITCS_GRAPHICS}/Libraries")

zjw_find_package(OpenGLTrainer Latest 
    "svn://linux01.uncc.edu:3690/zwartell-public/ITCS 6120-8120/OpenGLTrainer/trunk"
    ${TARGET_CONFIG_PATH_SUFFIX} 
    STATIC 
    ${TPL_DIR_FULL_PATH})

if (CMAKE_HOST_WIN32)
    zjw_find_package(glut 3.7.6 
	"svn://linux01.uncc.edu:3690/zwartell-public/vendor/opengl.org/glut/" 
	${TARGET_CONFIG_PATH_SUFFIX} 
	STATIC 
	${TPL_DIR_FULL_PATH})
endif (CMAKE_HOST_WIN32)# AND FALSE)

## hacks for libraries that are not yet supported by standard CMake find_package
## (nor or have I had time to go the zjw_find_package route.)
# none


##
## set source code files for this project
##
set(SOURCES 
  CoordinateSystem.h
  CoordinateSystem.cpp
  Shape.h
  Shape.cpp
  UnitDisk.h
  UnitDisk.cpp
  Main.cpp
  #ITCS4120.vssettings  # \todo see [T2]
)

##
## set include directories, link directories, etc.
##
include_directories( 
   "${Math2D_INCLUDE_DIR}/."
   "${GLUT_INCLUDE_DIR}/."
   "${OpenGLTrainer_INCLUDE_DIR}/."

   # For now, I list every TPL I've every used for any class project.
   # These have not been converted into the zjw_find_package convention
   # so must be installed and listed independently....
   #"$ENV{UNCC_ITCS_GRAPHICS}/Third Party Libraries/glew/include"
)

link_directories( 
       "${Math2D_LIBRARY_DIR}/."
       "${GLUT_LIBRARY_DIR}/."
       "${OpenGLTrainer_LIBRARY_DIR}/."
	)  

##
## set compiler's pre-set macro definitions
##
add_definitions( 
	"${Math2D_DEFINITIONS}"
	"${GLUT_DEFINITIONS}"
	"${OpenGLTrainer_DEFINITIONS}"
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
   set(TARGET_NAME "PlanetMobile")
   add_executable(${TARGET_NAME} ${SOURCES} )

   # but this is ok...
   set_target_properties (${TARGET_NAME}
	PROPERTIES PROJECT_LABEL "PlanetMobile"
	)
else(CMAKE_HOST_WIN32)
   set(TARGET_NAME "PlanetMobile")
   add_executable(${TARGET_NAME} ${SOURCES} )
endif(CMAKE_HOST_WIN32)


##
## add dependent libraries
##

# for IDE/native build scripts
add_dependencies(${TARGET_NAME}
    	${Math2D_DEPENDENCY_TARGET} 
    	${GLUT_DEPENDENCY_TARGET} 
    	${OpenGLTrainer_DEPENDENCY_TARGET} 
	)

# for linker
target_link_libraries( ${TARGET_NAME}
    ${Math2D_LIBRARIES}
    ${GLUT_LIBRARIES}
    ${OpenGLTrainer_LIBRARIES}
    )
