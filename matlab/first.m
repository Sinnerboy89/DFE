clear all;

N = 256; % expected length of HRIR
azimuth_locations = (0:10:350);
elevation_locations = (-75:15:90);
hrir_dir = 'C:\projects\DFE\D1_HRIR_WAV\';

% load hrirs, calculate PSD and sum
addpath(hrir_dir);
acc_Pxx = zeros(ceil((N+1)/2), 1);
total = length(azimuth_locations)*length(elevation_locations);
for az = 1:length(azimuth_locations)
    for el = 1:length(elevation_locations)
        filepath = strcat(hrir_dir, 'azi_', num2str(azimuth_locations(az)), ',0_ele_', num2str(elevation_locations(el)), ',0.wav');
        [hrir, Fs] = audioread(filepath);
        [Pxx, F] = periodogram(hrir, [], length(hrir), Fs);
        acc_Pxx = acc_Pxx + Pxx;
    end
end

% average PSDs (divide by no. of files)
avg_Pxx = acc_Pxx / total;

% plot
% semilogx(F, 10*log10(avg_Pxx))

% obtain avg mag response from avg PSD
avg_mag = sqrt(avg_Pxx);

% convert avg mag response to IR
FR_data = zeros(1,N);
FR_data(1:(N/2)+1) = avg_mag(:, 1);
FR_data((N/2)+1:N) = fliplr(avg_mag(1:end-1, 1));
IR_data = real(ifft(FR_data));

% derive inverse FIR from IR
inverse_fir = invFIR('linphase', IR_data, 512, 0, 256, [20 20000], [20 -6], 0);

% plot
plot(inverse_fir);