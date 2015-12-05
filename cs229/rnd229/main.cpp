#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <stdlib.h>

using namespace std;

string file_name;
int freq_mult;
int num_channels;
int bit_res;
int sample_rate;
int num_samples;

void output_header(ostream &out);
void output_rand_data(ostream &out);
void print_info();
void print_help();

int main() {
	ofstream file;

	file_name = "rnd.cs229";
	freq_mult = 20;

	num_channels = (rand() % 7 + 1); // (1, 7) channels
	bit_res = pow(2, (rand() % 3 + 3)); // 8, 16, or 32
	sample_rate = (rand() % 4 + 1) * freq_mult; // freq_mult hz * (1, 4)
	num_samples = sample_rate * (rand() % 30 + 1); // (1, 30) seconds long

	file.open(file_name);
	output_header(file);
	output_rand_data(file);
	print_info();

	file.close();
	return 0;
}

void output_header(ostream &out) {
	out << "CS229" << endl << endl;
	out << "# Generated by sndrnd (created by Ian Malerich)" << endl << endl;

	out << "Channels " << num_channels << endl;
	out << "BitRes " << bit_res << endl;
	out << "SampleRate " << sample_rate << endl;
	out << "Samples " << num_samples << endl << endl;
}

void output_rand_data(ostream &out) {
	out << "StartData" << endl;
	auto num_values = (int)pow(2, bit_res);

	// for each sample in the file
	for (auto s = 0; s < num_samples; s++) {
		// for each channel
		for (auto c = 0; c < num_channels; c++) {
			// generate a random sample that fits within this files bit_res
			auto sample = rand() % num_values - (num_values / 2 - 1);
			out << sample;

			// do not leave extra spaces, keep things clean
			if (c != num_channels - 1) out << " ";
		}

		// done outputing all channels for this sample
		out << endl;
	}
}

void print_info() {
	cout << "File Name:\t" << file_name << endl;
	cout << "File Type:\t" << ".cs229" << endl;
	cout << "Sample Rate:\t" << sample_rate << endl;
	cout << "Bit Depth:\t" << bit_res << endl;
	cout << "Num Channels:\t" << num_channels << endl;
	cout << "Num Samples:\t" << num_samples << endl;
	cout << "Length:\t" << num_samples / (double)sample_rate << " seconds" << endl;
}

void print_help() {
}
