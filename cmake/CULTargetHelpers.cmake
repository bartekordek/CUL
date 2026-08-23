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