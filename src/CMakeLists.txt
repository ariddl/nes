target_sources(${PROJECT_NAME} PRIVATE nes.h)

add_subdirectory(rom)
add_subdirectory(hardware)
add_subdirectory(platform)

target_include_directories(${PROJECT_NAME} PRIVATE
  rom
  hardware
  platform
)