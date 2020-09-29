#include "../include/dfe.h"

int main(int argc, char* argv[])
{
    // start up hrir_set object
    HRIR_set hrir_set;
    hrir_set.in_dir = argv[1];
    hrir_set.sample_36x12();
    size_t N = hrir_set.N();
    size_t total = hrir_set.total();

    // calculate "average" magnitude responses for L and R
    ComplexArray1D avg_mag_l(N);
    ComplexArray1D avg_mag_r(N);
    hrir_set.calc_avg_mag(avg_mag_l, avg_mag_r);

    // convert MRs to IRs (ifft and rotate)
    RealArray1D avg_ir_l = mr2ir(avg_mag_l, N);
    RealArray1D avg_ir_r = mr2ir(avg_mag_r, N);

    // derive inverse IR (TODO: make into "stereo" class)
    RealArray1D inv_ir_l(N);
    RealArray1D inv_ir_r(N);
    Kirkeby_Inverter kirk_inv_l(44100, N, 3, N, 20, 20000, 15, 20);
    Kirkeby_Inverter kirk_inv_r(44100, N, 3, N, 20, 20000, 15, 20);
    kirk_inv_l.reg();
    kirk_inv_r.reg();
    ComplexArray1D inv_mag_l = kirk_inv_l.calc_inverse(avg_ir_l, inv_ir_l);
    ComplexArray1D inv_mag_r = kirk_inv_l.calc_inverse(avg_ir_r, inv_ir_r);

    // combine FRs to check for "flat" response
    ComplexArray1D combo = vectorMultiplication(avg_mag_l, inv_mag_l);

    // plot
    plot_dfe_mr(avg_mag_l, inv_mag_l, combo);

    // apply inverse filter across HRIR set
    hrir_set.apply_fir(argv[2], inv_ir_l, inv_ir_r);
}
