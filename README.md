# rpi_autocorrelator

The results of a research project in which 2 Raspberry Pi (model B, original release) mini computer is used to collect a time series signal and perform an autocorrelation. 
Code is presented AS IS for those interested in lowering expenses in DCS or other systems which require a correlator device.

The RPi autocorrelator consists of to Raspberry Pi computers. RPi1 runs a "bare metal" custom operating system and is responsible for collecting the data and transferring to RPi2, which is responsible for receiving and storing the time series. 

A bare metal operating system is used on RPi1 because it results in a stable signal. Other modern operating systems do not allow for a long uninterupted stream of collections and a constant sample rate. The actual autocorrelation implementation is not included, but it is very straightforward. If the time series is stored in the vector "I[t]", the autocorrelation "g[tau]" is: g[tau] = IFFT( FFT(I[t]) FFT(I[t])* ).

1) The electrical connections must be as follows:
   RPi1 ground connected to common ground
   RPi2 ground connected to common ground
   RPi2 GPIO 17 connected to signal
   RPi1 GPIO 22 connected to RPi2 GPIO 22
   RPi1 GPIO 23 connected to RPi2 GPIO 23
   RPi1 GPIO 24 connected to RPi2 GPIO 24
   
2) The operating system for RPi2 must be compiled and installed using standard methods. See tutorial here: http://www.valvers.com/open-software/raspberry-pi/step01-bare-metal-programming-in-cpt1/

3) Compile and run "read_signal" on RPi2. This will send a signal to RPi1 to begin collection and transfer. This can take some time. The final result will be printed to the console of RPi2.

Further details can be found here:

http://www.mdpi.com/1424-8220/15/8/19709

Whenever this code is used, please cite this work as

Tivnan, M.; Gurjar, R.; Wolf, D.E.; Vishwanath, K.	High Frequency Sampling of TTL Pulses on a Raspberry Pi for Diffuse Correlation Spectroscopy Applications. Sensors 2015, 15, 19709-19722.

Questions or comments can be submitted on github or via email at tivnan.m@husky.neu.edu


