file(GLOB BASE_FILES RangeAnalysis/*.cpp vSSA/*.cpp RAInstrumentation/*.cpp RAPrinter OverflowDetect/*.cpp)

project(base)

add_library(${PROJECT_NAME}
  ${BASE_FILES}
  )

target_link_libraries(${PROJECT_NAME} utils)
