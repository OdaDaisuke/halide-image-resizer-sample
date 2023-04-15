cmake_minimum_required(VERSION 3.22)

find_package(Halide REQUIRED)
find_package(OpenMP)

function(add_tutorial source_file)
    set(options WITH_IMAGE_IO WITH_OPENMP)
    set(oneValueArgs)
    set(multiValueArgs SRCS GROUPS)
    cmake_parse_arguments(args "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    cmake_path(GET source_file STEM name)

    add_executable("${name}" "${source_file}")
    target_link_libraries("${name}" PRIVATE Halide::Halide Halide::Tools)
    target_compile_options(${name} PRIVATE "$<$<CXX_COMPILER_ID:GNU>:-Wno-unused-but-set-variable>")

    add_test(NAME tutorial_${name} COMMAND ${name})
    set_tests_properties(tutorial_${name}
                         PROPERTIES
                         ENVIRONMENT "HL_TARGET=${Halide_TARGET};HL_JIT_TARGET=${Halide_TARGET}"
                         LABELS "tutorial;${args_GROUPS}")

    if (args_WITH_IMAGE_IO)
        target_link_libraries(${name} PRIVATE Halide::ImageIO)
    endif ()

    if (args_WITH_OPENMP)
        if (TARGET OpenMP::OpenMP_CXX)
            target_link_libraries(${name} PRIVATE OpenMP::OpenMP_CXX)
        else ()
            # Compile anyway but suppress warnings about unrecognised pragmas
            target_compile_options("${name}"
                                   PRIVATE
                                   $<$<CXX_COMPILER_ID:MSVC>:/Wd4068>
                                   $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wno-unknown-pragmas>)
        endif ()
    endif ()
endfunction()

add_tutorial(resizer.cpp WITH_IMAGE_IO)
