# DFE

Coding challenge involving Diffuse Field Equalisation of HRTF databases:

"When recording an HRTF Set we use speakers and in-ear microphones in an anechoic chamber. These have spectral characteristics that we would like to remove from the HRTF Set. An HRTF Set is 2 collections (Left and Right) of HRTFs distributed in a sphere around the listener. For simplicity, assume each HRTF is a 512 bin array of complex numbers describing magnitude (real) and phase (imaginary). In C or C++ create functionality to remove the common spectral characteristics of the HRTF set, hence removing the spectral characteristics of the recording apparatus. Imagine this code would be submitted for review and used within a publicly available HRTF post-processing chain. This process is commonly known as diffuse field equalisation."

# Usage
`dfe.exe {input_dir} {output_dir}`

WARNING: Depending on how many IR wav files are in your input directory, this may well completely lock up your disk I/O (even my SSD started to sweat a bit when testing with the Neumann set from SADIE II).

# Developer Notes

## Building from Source
Open solution in VS 2019 and build.

## Commentary
Performance? Footprint? Readability? Features? Compatibility?

## Third-party Dependencies
AudioFile: https://github.com/adamstark/AudioFile Handy little WAV read/write library, this had exactly what I needed and nothing more to deal with HRIR I/O (at least, in the SADIE II database).

SimpleFFT: https://github.com/d1vanov/Simple-FFT Could easily be replaced by your favourite optimised FFT library (FFTW, FFTS, KISS_FFT etc.) but all I wanted was a simple header-only library for readability and minimal boilerplate.

matplotlib-cpp: https://github.com/lava/matplotlib-cpp "Welcome to matplotlib-cpp, possibly the simplest C++ plotting library. It is built to resemble the plotting API used by Matlab and matplotlib." - toots its own horn a bit, as it required a bit of hacking to get going in VS 2019 - but lets me go into Python prototyping mode a little more with its mirroring of matplotlib.pyplot module (one of the best scientific plotting libraries available).

## To-Do

## Queries
* I can understand for demonstration/exercise purposes, but apart from that, why C++? This feels like a server-client type of application, with no real-time constraints or deadlines, no CPU budgets - if placed within an HRTF post-processing chain, likely scenario is within a device where the measurements occur, which will always be the timing bottleneck. Python, Java, .NET, even MATLAB feels more appropriate.

## References
McKenzie, Thomas, Damian Murphy, and Gavin Kearney. "Diffuse-field equalisation of first-order Ambisonics." Proceedings of the 20th International Conference on Digital Audio Effects (DAFx), Edinburgh, UK. 2017.
