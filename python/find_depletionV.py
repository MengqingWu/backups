#
# author: Uwe Kraemer <>
#

import pylab
import numpy as np
import matplotlib.pyplot as plt

file_list=[("/home/weisera/afs/trackersensors/data_ld/sensor_31_CV_2", "Sensor 31"), ("/home/weisera/afs/trackersensors/data_ld/sensor_32_CV_2", "Sensor 32")
,("/home/weisera/afs/trackersensors/data_ld/sensor_33_CV_2", "Sensor 33"),("/home/weisera/afs/trackersensors/data_ld/sensor_34_CV_1", "Sensor 34"),("/home/weisera/afs/trackersensors/data_ld/sensor_35_CV_1", "Sensor 35"),("/home/weisera/afs/trackersensors/data_ld/sensor_36_CV_1", "Sensor 36"),
("/home/weisera/afs/trackersensors/data_ld/sensor_37_CV_1", "Sensor 37"),("/home/weisera/afs/trackersensors/data_ld/sensor_38_CV_1", "Sensor 38"),("/home/weisera/afs/trackersensors/data_ld/sensor_39_CV_1", "Sensor 39"),("/home/weisera/afs/trackersensors/data_ld/sensor_40_CV_1", "Sensor 40"),
("/home/weisera/afs/trackersensors/data_ld/sensor_41_CV_1", "Sensor 41"),("/home/weisera/afs/trackersensors/data_ld/sensor_42_CV_2", "Sensor 42"),("/home/weisera/afs/trackersensors/data_ld/sensor_43_CV_2", "Sensor 43"),("/home/weisera/afs/trackersensors/data_ld/sensor_44_CV_1", "Sensor 44"),
("/home/weisera/afs/trackersensors/data_ld/sensor_45_CV_1", "Sensor 45"),("/home/weisera/afs/trackersensors/data_ld/sensor_46_CV_1", "Sensor 46"),("/home/weisera/afs/trackersensors/data_ld/sensor_47_CV_1", "Sensor 47"),("/home/weisera/afs/trackersensors/data_ld/sensor_48_CV_1", "Sensor 48"),
("/home/weisera/afs/trackersensors/data_ld/sensor_49_CV_1", "Sensor 49"),("/home/weisera/afs/trackersensors/data_ld/sensor_50_CV_1", "Sensor 50"),("/home/weisera/afs/trackersensors/data_ld/sensor_51_CV_1", "Sensor 51"),("/home/weisera/afs/trackersensors/data_ld/sensor_52_CV_1", "Sensor 52"),
("/home/weisera/afs/trackersensors/data_ld/sensor_53_CV_1", "Sensor 53"),("/home/weisera/afs/trackersensors/data_ld/sensor_54_CV_1", "Sensor 54"),("/home/weisera/afs/trackersensors/data_ld/sensor_55_CV_1", "Sensor 55"),("/home/weisera/afs/trackersensors/data_ld/sensor_56_CV_1", "Sensor 56"),
("/home/weisera/afs/trackersensors/data_ld/sensor_57_CV_1", "Sensor 57"), ("/home/weisera/afs/trackersensors/data_ld/sensor_58_CV_1", "Sensor 58"),("/home/weisera/afs/trackersensors/data_ld/sensor_59_CV_1","Sensor 59")]
datalist = [ ( pylab.loadtxt(filename), label ) for filename, label in file_list ]
linestyle = ['-', '--', ':', '-.']
i = 1
stylenumber=0
depletion1 = []
depletion2 = []
depletion3 = []
number_sensors = 29


#ydata=data[:,2]

for data, label in datalist:
    ydata=data[:,2]
    xdata=data[:,0]
    
    count = 0 
    line2d = plt.plot(xdata, ydata, ls=linestyle[stylenumber], label=label,)
    x_data = line2d[0].get_xdata()
    y_data = line2d[0].get_ydata()
    
    y_data_1 = np.array(y_data, dtype=np.float)
    y_data_gradient = np.gradient(y_data_1)
    #yinterpol = np.interp(x_data, y_data_gradient)
    #print y_data_gradient

   
    #stylenumber=(i%4)
    
    y0 = -5e-12
    y1 = -3e-12
    y2 = -1e-12
    depletion1.append(np.interp(y0, y_data_gradient, x_data))
    depletion2.append(np.interp(y1, y_data_gradient, x_data))
    depletion3.append(np.interp(y2, y_data_gradient, x_data))
    #print depletion 

index = np.arange(number_sensors)
index1 = index+1 
#print index
bar_width = 0.5
opacity = 0.5
error_config = {'ecolor' : '0.3'}

fig, ax = plt.subplots()

#depl1 = plt.bar(index1- bar_width, depletion1, bar_width, alpha=opacity, color='g', error_kw = error_config, label= 'Depletion Voltage -5e-12')
depl2 = plt.bar(index1, depletion2, bar_width, alpha=opacity, color='c', error_kw = error_config, label= 'Depletion Voltage')
#depl3 = plt.bar(index1 + bar_width, depletion3, bar_width, alpha=opacity, color='r', error_kw = error_config, label= 'Depletion Voltage')

plt.xlabel('Sensors')
plt.ylabel('Voltage [V]')
plt.title('Depletion Voltage by Sensor')
plt.legend(fontsize = 10)
plt.xticks(index1 + 0.5*bar_width, ('31', '32', '33', '34', '35', '36', '37', '38', '39', '40','41', '42', '43', '44', '45', '46', '47', '48', '49', '50','51', '52', '53', '54', '55', '56', '57', '58', '59'))
#values2 = plt.bar(x, yvalues)
#plt.show()
plt.tight_layout()

Name_of_BarPlot = 'depletion_voltage.png'
Folder = "/home/weisera/afs/trackersensors/data_ld/"
print "File saved under", Folder+Name_of_BarPlot
pylab.savefig(Folder+Name_of_BarPlot, dpi = 150)


fig2, ax2 = plt.subplots()
fig2.canvas.draw()
#hist = plt.figure(2)
#plt.hist(depletion2, bins =12, align ='mid', range = (30,60))
#histogram = plt.hist(depletion2, bins =12, align ='mid', range = (30,60))
fig2.title = ("Depletion Voltage")
fig2.xlabel = ("$V_{depl} [V]$")
fig2.ylabel = ("# of Sensors")
histogram = plt.hist(depletion2, bins =12, align ='mid', range = (30,60))
#plt.axis([40,56, 0, 0.3])

Name_of_hist = 'depletion_hist.png'
Folder = "/home/weisera/afs/trackersensors/data_ld/"
print "File saved under", Folder+Name_of_hist
pylab.savefig(Folder+Name_of_hist, dpi = 150)


    
   # gradient = zip (x_data, y_data_gradient)
    #print gradient
    #for x_data, y_data_gradient in gradient:
	#if y_data_gradient > y0:
		#x_data_g = x_data
		#y_data_gradient_g = y_data_gradient
		#print x_data_g
		#if (count == 0): 
		#	dv.append(x_data_g)
		#count = count + 1
	

