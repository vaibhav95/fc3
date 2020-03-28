set(PROJECT_NAME "test_all")

file(GLOB PROJECT_SOURCE_FILES "Src/*.cpp")
file(GLOB INCLUDE_FILES "*.hpp" "Inline/*.hpp")
set (DOC_FILES "*.hpp")
add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCE_FILES} ${INCLUDE_FILES})
target_link_libraries(${PROJECT_NAME} cfl)

configure_file (
  "${PROJECT_SOURCE_DIR}/test/Output.hpp.in"
  "${PROJECT_SOURCE_DIR}/test/Output.hpp"
  )
  
