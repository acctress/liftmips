add_executable(liftmips_tests
        decoder.cpp
        translator.cpp)

target_include_directories(liftmips_tests PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(liftmips_tests PRIVATE Catch2::Catch2WithMain)

set_target_properties(liftmips_tests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/exe"
)

include(CTest)
include(Catch)
catch_discover_tests(liftmips_tests)