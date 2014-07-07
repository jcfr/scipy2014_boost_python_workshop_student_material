###########################################################################
#
#  Copyright (c) Kitware Inc.
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0.txt
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
#  This file was originally developed by Jean-Christophe Fillion-Robin, Kitware Inc.
#
###########################################################################

cmake_minimum_required(VERSION 2.8.9)
project(SciPy2014BoostPython)

include(CTest)

#
# Dependencies
#
find_package(PythonLibs 2.7 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

find_package(Boost COMPONENTS python REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# Convenience function to configure python boost module
function(scipy_workshop_add_module libname sources)
  add_library(${libname} MODULE ${sources})
  target_link_libraries(${libname} ${PYTHON_LIBRARIES} ${Boost_LIBRARIES})
  set_target_properties(${libname} PROPERTIES PREFIX "")
  if(WIN32 AND NOT CYGWIN)
    set_target_properties(${libname}PythonQt PROPERTIES SUFFIX ".pyd")
  endif()
endfunction()

#
# CheckEnv
#
add_executable(plumbing_test exercises/plumbing_test.cpp)
target_link_libraries(plumbing_test ${PYTHON_LIBRARIES} ${Boost_LIBRARIES})

scipy_workshop_add_module(smoke_test exercises/smoke_test.cpp)
scipy_workshop_add_module(hello_world exercises/hello_world.cpp)

#
# CheckEnv tests
#
if(BUILD_TESTING)
  find_package(PythonInterp 2.7 REQUIRED)

  add_test(NAME plumbing_test COMMAND $<TARGET_FILE:plumbing_test>)
  add_test(NAME smoke_test COMMAND ${PYTHON_EXECUTABLE} -c "import smoke_test; print(smoke_test.test())")
  set_tests_properties(smoke_test PROPERTIES PASS_REGULAR_EXPRESSION "42")
endif()

#
# Exercises
#
scipy_workshop_add_module(exceptions    exercises/exceptions/exceptions.cpp)
scipy_workshop_add_module(rps           exercises/rps/rps.cpp)
scipy_workshop_add_module(call_policies exercises/call_policies/call_policies.cpp)

#
# Answers
#
scipy_workshop_add_module(exceptions_answer_01      answers/exceptions/exceptions.01.cpp)
scipy_workshop_add_module(exceptions_answer_02      answers/exceptions/exceptions.02.cpp)
scipy_workshop_add_module(exceptions_answer_03      answers/exceptions/exceptions.03.cpp)

foreach(id RANGE 1 16)
  # XXX Pad with an extra zero
  string(LENGTH "${id}" _id_len)
  if(_id_len EQUAL 1)
    set(id "0${id}")
  endif()
  scipy_workshop_add_module(rps_answer_${id} answers/rps/rps.${id}.cpp)
endforeach()

scipy_workshop_add_module(call_policies_answer_01 answers/call_policies/call_policies.01.cpp)
scipy_workshop_add_module(call_policies_answer_02 answers/call_policies/call_policies.02.cpp)


