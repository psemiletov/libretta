default:
#	g++ -lX11 -L/usr/X11R6/lib test01.cpp
	g++ -std=gnu++0x -lX11 -L/usr/X11R6/lib libretta_img_utils.cpp libretta_img_tga.cpp libretta_tga_img_test.cpp -o libretta_tga_img_test

