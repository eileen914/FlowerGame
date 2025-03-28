cmake_minimum_required(VERSION 3.30)
project(FlowerGame)

set(CMAKE_CXX_STANDARD 17)

# SFML 라이브러리 찾기
find_package(SFML 2.6 COMPONENTS graphics REQUIRED)

# 실행 파일 생성
add_executable(FlowerGame main.cpp Flower.cpp)

# SFML 라이브러리와 링크
target_link_libraries(FlowerGame sfml-graphics sfml-window sfml-system)