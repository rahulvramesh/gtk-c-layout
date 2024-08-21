cmake_minimum_required(VERSION 3.10)
project(EmailClient C)

set(CMAKE_C_STANDARD 11)

# Find Homebrew prefix
execute_process(
        COMMAND brew --prefix
        OUTPUT_VARIABLE HOMEBREW_PREFIX
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Find packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(CURL REQUIRED libcurl)
find_package(OpenSSL REQUIRED)
find_package(SQLite3 REQUIRED)

# Set GTK3 directories
set(GTK3_PREFIX "${HOMEBREW_PREFIX}/opt/gtk+3")

# Include directories
include_directories(
        ${GTK3_INCLUDE_DIRS}
        ${GTK3_PREFIX}/include/gtk-3.0
        ${HOMEBREW_PREFIX}/opt/glib/include/glib-2.0
        ${HOMEBREW_PREFIX}/opt/glib/lib/glib-2.0/include
        ${HOMEBREW_PREFIX}/opt/pango/include/pango-1.0
        ${HOMEBREW_PREFIX}/opt/harfbuzz/include/harfbuzz
        ${HOMEBREW_PREFIX}/opt/cairo/include/cairo
        ${HOMEBREW_PREFIX}/opt/gdk-pixbuf/include/gdk-pixbuf-2.0
        ${HOMEBREW_PREFIX}/opt/atk/include/atk-1.0
        ${CURL_INCLUDE_DIRS}
        ${OPENSSL_INCLUDE_DIR}
        ${SQLite3_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/include
)

# Link directories
link_directories(${GTK3_LIBRARY_DIRS})

# Add subdirectories
add_subdirectory(src)

# Main executable
add_executable(email_client src/main.c)

# Link libraries
target_link_libraries(email_client
        ${GTK3_LIBRARIES}
        ${CURL_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        ${SQLite3_LIBRARIES}
        m
)

# Install
install(TARGETS email_client DESTINATION bin)