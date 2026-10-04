CXX := g++
CXXFLAGS := -std=c++20

TARGET := output/first_image.exe
SOURCES := \
	src/first_image.cpp \
	src/imple/Vec3.cpp \
	src/imple/sphere.cpp \
	src/imple/hitbale_list.cpp
HEADERS := \
	src/include/Vec3.hpp \
	src/include/Ray.hpp \
	src/include/hitable.hpp \
	src/include/sphere.hpp \
	src/include/hitable_list.hpp \
	src/include/camera.hpp \
	src/include/material.hpp

.PHONY: all
all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)
