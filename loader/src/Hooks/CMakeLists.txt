message("Adding hook target sources to ${PROJECT_NAME}")

target_sources(${PROJECT_NAME} PRIVATE 
	"${CMAKE_CURRENT_SOURCE_DIR}/AspyrHooks.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/CEngineHooks.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/DirectXHooks.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/GuitarFuncs.cpp"
)