#define __USE_SQUARE_BRACKETS_FOR_ELEMENT_ACCESS_OPERATOR

#include <iostream>
#include <vector>
#include <array>

#include "AudioFile/AudioFile.h"
#include "Simple-FFT/include/simple_fft/fft_settings.h"
#include "Simple-FFT/include/simple_fft/fft.h"

// required for simple FFT library use
typedef std::vector<real_type> RealArray1D;
typedef std::vector<complex_type> ComplexArray1D;

// mimic MATLAB's linspace function
std::vector<float> generateRange(float a, float b, float c) {
    std::vector<float> array;
    while (a <= c) {
        array.push_back(a);
        a += b;
    }
    return array;
}


int main()
{
    AudioFile<double> ir;

    // baked parameters (for now)
    const size_t N = 256;
    const std::vector<float> azi_locs = generateRange(0, 10, 350);
    const std::vector<float> ele_locs = generateRange(-75, 15, 90);
    const char *hrir_dir = "C:\\projects\\DFE\\D1_HRIR_WAV\\";

    // loop through selected IRs in subject, compute power spec and accumulate
    for (auto el = 0; el < 12; el++) {
        for (auto az = 0; az < 36; az++) {
            std::string testpath = std::string("C:\\projects\\DFE\\D1_HRIR_WAV\\azi_0,0_ele_0,0.wav");
            ir.load(testpath);
            RealArray1D ir_l;
            ComplexArray1D fr_l;
            ir_l.resize(N);
            fr_l.resize(N);
            for (auto s = 0; s < N; s++) {
                ir_l.push_back(ir.samples[0][s]);
            }
            const char* error = nullptr;
            auto status = simple_fft::FFT(ir_l, fr_l, N, error);
        }
    }

    std::cin.get();
}
