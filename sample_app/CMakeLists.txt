project(sample_app)

file(GLOB PROJ_SRC *.c)

add_executable(${PROJECT_NAME} ${PROJ_SRC})
target_link_libraries(${PROJECT_NAME} flecs_app)
