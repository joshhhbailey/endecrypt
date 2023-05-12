add_executable(${TARGETNAME})

target_sources(${TARGETNAME} PRIVATE
	# .cpp
	${PROJECT_SOURCE_DIR}/src/app/main.cpp
	${PROJECT_SOURCE_DIR}/src/app/MainWindow.cpp
	${PROJECT_SOURCE_DIR}/src/app/EndecryptWidget.cpp
	
	# .h
	${PROJECT_SOURCE_DIR}/include/app/MainWindow.h
	${PROJECT_SOURCE_DIR}/include/app/EndecryptWidget.h
)

target_include_directories(${TARGETNAME} PRIVATE ${CMAKE_SOURCE_DIR}/include/app)
target_link_libraries(${TARGETNAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(${TARGETNAME} PRIVATE cryptopp::cryptopp)

set_target_properties(${TARGETNAME} PROPERTIES
    WIN32_EXECUTABLE ON		# Prevent the creation of a console window on Windows [THIS MIGHT BE PROBLEMATIC]
    MACOSX_BUNDLE ON		# Create an application bundle on macOS
)

install(TARGETS ${TARGETNAME} DESTINATION bin)
install(DIRECTORY ../../dependencies/platforms DESTINATION bin)
install(FILES 
			../../dependencies/Qt6Core.dll
			../../dependencies/Qt6Gui.dll
			../../dependencies/Qt6Widgets.dll
		DESTINATION bin)