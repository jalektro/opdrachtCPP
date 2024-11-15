# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\WeaponSystemAPI_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\WeaponSystemAPI_autogen.dir\\ParseCache.txt"
  "WeaponSystemAPI_autogen"
  )
endif()
