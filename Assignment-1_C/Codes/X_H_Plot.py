import numpy as np
import matplotlib.pyplot as plt
import soundfile as sf

#If using termux
import subprocess
import shlex

def to_complex(field):
	field = str(field)[2:]
	field = field[0 : len(field) - 1]
	return complex(field.replace('+-', '-').replace('i', 'j'))

X_k = np.loadtxt('X_FFT.dat', converters={0: to_complex}, dtype = np.complex128, delimiter = '\n')
H_k = np.loadtxt('H_FFT.dat', converters={0: to_complex}, dtype = np.complex128, delimiter = '\n')
X_k = np.fft.fftshift(X_k)
H_k = np.fft.fftshift(H_k)
n = len(X_k)


plt.subplot(2,1,1)
plt.plot(np.linspace(-np.pi,np.pi,n),abs(X_k))
plt.grid()
plt.xlabel("$\omega$")
plt.ylabel("|X(k)|")
plt.title("FFT of x[n] using in built function")

plt.subplot(2,1,2)
plt.plot(np.linspace(-np.pi,np.pi,len(H_k)),abs(H_k))
plt.grid()
plt.xlabel("$\omega$")
plt.ylabel("|H(k)|")
plt.title("FFT of h[n] using in built function")
plt.tight_layout()

#if using termux
plt.savefig('../Figures/Hk.eps')
plt.savefig('../Figures/Hk.pdf')

#subprocess.run(shlex.splilt("termux-open ../Figures/Hk.pdf"))

#else
plt.show()