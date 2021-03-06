clear all;

N = 256; % expected length of HRIR (which we'll make FFT size for convenience)
azimuth_locations = (0:10:350); % example regular sampling across azimuth (degrees)
elevation_locations = (-75:15:90); % example regular sampling across elevation (degrees)
hrir_dir = 'C:\projects\DFE\D1_HRIR_WAV\'; % location of HRIR set

% load hrirs, calculate power spectra and accumulate
addpath(hrir_dir);
acc_pow = zeros(N, 1);
total = length(azimuth_locations)*length(elevation_locations);
for az = 1:length(azimuth_locations)
    for el = 1:length(elevation_locations)
        filepath = strcat(hrir_dir, 'azi_', num2str(azimuth_locations(az)), ',0_ele_', num2str(elevation_locations(el)), ',0.wav');
        [hrir, Fs] = audioread(filepath);
        hrtf = fft(hrir, N);
        acc_pow = acc_pow + abs(hrtf).^2;
    end
end

% average and root (effectively making acc power spec --> average mag response) 
avg_mag = sqrt(acc_pow / total);

% plot
F = linspace(0, Fs - (Fs/N), N);
semilogx(F(1:N/2), 10*log10(avg_mag(1:N/2)));

% convert avg mag response to IR (zero phase)
avg_ir = circshift(real(ifft(avg_mag)), N/2);

% separate channels
avg_ir_l = avg_ir(:,1); 

% normalise?
% / max(abs(avg_ir(:,1)));

% derive inverse FIR from IR (setting phase aside for now - inverse may be unstable though)
inverse_l = invFIR('linphase', avg_ir_l, N, 3, N, [20 20000], [15 20], 1, Fs);

% QC: combine DFIR with inverse and check FR is "flat"
hold on;
inverse_tf_l = fft(inverse_l, N);
semilogx(F(1:N/2), 10*log10(abs(inverse_tf_l(1:N/2))));
flat_ir_l = conv(avg_ir_l, inverse_l, 'same');
flat_tf_l = fft(flat_ir_l, N);
semilogx(F(1:N/2), 10*log10(abs(flat_tf_l(1:N/2))));
