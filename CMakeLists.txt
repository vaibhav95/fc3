cmake_minimum_required (VERSION 3.10)

project(FC-III VERSION 1.0 LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-Wall")

set(OUTPUT_DIR "${PROJECT_BINARY_DIR}/output")
include_directories(${CMAKE_SOURCE_DIR})

# documentation with Doxygen
set(CFL_DOC NO)
if(${CFL_DOC})
message("Looking for Doxygen to prepare documentation ...")
find_package(Doxygen REQUIRED dot)
  set(DOXYGEN_EXTERNAL_GROUPS NO) 
  set(CFL_DOC_DIR "${PROJECT_BINARY_DIR}/doc")
  set(STD_TAG "${PROJECT_SOURCE_DIR}/cfl/cppreference-doxygen-web.tag.xml=http://en.cppreference.com/w/")
  set(CFL_TAG "${CFL_DOC_DIR}/cfl/cfl.tag=${CFL_DOC_DIR}/cfl/html")
endif ()

# GSL
# if GSl is not found, write the root directory containing gsl
# set (GSL_ROOT_DIR "C:/msys64/mingw32")
find_package(GSL REQUIRED)
message("GSL include dir: " ${GSL_INCLUDE_DIRS})
message("GSL library: " ${GSL_LIBRARY})
message("BLAS library:" ${GSL_CBLAS_LIBRARY})
include_directories(${GSL_INCLUDE_DIRS})

# write your Student ID in ""
set (STUDENT_ID "vgoel2")

# add subdicretories below, when you need them
add_subdirectory(cfl)
add_subdirectory(test)
add_subdirectory(test_cfl)

add_subdirectory(prb)
# add_subdirectory(test_prb)

add_subdirectory(test_set1)
add_subdirectory(test_set2)
# add_subdirectory(test_set3)
# add_subdirectory(test_set4)
# add_subdirectory(test_set5)
# add_subdirectory(test_set6)
# add_subdirectory(test_set7)
# add_subdirectory(test_set8)
# add_subdirectory(test_set9)
# add_subdirectory(test_set10)

# add_subdirectory(Exam)
# add_subdirectory(test_Exam)

