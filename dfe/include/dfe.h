#pragma once

#define __USE_SQUARE_BRACKETS_FOR_ELEMENT_ACCESS_OPERATOR

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <memory>
#include <filesystem>

// Python-style print https://gist.github.com/fresky/5524148
namespace __hidden__ {
    struct print {
        bool space;
        print() : space(false) {}
        ~print() { std::cout << std::endl; }

        template <typename T>
        print& operator , (const T& t) {
            if (space) std::cout << ' ';
            else space = true;
            std::cout << t;
            return *this;
        }
    };
}
#define print __hidden__::print(),

// Python-style plotting
#include "../matplotlib-cpp/matplotlibcpp.h"
namespace plt = matplotlibcpp;

#include "AudioFile/AudioFile.h"
#include "Simple-FFT/include/simple_fft/fft_settings.h"
#include "Simple-FFT/include/simple_fft/fft.h"

// required for simple FFT library use
typedef std::vector<real_type> RealArray1D;
typedef std::vector<complex_type> ComplexArray1D;

// mimic MATLAB's linspace function
std::vector<int> generateRange(int a, int b, int c);
std::vector<float> generateRange(float a, float b, float c);

// convert butterfly MR to IR (input complex for type convenience only - assumed imag() = 0 everywhere)
RealArray1D mr2ir(ComplexArray1D &mr, size_t Nfft);

// in-place hamming windowing (adapted from https://www.phon.ucl.ac.uk/courses/spsci/dsp/window.html)
void Hamming(ComplexArray1D& iwv);

// element-wise vector multiply (adapted from https://stackoverflow.com/questions/42278819/element-wise-vector-multiplication-c-code-not-working)
ComplexArray1D vectorMultiplication(ComplexArray1D &v1, ComplexArray1D &v2);

// Routine peforms linear convolution by straight forward calculation - written by Clay S. Turner
// inputs:
//  X  array of data comprising vector #1
//  Y  array of data comprising vector #2
//  Z  pointer to place to save resulting data - needs to be len+leny - 1 long
//  lenx  # of items in vector 1
//  leny  # of items in vector 2
void LinearConvolution(double X[], double Y[], double Z[], int lenx, int leny);

// compare MRs of input, inverse and combo
void plot_dfe_mr(ComplexArray1D& avg_mr, ComplexArray1D inv_mr, ComplexArray1D combo);

// simple interpolation (adapted from https://stackoverflow.com/questions/9394867/c-implementation-of-matlab-interp1-function-linear-interpolation)
vector<float> interp1(vector<float>& x, vector<float>& y, vector<float>& x_new);

// assumes data comes from SADIE II, with their naming convention
class HRIR_set {

public:
    HRIR_set();
    ~HRIR_set();

    std::string in_dir;
    std::vector<int> azi_locs;
    std::vector<int> ele_locs;

    // getters
    size_t N() const { return _N; }
    size_t total() const { return _total; }

    // example sampling of HRIR subject data - 10 deg increments along azimuth, 15 deg spacing along elevation
    void sample_36x12();

    // loop through sampled IRs, compute power spec and accumulate - then average and root
    void calc_avg_mag(ComplexArray1D &acc_pow_l, ComplexArray1D &acc_pow_r);

    // apply FIR filter to entire HRIR dir (in stereo) and save to disk
    void apply_fir(std::string out_dir, RealArray1D& ir_l, RealArray1D& ir_r);

private:
    size_t _N;
    size_t _total;
    size_t _azi_len;
    size_t _ele_len;

};

// port of MATLAB's infamous Kirkeby regularised FIR inversion function (https://uk.mathworks.com/matlabcentral/fileexchange/19294-inverse-fir-filter)
class Kirkeby_Inverter {

public:

    // probably a neater way of initialising with parameters, but this'll do for now
    Kirkeby_Inverter(int Fs, size_t Nfft, int Noct, size_t L, int f1, int f2, float reg_in, float reg_out);
    ~Kirkeby_Inverter() {};

    // regularisation with 1/3 oct interpolated transient edges
    void reg();

    // octave smoothing
    void cmplxsmooth(ComplexArray1D H);

    // calculate inverse filter (returns inverse MR for debugging)
    ComplexArray1D calc_inverse(RealArray1D& ir, RealArray1D& inv_ir);

private:

    int _Fs, _Noct, _f1, _f2;
    size_t _Nfft, _L;
    float _reg_in, _reg_out, _f1e, _f2e;
    std::vector<float> _freq;
    ComplexArray1D _B;

};


