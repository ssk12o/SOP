cmake_minimum_required(VERSION 3.10)

link_libraries(pthread rt)

add_executable(07synchro_1_semaphore_base 01_semaphore_base.c)
add_executable(07synchro_11_sem_open 11_sem_open.c)
add_executable(07synchro_13_mtx_attributes 13_mtx_attributes.c)
add_executable(07synchro_14_cv_base 14_cv_base.c)
add_executable(07synchro_15_cv 15_cv.c)
