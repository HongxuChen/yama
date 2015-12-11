file(GLOB BASE_FILES RangeAnalysisTest/*.cpp RangeAnalysis/*.cpp ClientRA/*.cpp vSSA/*.cpp uSSA/*.cpp RAInstrumentation/*.cpp RAPrinter) # OverflowDetect/*.cpp)

project(range)

add_library(${PROJECT_NAME} SHARED
  ${BASE_FILES}
  )

target_link_libraries(${PROJECT_NAME})
