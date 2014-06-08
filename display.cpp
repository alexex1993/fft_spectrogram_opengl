#include <GL/glut.h>
#include <iostream>
#include <sndfile.h>
#include <math.h>
#include <stdlib.h>
#include "fft.h"
#include "pipeline.h"
#include "display.h"

using std::cout;
using std::endl;

char * name;
unsigned int globalLogN;

void display() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(SIZE_OF_POINT); 
	glBegin(GL_POINTS); 
	char *infilename ;
	SNDFILE *infile = NULL ;
	FILE *outfile = NULL ;
	SF_INFO sfinfo ;
	//Открываем wav-файл
	infile = sf_open(/*argv [1]*/name, SFM_READ, &sfinfo);
	if(!sf_format_check(&sfinfo))
	{
		cout << "Invalid format of input file!" << endl;
		cout << "Exit." << endl;
		exit(0);
	}
	
	double FREQ;
	
	FREQ = sfinfo.samplerate;
	
	int N = pow(2, globalLogN);
	unsigned int numberOfSamples = N*sfinfo.channels;
	double *samples = new double[numberOfSamples];
	complex *complexData = new complex[numberOfSamples];
	double *window = new double[numberOfSamples];
	
	
	for (int i = 0; i < numberOfSamples; i++) window[i] = 0.5 * (1 - cos( 2 * PI * i / N));

	//Выводим данные о файле
	cout << "Samplerate = " << sfinfo.samplerate << endl;
	cout << "Channels = " << sfinfo.channels << endl;
	cout << "Numbers of a samples in the file " << sfinfo.frames << endl;
	

	
	while(sf_seek(infile, 0, SEEK_CUR) <  sfinfo.frames)
	{
		//Читаем N сэмплов
		sf_readf_double(infile, samples, N);
		
		//Применяем окно
		for (int i = 0; i < numberOfSamples; i++) complexData[i] =  window[i] *  samples[i]; /*complexData[i].m_im*/ 

		CFFT::Forward(complexData, N);


		//Цикла для задания АЧХ
		for (int i = 0; i < numberOfSamples/2 ; i++)
		{
			unsigned int currsamp = sf_seek(infile, 0, SEEK_CUR);
			double amplitude = complexData[i].amplitude()/N;
			double valueIndB = 20.0f * log10f(amplitude);
			unsigned int rr, gg, bb;
			palette_spectrum((valueIndB + 120)/100, rr, gg, bb);
			glColor3ub(rr, gg, bb);
			
			/*cout << "Hz = " << (i * FREQ / N )/2 << "Sample = (" << 
			currsamp - N << " - " << currsamp << ") Time = (" << (currsamp - N) * 1.0/FREQ << " - " << currsamp * 1.0/FREQ 
			<< "s) dB = " << valueIndB << endl;*/
		        glVertex2f((double)sf_seek(infile, 0, SEEK_CUR)/sfinfo.frames,(double)i/(N/2/sfinfo.channels));
		}
		
		
	}
	delete[] complexData;
	glEnd();
	glFlush();
}