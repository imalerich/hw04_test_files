#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>

using namespace std;

string file_name = "rnd.cs229";
int freq_mult = 20;
int min_channels = 1;
int max_channels = 7;
int min_length = 1; // seconds
int max_length = 30; // seconds

int num_channels;
int bit_res;
int sample_rate;
int num_samples;

void output_header(ostream &out);
void output_rand_data(ostream &out);
void print_info();
void print_help();

int main(int argc, char ** argv) {
	srand(time(NULL));

	// grab any arguments for generation
	static struct option long_options[] = {
		{ "help", no_argument, 0, 'h' },
		{ "output", required_argument, 0, 'o' },
		{ "freq", required_argument, 0, 'f' },
		{ "min-channels", required_argument, 0, 0 },
		{ "max-channels", required_argument, 0, 'c' },
		{ "min-length", required_argument, 0, 0 },
		{ "max-length", required_argument, 0, 'l' },
		{ 0, 0, 0, 0 }
	};

	char c = 0;
	int option_index = 0;

	while ((c = getopt_long(argc, argv, "ho:f:c:l:012", long_options, &option_index)) != -1) {
		switch(c) {
			case 0:
				switch (option_index) {
				case 3: // min-channels
					min_channels = atoi(optarg);
					break;

				case 5: // min-length
					min_length = atoi(optarg);
					break;
				}

				break;

			case 'o':
				file_name = string(optarg);
				break;

			case 'f':
				freq_mult = atoi(optarg);

			case 'c':
				max_channels = atoi(optarg);
				break;

			case 'l':
				max_length = atoi(optarg);
				break;
				
			case 'h':
				print_help();
				return 0;
		}
	}

	// if any extra arguments are found, print the help and exit
	if (argc - optind > 0) {
		print_help();
		return 1;
	}

	// create the limit values for the generated file
	num_channels = (rand() % (max_channels - min_channels + 1) + min_channels); // number of channels from (min_channels, max_channels) 
	bit_res = pow(2, (rand() % 3 + 3)); // 8, 16, or 32
	sample_rate = (rand() % 4 + 1) * freq_mult; // freq_mult hz * (1, 4)
	num_samples = sample_rate * (rand() % (max_length - min_length + 1) + min_length); // (min_length, max_length) seconds long

	// generate the file
	ofstream file;
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
	cout << "Length:\t\t" << num_samples / (double)sample_rate << " seconds" << endl;
}

void print_help() {
	cout << "Usage: rnd229 [options]" << endl;
	cout << "  -h --help\tDisplay this information" << endl;
	cout << "  -o --output\tOutput file name (default 'rnd.cs229')" << endl;
	cout << "  -f --freq\tFrequency multiplier, SampleRate will be a random value in the range (1, 4) times this value (deafault '20')" << endl;
	cout << "  --min-channels\tMinimum number of channels in the output file (default '1')" << endl;
	cout << "  -c --max-channels\tMaximum number of channels in the output file (default '7')" << endl;
	cout << "  --min-length\tMinimum length of generated sound (in seconds) (default '1')" << endl;
	cout << "  -l --max-length\tMaximum length of generated sound (in seconds) (default '30')" << endl;
	cout << "Generates a random .cs229 file within the input bounds." << endl;
	cout << "The output will be written to the specified file (rnd.cs229 if none present) and the appropriate info for 'sndinfo' will be written to the standard output." << endl;
	cout << "If no arguments are provided, this program will generate the file rnd.cs229 with (1,7) channels, with a length of (1,30) seconds." << endl;
	cout << "BitResolution will either be 8, 16, or 32 bits. Samples are generated at random to fit within that bit depth." << endl;
	cout << "This program was written by Ian Malerich for testing hw04 of cs229 at Iowa State University (Fall 2015)." << endl;
}
