project(base-utils)

set(BASE_SRC_LIST misc.cpp debugging.cpp logger.cpp)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(BASE_LIB baseutils_base)
add_library(${BASE_LIB} STATIC ${BASE_SRC_LIST})

#if(NOT NO_TCMALLOC)
#   target_link_libraries(tcmalloc)
#   add_dependencies(${BASE_LIB} libtcmalloc)
#endif()

