cmake_minimum_required(VERSION 3.0...3.13)

# Sub-Projects
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/02_01_load_and_display_images")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/02_02_load_and_display_gray_images")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/02_03_image_properties")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/02_04_convert_and_save_images")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/02_05_split_and_merge_channels")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/02_06_concatenate_gray_images")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/02_07_concatenate_color_and_gray_images")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/02_08_region_of_interest")