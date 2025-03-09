message("Processing ${CMAKE_CURRENT_SOURCE_DIR} - ${PROJECT_NAME}")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Internal")


target_sources(${PROJECT_NAME} PRIVATE 
	"${CMAKE_CURRENT_SOURCE_DIR}/CommandConsole.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Hook.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Profile.cpp"
)