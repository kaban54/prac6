import matplotlib.pyplot as plt

filename1 = 'output1.txt'
filename2 = 'output2.txt'
imgname = 'images/plot3.png'

data1 = open(filename1, 'r').read().splitlines()
data2 = open(filename2, 'r').read().splitlines()

xvals1 = [float (data1[i].split()[0]) for i in range(len(data1))]
yvals1 = [float (data1[i].split()[1]) for i in range(len(data1))]

xvals2 = [float (data2[i].split()[0]) for i in range(len(data2))]
yvals2 = [float (data2[i].split()[1]) for i in range(len(data2))]

plt.axis([0, 1000000, 0, 0.2])
plt.xlabel('Number of operations', color='gray')
plt.ylabel('Time', color='gray')
plt.grid(True)
plt.plot (xvals1, yvals1, 'ro')
plt.plot (xvals2, yvals2, 'bo')
plt.legend(['Операции равновероятны','Вероятность вставки больше'], loc=2)

plt.savefig(imgname)