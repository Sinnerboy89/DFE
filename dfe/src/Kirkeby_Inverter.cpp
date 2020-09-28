#include "../include/dfe.h"

Kirkeby_Inverter::Kirkeby_Inverter(int Fs, size_t Nfft, int Noct, size_t L, int f1, int f2, float reg_in, float reg_out) {

    // set parameters
    _Fs = Fs;
    _Nfft = Nfft;
    _Noct = Noct;
    _L = L;
    _f1 = f1;
    _f2 = f2;
    _reg_in = reg_in;
    _reg_out = reg_out;

    // calculate 1/3 octave edges of regularisation
    _freq = generateRange(0.0f, (float)_Fs / ((float)_Nfft - 1.0f), (float)_Fs / 2.0f);
    _f1e = _f1 - (_f1 / 3.0f);
    _f2e = _f2 + (_f2 / 3.0f);
    if (_f2e > _freq.back()) {
        _f2e = (float)_f2 + 1.0f;
    }
}

void Kirkeby_Inverter::reg() {

    float interp_x[] = { 0.0f, _f1e, (float)_f1, (float)_f2, _f2e, _freq.back() };
    float interp_y[] = { _reg_out, _reg_out, _reg_in, _reg_in, _reg_out, _reg_out };
    float* freq_ptr = &_freq[0];
    CubicSpline interpolator;
    interpolator.Initialize(interp_x, interp_y, 6);
    _B.resize(_freq.size());
    for (auto i = 0; i < _B.size(); i++) {
        _B[i] = interpolator.Interpolate(_freq[i]);
        _B[i] = std::pow(10.0f, -_B[i].real() / 20.0f); // from dB to linear
    }
    ComplexArray1D B_copy(_Nfft / 2);
    simple_fft::copy_array::copyArray(_B, B_copy, _Nfft / 2);
    for (auto i = 0; i < _Nfft / 2; i++) {
        complex_type b = B_copy[(_Nfft / 2) - i - 1];
        _B.push_back(b); // butterfly upto Fs to simplify IFFT
    }
    const char* error = nullptr;
    auto status = simple_fft::IFFT(_B, _Nfft, error);
    std::rotate(_B.begin(), _B.begin() + (_Nfft / 2), _B.end());
    Hamming(_B);
    status = simple_fft::FFT(_B, _B.size(), error);

}

void Kirkeby_Inverter::cmplxsmooth(ComplexArray1D H) {
    
    int i = 0;
    float Fs = 96000;
    std::vector<float> freq = generateRange(0.0f, Fs / (H.size() - 1), Fs / 2);
    int Noct = _Noct * 4;

    ComplexArray1D H2(H.size() / 2);
    for (i = 0; i < H.size() / 2; i++) {
        H2[i] = H[i];
    }

    // octave centre freqs
    float f1 = 1.0f;
    std::vector<float> fc;
    while (f1 < 48000.0f) {
        f1 *= std::pow(10.0f, (3.0f / (10.0f * (float)Noct)));
        i++;
        fc.push_back(f1);
    }

    // octave edge freqs
    std::vector<float> fe;
    for (i = 0; i < fc.size(); i++) {
        f1 = std::pow(10.0f, (3.0f / (20.0f * (float)Noct))) * fc[i];
        fe.push_back(f1);
    }

    // find nearest freq edges (TODO: do)
    //float fe_m, p, m, fe_p = 0, fe_0 = 0;
    //for (i = 0; i < fe.size(); i++) {
    //    for (auto j = 0; j < freq.size(); j++) {
    //        if (freq[j] == fe[i]) {
    //            fe_0 = freq[j];
    //        }
    //        else if (freq[j] > fe[i]) {
    //            fe_p = freq[j];
    //        }
    //    }
    //    for (auto j = freq.size() - 1; j >= 0; j--) {
    //        if (freq[j] < fe[i]) {
    //            fe_m = freq[j];
    //        }
    //    }
    //    if (fe_0) {
    //        fe[i] = fe_0;
    //    }
    //    else {
    //        p = fe_p - fe[i];
    //        m = fe[i] - fe_m;
    //        if (p < m) {
    //            fe[i] = fe_p;
    //        }
    //        else {
    //            fe[i] = fe_m;
    //        }
    //    }
    //}

    // to be continued...

}

void Kirkeby_Inverter::calc_inverse(RealArray1D& ir, RealArray1D& inv_ir) {

    const char* error = nullptr;

    ComplexArray1D inv_cplx(_Nfft);
    auto status = simple_fft::FFT(ir, inv_cplx, _Nfft, error);
    for (auto i = 0; i < _Nfft; i++) {
        inv_cplx[i] = std::abs(inv_cplx[i]);
    }

    // TODO: fractional octave smoothing
    cmplxsmooth(inv_cplx);

    // calculate regulated spectral inverse
    for (auto i = 0; i < _Nfft; i++) {
        inv_cplx[i] = std::conj(inv_cplx[i]) / ((std::conj(inv_cplx[i]) * inv_cplx[i]) + (std::conj(_B[i]) * _B[i]));
    }
    status = simple_fft::IFFT(inv_cplx, _Nfft, error);
    std::rotate(inv_cplx.begin(), inv_cplx.begin() + (_Nfft / 2), inv_cplx.end());

    for (auto i = 0; i < _Nfft; i++) {
        inv_ir[i] = inv_cplx[i].real();
    }
}