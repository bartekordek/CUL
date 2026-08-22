function(cul_setup_target TARGET)
    # ============================================================
    # Compile options
    # ============================================================

    if(MSVC)
        target_compile_options(${TARGET} PRIVATE
            "$<$<CONFIG:Test>:/Ot>"
            "$<$<CONFIG:Test>:/Oi>"
            "$<$<CONFIG:Release>:/Ot>"
            "$<$<CONFIG:Release>:/Oi>"
        )
    endif()


    # ============================================================
    # Configuration defines
    # ============================================================

    target_compile_definitions(${TARGET} PRIVATE
        "$<$<CONFIG:Debug>:CUL_DEBUG=1>"
        "$<$<CONFIG:Test>:CUL_TEST=1>"
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
        INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE
    )


    # ============================================================
    # Linker options
    # ============================================================

    if(MSVC)
        target_link_options(${TARGET} PRIVATE
            "$<$<CONFIG:Debug>:/INCREMENTAL:NO>"
            "$<$<CONFIG:Release>:/INCREMENTAL:NO>"
            "$<$<CONFIG:Test>:/LTCG:INCREMENTAL>"
            "$<$<CONFIG:Release>:/LTCG>"
        )
    endif()
endfunction()