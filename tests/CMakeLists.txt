set(TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB FILES "${TEST_DIR}/*")

string(ASCII 27 ESC)
message("-- ${ESC}[33mAdding test files...${ESC}[m")

message("Test files are in " ${TEST_DIR})
foreach(FILE ${FILES})
	get_filename_component(FILE_NAME "${FILE}" NAME_WE)
	get_filename_component(FILE_EXT "${FILE}" EXT)

	if(${FILE_EXT} STREQUAL ".cpp")
	  message("Adding test: " ${FILE_NAME} " from " ${FILE})
	  add_executable(ege3d-test-${FILE_NAME} ${FILE})
	  target_link_libraries(ege3d-test-${FILE_NAME} PUBLIC ege3d)
	  target_include_directories(ege3d-test-${FILE_NAME} PUBLIC ${CMAKE_SOURCE_DIR})
	endif()
endforeach()
