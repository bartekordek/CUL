function(setup_ispc)

    set(options)

    set(oneValueArgs
        VERSION
    )

    cmake_parse_arguments(
        ISPC
        "${options}"
        "${oneValueArgs}"
        ""
        ${ARGN}
    )

    if(NOT ISPC_VERSION)
        message(FATAL_ERROR "setup_ispc requires VERSION")
    endif()

    # --------------------------------------------------------------------------
    # Platform detection
    # --------------------------------------------------------------------------

    if(WIN32)
        set(ISPC_PLATFORM "windows")
        set(ISPC_DIR ispc-v${ISPC_VERSION}-windows)
        set(ISPC_ARCHIVE "${ISPC_DIR}.zip")
        set(ISPC_EXECUTABLE_NAME "ispc.exe")
    elseif(UNIX)
        set(ISPC_PLATFORM "linux")
        set(ISPC_DIR ispc-v${ISPC_VERSION}-linux)
        set(ISPC_ARCHIVE "${ISPC_DIR}.tar.gz")
        set(ISPC_EXECUTABLE_NAME "ispc")
    else()
        message(FATAL_ERROR "Unsupported platform")
    endif()

    message(STATUS "Detected platform: ${ISPC_PLATFORM}")
    message(STATUS "ISPC directory: ${ISPC_DIR}")
    message(STATUS "ISPC archive: ${ISPC_ARCHIVE}")
    message(STATUS "ISPC executable name: ${ISPC_EXECUTABLE_NAME}")

    # --------------------------------------------------------------------------
    # Paths
    # --------------------------------------------------------------------------

    message(STATUS "CUL_ROOT_DIR: ${CUL_ROOT_DIR}")

    set(ISPC_ROOT "${CUL_ROOT_DIR}/tools/${ISPC_DIR}")
    message(STATUS "ISPC root: ${ISPC_ROOT}")

    set(ISPC_EXECUTABLE "${ISPC_ROOT}/bin/${ISPC_EXECUTABLE_NAME}" PARENT_SCOPE)
    message(STATUS "ISPC executable: ${ISPC_EXECUTABLE}")

    set(ISPC_URL "https://github.com/ispc/ispc/releases/download/v${ISPC_VERSION}/${ISPC_ARCHIVE}")
    message(STATUS "ISPC URL: ${ISPC_URL}")

    set(ISPC_ARCHIVE_PATH "${CUL_ROOT_DIR}/tools/${ISPC_ARCHIVE}")
    message(STATUS "ISPC archive path: ${ISPC_ARCHIVE_PATH}")

    # https://github.com/ispc/ispc/releases/download/v1.25.3/ispc-v1.25.3-linux.tar.gz

    # --------------------------------------------------------------------------
    # Download if missing
    # --------------------------------------------------------------------------

    message("Checking for ${ISPC_EXECUTABLE}...")
    if(NOT EXISTS "${ISPC_EXECUTABLE}")

        message("${ISPC_EXECUTABLE} not found.")

        if(NOT EXISTS "${ISPC_ARCHIVE_PATH}")
            message(STATUS "Downloading ISPC ${ISPC_VERSION} to ${ISPC_ARCHIVE_PATH}")
            file(
                DOWNLOAD
                "${ISPC_URL}"
                "${ISPC_ARCHIVE_PATH}"
                SHOW_PROGRESS
                STATUS DOWNLOAD_STATUS
            )

            list(GET DOWNLOAD_STATUS 0 STATUS_CODE)

            if(STATUS_CODE EQUAL 0)
                message(STATUS "Download completed.")
            else()
                message(FATAL_ERROR "Failed to download ISPC")
            endif()
        endif()

        file(
            ARCHIVE_EXTRACT
            INPUT "${ISPC_ARCHIVE_PATH}"
            DESTINATION "${CUL_ROOT_DIR}/tools/"
        )

    endif()

    # --------------------------------------------------------------------------
    # Export compiler path to parent scope
    # --------------------------------------------------------------------------

    set(
        CMAKE_ISPC_COMPILER
        "${ISPC_EXECUTABLE}"
        CACHE FILEPATH
        "ISPC compiler"
        FORCE
    )

    message(STATUS "ISPC compiler:")
    message(STATUS "  ${CMAKE_ISPC_COMPILER}")

endfunction()


function(add_ispc_sources TARGET)

    set(options)
    set(oneValueArgs)
    set(multiValueArgs SOURCES)

    cmake_parse_arguments(ISPC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT ISPC_SOURCES)
        message(FATAL_ERROR "add_ispc_sources: SOURCES is empty")
    endif()

    if(NOT ISPC_EXECUTABLE)
        message(FATAL_ERROR "ISPC_EXECUTABLE is not set")
    endif()

    if(NOT ISPC_TARGET)
        set(ISPC_TARGET "avx2-i32x8")
    endif()

    set(GENERATED_OBJS "")
    set(GENERATED_HEADERS "")

    foreach(ISPC_FILE IN LISTS ISPC_SOURCES)

        get_filename_component(NAME_WE "${ISPC_FILE}" NAME_WE)

        set(OBJ_FILE
            "${CMAKE_CURRENT_BINARY_DIR}/${TARGET}_${NAME_WE}.ispc.obj"
        )

        set(HEADER_FILE
            "${CMAKE_CURRENT_BINARY_DIR}/${TARGET}_${NAME_WE}.ispc.h"
        )

        add_custom_command(
            OUTPUT
                "${OBJ_FILE}"
                "${HEADER_FILE}"

            COMMAND
                "${ISPC_EXECUTABLE}"
                "${ISPC_FILE}"
                -o "${OBJ_FILE}"
                -h "${HEADER_FILE}"
                --target=${ISPC_TARGET}

            DEPENDS
                "${ISPC_FILE}"

            COMMENT
                "ISPC [${TARGET}] compiling ${ISPC_FILE}"

            VERBATIM
        )

        list(APPEND GENERATED_OBJS "${OBJ_FILE}")
        list(APPEND GENERATED_HEADERS "${HEADER_FILE}")

    endforeach()

    # Attach generated objects to real target
    target_sources(${TARGET} PRIVATE ${GENERATED_OBJS})

    # Ensure headers are visible in IDEs (optional but nice)
    source_group("Generated\\ISPC" FILES ${GENERATED_OBJS} ${GENERATED_HEADERS})

    # Make sure include dir is available for generated headers
    target_include_directories(${TARGET} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")

    message(STATUS "ISPC added to target: ${TARGET}")
    message(STATUS "  files: ${ISPC_SOURCES}")

endfunction()