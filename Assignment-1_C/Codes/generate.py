import soundfile as sf
import numpy as np
from scipy import signal

import subprocess
import shlex

x, fs = sf.read('Sound_Noise.wav')

n = int(2 ** np.floor(np.log2(len(x))))
f = open("x.dat", "w") 
for i in range(n):
    f.write(str(x[i]) + "\n")
f.close()