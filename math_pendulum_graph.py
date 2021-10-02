import matplotlib.pyplot as plt
import numpy as np


def main():
    # можно брать данные из файла без использования этих жутких функций!!!
    t1, phi1, xi1, inv1 = np.loadtxt('cmake-build-debug/result1.txt', unpack=True)
    t2, phi2, xi2, inv2 = np.loadtxt('cmake-build-debug/result2.txt', unpack=True)

    fig, ((g1, g2), (g3, g4)) = plt.subplots(2, 2)

    line_width = 1

    g1.plot(t1, phi1, line_width, color='red')
    g2.plot(t1, xi1, line_width, color='red')
    g3.plot(t1, inv1, line_width, color='red')
    g4.plot(phi1, xi1, line_width, color='red')

    g1.plot(t2, phi2, line_width, color='green', alpha=0.5)
    g2.plot(t2, xi2, line_width, color='green', alpha=0.5)
    g3.plot(t2, inv2, line_width, color='green', alpha=0.5)
    g4.plot(phi2, xi2, line_width, color='green', alpha=0.5)

    plt.show()

    return


main()
