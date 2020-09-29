#include "../include/dfe.h"

HRIR_set::HRIR_set()
{
	in_dir = "";
	_total = 0;
	_N = 0;
    _azi_len = 0;
    _ele_len = 0;
}

HRIR_set::~HRIR_set()
{}

void HRIR_set::sample_36x12() {

	azi_locs = generateRange(0, 10, 350);
	ele_locs = generateRange(-75, 15, 90);
    _azi_len = azi_locs.size();
    _ele_len = ele_locs.size();
	_total = _azi_len * _ele_len;
	_N = 256; // SADIE II test input has this TODO: determine N from example loaded IR
}

void HRIR_set::calc_avg_mag(ComplexArray1D &avg_mag_l, ComplexArray1D &avg_mag_r) {

    if (in_dir.empty()) {
        std::perror("Please set HRIR.dir before running calc_avg_mag()");
    }

    if (avg_mag_l.size() != _N || avg_mag_r.size() != _N) {
        std::perror("acc_pow vectors have incorrect length");
    }

    ComplexArray1D in_l(_N), in_r(_N);
    AudioFile<real_type> stereo_ir;
    const char* error = nullptr;
    std::string ir_path;
    bool status_l, status_r;

    // calculate power spectra and accumulate (variable naming readability slightly sacrificed for in-place stack recycling!)
    for (auto el = 0; el < _ele_len; el++) {
        for (auto az = 0; az < _azi_len; az++) {
            ir_path = in_dir + "azi_" + std::to_string(azi_locs[az]) + ",0_ele_" + std::to_string(ele_locs[el]) + ",0.wav";
            stereo_ir.load(ir_path);
            for (auto i = 0; i < _N; i++) {
                in_l[i] = stereo_ir.samples[0][i];
                in_r[i] = stereo_ir.samples[1][i];
            }

            // TODO: handle any FFT failures
            status_l = simple_fft::FFT(in_l, _N, error);
            status_r = simple_fft::FFT(in_r, _N, error);

            for (auto i = 0; i < _N; i++) {
                avg_mag_l[i] += std::pow(std::abs(in_l[i]), 2);
                avg_mag_r[i] += std::pow(std::abs(in_r[i]), 2);
            }
        }
    }

    // average and root, giving us "average" mag response (MR)
    for (auto i = 0; i < _N; i++) {
        avg_mag_l[i] = std::sqrt((avg_mag_l[i].real() / _total));
        avg_mag_r[i] = std::sqrt((avg_mag_r[i].real() / _total));
    }

}

void HRIR_set::apply_fir(std::string out_dir, RealArray1D &ir_l, RealArray1D &ir_r) {

    AudioFile<real_type> input_ir, output_ir;

    output_ir.setAudioBufferSize(2, (int)_N);
    output_ir.setBitDepth(16);
    output_ir.setSampleRate(44100);

    for (const auto& entry : std::filesystem::directory_iterator(in_dir)) {
        input_ir.load(entry.path().string());

        // simple convolution
        LinearConvolution(&input_ir.samples[0][0], &ir_l[0], &output_ir.samples[0][0], (int)_N, (int)_N);
        LinearConvolution(&input_ir.samples[1][0], &ir_r[0], &output_ir.samples[1][0], (int)_N, (int)_N);

        // save to output dir
        output_ir.save(out_dir + entry.path().filename().string());
        print entry.path().filename().string();
    }
        
        
}