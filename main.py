import numpy as np
import matplotlib.pyplot as plt

_data_1 = np.fromfile("harmonic_oscillator_position.bin")
_data_2 = np.fromfile("harmonic_oscillator_velocity.bin")

print(_data_1)
plt.plot(_data_1[::10])
plt.show()
plt.plot(_data_2[::10])
plt.show()

plt.plot(_data_1[::10], _data_2[::10])

energy = 0.5 * np.power(_data_1, np.ones(_data_1.shape) * 2) + 0.5 * np.power(_data_2, np.ones(_data_1.shape) * 2)
print(energy)
print(np.average(energy))

plt.show()