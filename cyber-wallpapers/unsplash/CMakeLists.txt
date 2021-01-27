cmake_minimum_required(VERSION 3.5)
project(unsplash-wallpapers)

set(BACKGROUNDS
	unsplash-0.jpg
	unsplash-1.jpg
	unsplash-2.jpg
	unsplash-3.jpg
	unsplash-4.jpg
	unsplash-5.jpg
	unsplash-6.jpg
	unsplash-7.jpg
	unsplash-8.jpg
	unsplash-9.jpg
	unsplash-10.jpg
	unsplash-11.jpg
	unsplash-12.jpg
)

install(FILES ${BACKGROUNDS} DESTINATION /usr/share/backgrounds/cyber)
