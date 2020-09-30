# DFE

Coding challenge involving Diffuse Field Equalisation of HRTF databases (description below).

"When recording an HRTF Set we use speakers and in-ear microphones in an anechoic chamber. These have spectral characteristics that we would like to remove from the HRTF Set. An HRTF Set is 2 collections (Left and Right) of HRTFs distributed in a sphere around the listener. For simplicity, assume each HRTF is a 512 bin array of complex numbers describing magnitude (real) and phase (imaginary). In C or C++ create functionality to remove the common spectral characteristics of the HRTF set, hence removing the spectral characteristics of the recording apparatus. Imagine this code would be submitted for review and used within a publicly available HRTF post-processing chain. This process is commonly known as diffuse field equalisation."

![Plot](plot_dfe.png)

# Usage
`dfe.exe {input_dir} {output_dir}`

WARNING: Depending on how many IR wav files are in your input directory, this may well completely lock up your disk I/O (even my SSD started to sweat a bit when testing with the Neumann set from SADIE II).

WARNING: This hasn't been tested on another machine yet, but my guess is that it's going to look for Python 3 with numpy and matplotlib packages, and crash if it doesn't find them. Puzzlingly these are required for plotting only, but a memory-related bug means that the main routine is now somehow dependent on them completely!

# Developer Notes

## Building from Source

### Requirements
* Visual Studio 2019 (may work on older versions, but not tested)
* Python 3 (for matplotlib-cpp)
* numpy python package (open a command window and enter `pip install numpy` - precede this with `{python_exe_path} -m` if not already in your $PATH)
* matplotlib python package

Open solution in VS 2019. Check that your Python and numpy core include paths are in Additional Include Directories and correct (mine is `C:\Python38\include`, `C:\Python38\Lib\site-packages\numpy\core\include`), along with library path for linker in Additional Library Directories (mine is `C:\Python38\libs`) and build in Release (Debug will fail as both Python and numpy package need to be compiled in Debug, which you're not gonna do). Any compiler warnings are only expected to originate from matplotlib-cpp library.

## Comments
After digesting Tom Mckenzie's paper and doing a little background research, I sketched out a prototype routine in MATLAB before porting to C++, focusing on core functionality and intended features/upgrades along the way. I avoided reinventing the wheel where possible, mindful that this is an exercise with HRTF processing, DSP and prototyping in mind. I included libraries as and when I needed them, usually finding what I needed on GitHub, and where I felt time would be better spent at a "higher level" (for instance, I didn't spend a week writing my own optimised FFT library). Whilst the C++ source builds, runs and appears to work as intended (as of 29/09/20) it's still very much a WIP, with various major features/improvements/ideas listed in the TODO list below. 

## Third-party Dependencies
AudioFile: https://github.com/adamstark/AudioFile Handy little WAV read/write library, this had exactly what I needed and nothing more to deal with HRIR I/O (at least, in the SADIE II database).

SimpleFFT: https://github.com/d1vanov/Simple-FFT Could easily be replaced by your favourite optimised FFT library (FFTW, FFTS, KISS_FFT etc.) but all I wanted was a simple header-only library for readability and minimal boilerplate.

matplotlib-cpp: https://github.com/lava/matplotlib-cpp "Welcome to matplotlib-cpp, possibly the simplest C++ plotting library. It is built to resemble the plotting API used by Matlab and matplotlib." - toots its own horn a bit, as it required a bit of hacking to get going in VS 2019 - but lets me go into Python prototyping mode a little more with its mirroring of matplotlib.pyplot module (one of the best scientific plotting libraries available).

## To-Do
* HRIRs can be reasonably assumed to be minimum-phase in nature - use this fact to derive companion all-pass filters/group delays when processing input IRs (retaining ITDs), also guaranteeing DFE filter is always stable
* Add support for irregular spatial sampling (e.g. from popular ambisonic loudspeaker configurations - requires spatial weighting to "interpolate" onto sphere)
* finish octave smoothing routine of inverse filter for reduced "extreme" gains and cuts
* SADIE II also includes headphone IRs - add this into the processing chain as a similar inversion routine (similar to Mckenzie et. al) to further reduce recording apparatus influence on data
* Throw some popular Ambisonic loudspeaker configurations into the mix and use DFE to remove their influence on reproduction too
* Support HRTF databases other than SADIE II (CIPIC, LISTEN etc.)
* Determine FFT size and IR length from input directory
* Consider disk I/O vs. heap allocation tradeoffs if performance becomes a priority

## References
McKenzie, Thomas, Damian Murphy, and Gavin Kearney. "Diffuse-field equalisation of first-order Ambisonics." Proceedings of the 20th International Conference on Digital Audio Effects (DAFx), Edinburgh, UK. 2017.
