add_subdirectory(mips)

set(ARCH_SRCS
  tac.cc
  )

add_library(arch ${ARCH_SRCS}
  $<TARGET_OBJECTS:mips>
  )

