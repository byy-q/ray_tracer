output/first_image.exe: src/first_image.cpp src/include/Vec3.hpp src/include/Ray.hpp output/Vec3.o 
	g++ -o output/first_image.exe src/first_image.cpp src/include/Vec3.hpp src/include/Ray.hpp 
output/Vec3.o 
	g++ -c src/imple/Vec3.cpp -o output/Vec3.o
	