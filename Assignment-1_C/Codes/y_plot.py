import numpy as np
import matplotlib.pyplot as plt
import soundfile as sf

#If using termux
import subprocess
import shlex

yn= np.loadtxt('Y_IFFT.dat')
input_file, fs = sf.read('Sound_Noise.wav')

sf.write('Sound_diff_eq_C.wav', yn, fs)
plt.plot(yn)
plt.xlabel('$n$')
plt.ylabel('$y(n)$')
plt.grid()# minor
plt.title("IFFT of Y using the fuction written in C")

plt.tight_layout()

#if using termux
plt.savefig('../Figures/Yn_IFFT.eps')
plt.savefig('../Figures/Yn_IFFT.pdf')

#subprocess.run(shlex.splilt("termux-open ../Figures/ifft_yn.pdf"))

#else
plt.show()