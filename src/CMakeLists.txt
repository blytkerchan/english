# SHARED library
add_library(english-shared SHARED "")

include(GenerateExportHeader)
generate_export_header(english-shared
	BASE_NAME "english"
	EXPORT_MACRO_NAME "english_EXPORT"
	EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/english-export.h"
	DEPRECATED_MACRO_NAME "english_DEPRECATED"
	NO_EXPORT_MACRO_NAME "english_NO_EXPORT"
	STATIC_DEFINE "english_STATIC_DEFINE"
	NO_DEPRECATED_MACRO_NAME "english_NO_DEPRECATED"
	DEFINE_NO_DEPRECATED
	)

if (WIN32 AND NOT CYGWIN)
	set(TARGET_PLATFORM win32)
else()
	set(TARGET_PLATFORM posix)
endif()

set(ENGLISH_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/details/extractor.cpp
	${CMAKE_CURRENT_LIST_DIR}/poet.cpp
	)
set(ENGLISH_HEADERS
	${CMAKE_CURRENT_LIST_DIR}/details/extractor.hpp
	${CMAKE_CURRENT_LIST_DIR}/poet.hpp
	${CMAKE_CURRENT_LIST_DIR}/words/adjectives.hpp
	${CMAKE_CURRENT_LIST_DIR}/words/adverbs.hpp
	${CMAKE_CURRENT_LIST_DIR}/words/articles.hpp
	${CMAKE_CURRENT_LIST_DIR}/words/nouns.hpp
	${CMAKE_CURRENT_LIST_DIR}/words/prepositions.hpp
	${CMAKE_CURRENT_LIST_DIR}/words/verbsi.hpp
	${CMAKE_CURRENT_LIST_DIR}/words/verbst.hpp
	)

target_sources(english-shared
	PRIVATE
	${ENGLISH_SOURCES}
	)

target_compile_definitions(english-shared
	INTERFACE
	$<INSTALL_INTERFACE:USING_english>
	)

target_include_directories(english-shared
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}>
	$<INSTALL_INTERFACE:${INSTALL_INCLUDEDIR}>
	)

set_target_properties(english-shared
	PROPERTIES
	POSITION_INDEPENDENT_CODE 1
	CXX_VISIBILITY_PRESET hidden
	VISIBILITY_INLINES_HIDDEN 1
	SOVERSION ${PROJECT_VERSION_MAJOR}
	OUTPUT_NAME "english"
	DEBUG_POSTFIX "_d"
	PUBLIC_HEADER "${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/english-export.h;${ENGLISH_HEADERS}"
	MACOSX_RPATH ON
	)

# STATIC library
add_library(english-static STATIC "")

target_sources(english-static
	PRIVATE
	${ENGLISH_SOURCES}
	)

target_compile_definitions(english-static
	PUBLIC
	INTERFACE
	$<INSTALL_INTERFACE:USING_english>
	)

target_include_directories(english-static
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}>
	$<INSTALL_INTERFACE:${INSTALL_INCLUDEDIR}>
	)

set_target_properties(english-static
	PROPERTIES
	POSITION_INDEPENDENT_CODE 1
	ARCHIVE_OUTPUT_NAME "english"
	DEBUG_POSTFIX "_sd"
	RELEASE_POSTFIX "_s"
	PUBLIC_HEADER "${CMAKE_BINARY_DIR}/${INSTALL_INCLUDEDIR}/english-export.h;${ENGLISH_HEADERS}"
	)

# <<< Install and export targets >>>

install(
	TARGETS
	english-shared
	english-static
	EXPORT
	englishTargets
	ARCHIVE
	DESTINATION ${INSTALL_LIBDIR}
	COMPONENT lib
	RUNTIME
	DESTINATION ${INSTALL_BINDIR}
	COMPONENT bin
	LIBRARY
	DESTINATION ${INSTALL_LIBDIR}
	COMPONENT lib
	PUBLIC_HEADER
	DESTINATION ${INSTALL_INCLUDEDIR}/english
	COMPONENT dev
	)

install(
	EXPORT
	englishTargets
	NAMESPACE
	"english::"
	DESTINATION
	${INSTALL_CMAKEDIR}
	COMPONENT
	dev
	)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/englishConfigVersion.cmake
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion
	)

configure_package_config_file(
	${PROJECT_SOURCE_DIR}/cmake/englishConfig.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/englishConfig.cmake
	INSTALL_DESTINATION ${INSTALL_CMAKEDIR}
	)

install(
	FILES
	${CMAKE_CURRENT_BINARY_DIR}/englishConfig.cmake
	${CMAKE_CURRENT_BINARY_DIR}/englishConfigVersion.cmake
	DESTINATION
	${INSTALL_CMAKEDIR}
	)

