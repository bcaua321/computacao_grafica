# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/computacao_grafica_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/computacao_grafica_autogen.dir/ParseCache.txt"
  "computacao_grafica_autogen"
  )
endif()
