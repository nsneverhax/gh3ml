message("Adding ImGUI target sources to ${PROJECT_NAME}")

target_sources(${PROJECT_NAME} PRIVATE 
	"${CMAKE_CURRENT_SOURCE_DIR}/ImGUI.cpp"
)