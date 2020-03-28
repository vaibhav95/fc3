set(PROJECT_NAME "prb")

file(GLOB PROJECT_SOURCE_FILES "Src/*.cpp")
file(GLOB INCLUDE_FILES "*.hpp")
file(GLOB DOC_FILES "*.hpp")
add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCE_FILES} ${INCLUDE_FILES})
target_link_libraries(${PROJECT_NAME} cfl)
target_link_libraries(${PROJECT_NAME} ${GSL_LIBRARIES})

if(${CFL_DOC} AND Doxygen_FOUND)
file(MAKE_DIRECTORY "${CFL_DOC_DIR}/${PROJECT_NAME}/html")    
set(DOXYGEN_PROJECT_NAME ${PROJECT_NAME})
set(DOXYGEN_TAGFILES "${CFL_TAG};${STD_TAG}")
set(DOXYGEN_OUTPUT_DIRECTORY "${CFL_DOC_DIR}/${PROJECT_NAME}")
doxygen_add_docs(
  doc-${PROJECT_NAME}
  ALL
  ${DOC_FILES}
  )
endif()
