#include "../include/dfe.h"

constexpr auto _PI = 3.1415;

std::vector<int> generateRange(int a, int b, int c) {
    std::vector<int> array;
    while (a <= c) {
        array.push_back(a);
        a += b;
    }
    return array;
}

std::vector<float> generateRange(float a, float b, float c) {
    std::vector<float> array;
    while (a <= c) {
        array.push_back(a);
        a += b;
    }
    return array;
}

RealArray1D mr2ir(ComplexArray1D &mr, size_t Nfft) {
    
    RealArray1D ir(Nfft);
    bool status;
    const char* error = nullptr;

    status = simple_fft::IFFT(mr, mr, Nfft, error);

    for (auto i = 0; i < Nfft; i++) {
        ir[i] = mr[i].real();
    }

    // circshift in MATLAB speak
    std::rotate(ir.begin(), ir.begin() + (Nfft / 2), ir.end());

    return ir;

}

void Hamming(ComplexArray1D &ir)
{
    double omega = 2.0 * _PI / (ir.size());
    for (int i = 0; i < ir.size(); i++)
        ir[i] = (0.54 - 0.46 * std::cos(omega * (i))) * ir[i].real();
}

void LinearConvolution(double X[], double Y[], double Z[], int lenx, int leny)
{
    double* zptr, s, * xp, * yp;
    int lenz;
    int i, n, n_lo, n_hi;

    lenz = lenx + leny - 1;
    zptr = Z;

    for (i = 0; i < lenz; i++) {
        s = 0.0;
        n_lo = 0 > (i - leny + 1) ? 0 : i - leny + 1;
        n_hi = lenx - 1 < i ? lenx - 1 : i;
        xp = X + n_lo;
        yp = Y + i - n_lo;
        for (n = n_lo; n <= n_hi; n++) {
            s += *xp * *yp;
            xp++;
            yp--;
        }
        *zptr = s;
        zptr++;
    }
}

