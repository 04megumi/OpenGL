#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "glm::glm" for configuration "Release"
set_property(TARGET glm::glm APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(glm::glm PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libglm.dylib"
  IMPORTED_SONAME_RELEASE "@rpath/libglm.dylib"
  )

list(APPEND _cmake_import_check_targets glm::glm )
list(APPEND _cmake_import_check_files_for_glm::glm "${_IMPORT_PREFIX}/lib/libglm.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
