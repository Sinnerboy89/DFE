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
    ComplexArray1D ir_cplx(Nfft);
    bool status;
    const char* error = nullptr;

    status = simple_fft::IFFT(mr, ir_cplx, Nfft, error);

    for (auto i = 0; i < Nfft; i++) {
        ir[i] = ir_cplx[i].real();
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


ComplexArray1D vectorMultiplication(ComplexArray1D &v1, ComplexArray1D &v2)
{
    ComplexArray1D result;
    std::transform(v1.begin(), v1.end(), v2.begin(), 
                   std::back_inserter(result), std::multiplies<complex_type>());
    return result;
}

#ifdef USE_PYTHON
void plot_dfe_mr(ComplexArray1D& avg_mr, ComplexArray1D inv_mr, ComplexArray1D combo) {

    float bin = 22050.0f / 128.0f;
    std::vector<float> freq = generateRange(0.0f, bin, 22050.0f - bin);
    std::vector<float> avg_mr_real, inv_mr_real, combo_real;
    for (auto i = 0; i < 128; i++) {
        avg_mr_real.push_back(avg_mr[i].real());
        inv_mr_real.push_back(inv_mr[i].real());
        combo_real.push_back(combo[i].real());
    }

    plt::figure_size(1200, 780);
    plt::named_plot("avg", freq, avg_mr_real);
    plt::named_plot("inverse", freq, inv_mr_real);
    plt::named_plot("combo", freq, combo_real);
    plt::title("DFE");
    plt::legend();
    plt::save("./plot_dfe.png");
}
#endif // USE_PYTHON

static int findNearestNeighbourIndex(float value, std::vector<float>& x)
{
    float dist = FLT_MAX;
    int idx = -1;
    for (int i = 0; i < x.size(); ++i) {
        float newDist = value - x[i];
        if (newDist > 0 && newDist < dist) {
            dist = newDist;
            idx = i;
        }
    }

    return idx;
}

std::vector<float> interp1(std::vector<float>& x, std::vector<float>& y, std::vector<float>& x_new)
{
    std::vector<float> y_new;

    std::vector<float> dx, dy, slope, intercept;
    dx.reserve(x.size());
    dy.reserve(x.size());
    slope.reserve(x.size());
    intercept.reserve(x.size());
    for (int i = 0; i < x.size(); ++i) {
        if (i < x.size() - 1)
        {
            dx.push_back(x[i + 1] - x[i]);
            dy.push_back(y[i + 1] - y[i]);
            slope.push_back(dy[i] / dx[i]);
            intercept.push_back(y[i] - x[i] * slope[i]);
        }
        else
        {
            dx.push_back(dx[i - 1]);
            dy.push_back(dy[i - 1]);
            slope.push_back(slope[i - 1]);
            intercept.push_back(intercept[i - 1]);
        }
    }

    for (int i = 0; i < x_new.size(); ++i)
    {
        int idx = std::max(0, findNearestNeighbourIndex(x_new[i], x));
        y_new.push_back(slope[idx] * x_new[i] + intercept[idx]);

    }

    return y_new;

}

