# Silence compiler warnings for third-party (deps/) targets on Windows and Linux.
# INTERFACE libraries are only marked SYSTEM (nothing to compile).
function(cul_disable_third_party_warnings target_name)
    if(NOT TARGET ${target_name})
        return()
    endif()

    get_target_property(_cul_aliased ${target_name} ALIASED_TARGET)
    if(_cul_aliased)
        return()
    endif()

    get_target_property(_cul_type ${target_name} TYPE)
    if(_cul_type STREQUAL "UTILITY")
        return()
    endif()

    if(_cul_type STREQUAL "INTERFACE_LIBRARY")
        if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.25")
            set_target_properties(${target_name} PROPERTIES SYSTEM TRUE)
        endif()
        message(STATUS "Silencing third-party warnings (SYSTEM): ${target_name}")
        return()
    endif()

    # Appended after the dep's own flags so /W0 and -w win on MSVC/GCC/Clang.
    if(MSVC)
        target_compile_options(${target_name} PRIVATE /W0)
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
        target_compile_options(${target_name} PRIVATE -w)
    endif()

    if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.25")
        set_target_properties(${target_name} PROPERTIES SYSTEM TRUE)
    endif()
    message(STATUS "Silencing third-party warnings: ${target_name}")
endfunction()

# Legacy name used in root CMakeLists.txt
function(disable_third_party_warnings target_name)
    cul_disable_third_party_warnings(${target_name})
endfunction()

macro(cul_get_all_targets_recursive out_var dir)
    get_property(_cul_subdirs DIRECTORY "${dir}" PROPERTY SUBDIRECTORIES)
    foreach(_cul_subdir IN LISTS _cul_subdirs)
        cul_get_all_targets_recursive(${out_var} "${_cul_subdir}")
    endforeach()
    get_property(_cul_dir_targets DIRECTORY "${dir}" PROPERTY BUILDSYSTEM_TARGETS)
    list(APPEND ${out_var} ${_cul_dir_targets})
endmacro()

# Silence every buildsystem target whose SOURCE_DIR lives under deps_root.
function(cul_silence_warnings_for_deps_dir deps_root)
    set(_cul_all_targets "")
    cul_get_all_targets_recursive(_cul_all_targets "${CMAKE_CURRENT_SOURCE_DIR}")

    file(TO_CMAKE_PATH "${deps_root}" _cul_deps_root)
    string(LENGTH "${_cul_deps_root}" _cul_deps_root_len)

    foreach(_cul_t IN LISTS _cul_all_targets)
        if(NOT TARGET ${_cul_t})
            # skip
        else()
            get_target_property(_cul_src ${_cul_t} SOURCE_DIR)
            if(_cul_src)
                file(TO_CMAKE_PATH "${_cul_src}" _cul_src_norm)
                string(FIND "${_cul_src_norm}" "${_cul_deps_root}" _cul_pos)
                if(_cul_pos EQUAL 0)
                    cul_disable_third_party_warnings(${_cul_t})
                endif()
            endif()
        endif()
    endforeach()
endfunction()

function(cul_setup_target TARGET)
    # ============================================================
    # Compile options
    # ============================================================

    if(MSVC)
        target_compile_options(${TARGET} PRIVATE
            "$<$<CONFIG:Test>:/Ot>"
            "$<$<CONFIG:Test>:/Oi>"
            "$<$<CONFIG:Test>:/Ob2>"
            "$<$<CONFIG:RelWithDebInfo>:/Ot>"
            "$<$<CONFIG:RelWithDebInfo>:/Oi>"
            "$<$<CONFIG:RelWithDebInfo>:/Ob2>"
            "$<$<CONFIG:Release>:/Ot>"
            "$<$<CONFIG:Release>:/Oi>"
            "$<$<CONFIG:Release>:/Ob2>"
        )
    endif()


    # ============================================================
    # Configuration defines
    # ============================================================

    target_compile_definitions(${TARGET} PRIVATE
        "$<$<CONFIG:Debug>:CUL_DEBUG=1>"
        "$<$<CONFIG:Test>:CUL_TEST=1>"
        "$<$<CONFIG:RelWithDebInfo>:CUL_RELWITHDEBINFO=1>"
        "$<$<CONFIG:Release>:CUL_RELEASE=1>"
    )


    # ============================================================
    # LTO / IPO
    # ============================================================

    set_property(TARGET ${TARGET} PROPERTY
        INTERPROCEDURAL_OPTIMIZATION_DEBUG FALSE
    )

    set_property(TARGET ${TARGET} PROPERTY
        INTERPROCEDURAL_OPTIMIZATION_TEST TRUE
    )

    set_property(TARGET ${TARGET} PROPERTY
        INTERPROCEDURAL_OPTIMIZATION_RELWITHDEBINFO TRUE
    )

    set_property(TARGET ${TARGET} PROPERTY
        INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE
    )


    # ============================================================
    # Linker options
    # ============================================================

    if(MSVC)
        target_link_options(${TARGET} PRIVATE
            "$<$<CONFIG:Debug>:/INCREMENTAL:NO>"
            "$<$<CONFIG:Test>:/LTCG:INCREMENTAL>"
            "$<$<CONFIG:RelWithDebInfo>:/INCREMENTAL:NO>"
            "$<$<CONFIG:RelWithDebInfo>:/LTCG>"
            "$<$<CONFIG:Release>:/INCREMENTAL:NO>"
            "$<$<CONFIG:Release>:/LTCG>"
        )
    endif()
endfunction()