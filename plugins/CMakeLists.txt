# Check that people use the good file
if(NOT TOP_CMAKE_WAS_SOURCED)
    message(FATAL_ERROR "
    You did not 'cmake' the good CMakeLists.txt file. Use the one in the top dir.
    It is advice to delete all wrongly generated cmake stuff => CMakeFiles & CMakeCache.txt")
endif()


if(EXISTS "${CMAKE_SOURCE_DIR}/plugins/dev9null" AND dev9null)
	add_subdirectory(dev9null)
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/plugins/dev9ghzdrk" AND dev9ghzdrk AND NOT LIBRETRO)
	add_subdirectory(dev9ghzdrk)
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/plugins/GSdx" AND GSdx)
	add_subdirectory(GSdx)
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/plugins/GSnull" AND GSnull)
	add_subdirectory(GSnull)
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/plugins/LilyPad" AND LilyPad AND NOT LIBRETRO)
	add_subdirectory(LilyPad)
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/plugins/onepad" AND onepad)
	add_subdirectory(onepad)
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/plugins/onepad_legacy" AND onepad_legacy AND NOT LIBRETRO)
	add_subdirectory(onepad_legacy)
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/plugins/PadNull" AND PadNull)
	add_subdirectory(PadNull)
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/plugins/USBnull" AND USBnull)
	add_subdirectory(USBnull)
endif()
