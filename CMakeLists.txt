cmake_minimum_required(VERSION 4.3)

project(maka LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(maka
    src/main.c
    src/lexer/lexer.c
    src/util/memory.c
    src/util/array.c
)

target_include_directories(maka PRIVATE
    include
)

target_compile_options(maka PRIVATE
    -Werror
    -Wnullable-to-nonnull-conversion
)

target_compile_definitions(maka PRIVATE
    constexpr=constexpr
    nullptr=nullptr
    nullable=_Nullable
    nonnull=_Nonnull
    auto=auto
    var=auto
    let=const\ auto
)

set_target_properties(maka PROPERTIES
    C_CLANG_TIDY
    "clang-tidy;-checks=-*,clang-analyzer-nullability.*;--warnings-as-errors=clang-analyzer-nullability.*"
)

add_custom_target(run
    COMMAND maka
    DEPENDS maka
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

