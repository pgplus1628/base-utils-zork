#project(base-utils)

if(BUILD_TESTING)
  add_base_executable(test-logger test-logger.cpp)
  add_test(logger test-logger)
endif(BUILD_TESTING)

