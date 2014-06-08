all:
	c++ main.cpp fft.cpp pipeline.cpp display.cpp complex.cpp -o wav_spectr -lglut -lGL -lsndfile

