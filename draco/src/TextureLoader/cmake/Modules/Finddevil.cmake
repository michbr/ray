# - Try to find LibXml2
# Once done this will define
#  LIBXML2_FOUND - System has LibXml2
#  LIBXML2_INCLUDE_DIRS - The LibXml2 include directories
#  LIBXML2_LIBRARIES - The libraries needed to use LibXml2
#  LIBXML2_DEFINITIONS - Compiler switches required for using LibXml2

find_package(PkgConfig)
pkg_check_modules(PC_IL REQUIRED IL)
set(DEVIL_DEFINITIONS ${PC_IL_CFLAGS_OTHER})

find_path(IL_INCLUDE_DIR IL/il.h
	  HINTS ${PC_IL_INCLUDEDIR} ${PC_IL_INCLUDE_DIRS})

find_library(IL_LIBRARY NAMES IL
             HINTS ${PC_IL_LIBDIR} ${PC_IL_LIBRARY_DIRS} )

set(IL_LIBRARIES ${IL_LIBRARY} )
set(IL_INCLUDE_DIRS ${IL_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBXML2_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(IL DEFAULT_MSG
                                  IL_LIBRARY IL_INCLUDE_DIR)

mark_as_advanced(IL_INCLUDE_DIR IL_LIBRARY )
