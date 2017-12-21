#
# author: Uwe Kraemer <>
#

import pylab
import numpy as np
import matplotlib.pyplot as plt


file_list=[("/home/weisera/afs/trackersensors/data_ld/sensor_31_IV_2", "Sensor 31"), ("/home/weisera/afs/trackersensors/data_ld/sensor_32_IV_2", "Sensor 32")
,("/home/weisera/afs/trackersensors/data_ld/sensor_33_IV_2", "Sensor 33"),("/home/weisera/afs/trackersensors/data_ld/sensor_34_IV_1", "Sensor 34"),("/home/weisera/afs/trackersensors/data_ld/sensor_35_IV_1", "Sensor 35"),("/home/weisera/afs/trackersensors/data_ld/sensor_36_IV_1", "Sensor 36"),
("/home/weisera/afs/trackersensors/data_ld/sensor_37_IV_1", "Sensor 37"),("/home/weisera/afs/trackersensors/data_ld/sensor_38_IV_1", "Sensor 38"),("/home/weisera/afs/trackersensors/data_ld/sensor_39_IV_1", "Sensor 39"),("/home/weisera/afs/trackersensors/data_ld/sensor_40_IV_1", "Sensor 40"),
("/home/weisera/afs/trackersensors/data_ld/sensor_41_IV_1", "Sensor 41"),("/home/weisera/afs/trackersensors/data_ld/sensor_42_IV_2", "Sensor 42"),("/home/weisera/afs/trackersensors/data_ld/sensor_43_IV_2", "Sensor 43"),("/home/weisera/afs/trackersensors/data_ld/sensor_44_IV_1", "Sensor 44"),
("/home/weisera/afs/trackersensors/data_ld/sensor_45_IV_1", "Sensor 45"),("/home/weisera/afs/trackersensors/data_ld/sensor_46_IV_1", "Sensor 46"),("/home/weisera/afs/trackersensors/data_ld/sensor_47_IV_1", "Sensor 47"),("/home/weisera/afs/trackersensors/data_ld/sensor_48_IV_1", "Sensor 48"),
("/home/weisera/afs/trackersensors/data_ld/sensor_49_IV_1", "Sensor 49"),("/home/weisera/afs/trackersensors/data_ld/sensor_50_IV_1", "Sensor 50"),("/home/weisera/afs/trackersensors/data_ld/sensor_51_IV_1", "Sensor 51"),("/home/weisera/afs/trackersensors/data_ld/sensor_52_IV_1", "Sensor 52"),
("/home/weisera/afs/trackersensors/data_ld/sensor_53_IV_1", "Sensor 53"),("/home/weisera/afs/trackersensors/data_ld/sensor_54_IV_1", "Sensor 54"),("/home/weisera/afs/trackersensors/data_ld/sensor_55_IV_1", "Sensor 55"),("/home/weisera/afs/trackersensors/data_ld/sensor_56_IV_1", "Sensor 56"),
("/home/weisera/afs/trackersensors/data_ld/sensor_57_IV_1", "Sensor 57"), ("/home/weisera/afs/trackersensors/data_ld/sensor_58_IV_1", "Sensor 58"),("/home/weisera/afs/trackersensors/data_ld/sensor_59_IV_1", "Sensor 59")]
datalist = [ ( pylab.loadtxt(filename), label ) for filename, label in file_list ]
linestyle = ['-', '--', ':', '-.']
i = 1
stylenumber=0
count = 0
yvalues200 = []
yvalues100 = []
yvalues50 = []

for data, label in datalist:
    
    xdata=data[:,0]
    ydata=data[:,3]
    
    plt.figure(0)
    line2d = plt.plot(xdata, ydata, ls=linestyle[stylenumber], label=label,)
    #fig1 = plt.figure()
    #line2d = fig1.add_subplot(111)
    #line2d.plot(xdata, ydata, ls=linestyle[stylenumber], label=label,)
    i=i+1
    stylenumber=(i%4)
    
    xvalues = line2d[0].get_xdata()
    y_data = line2d[0].get_ydata()
    yvalues200.append(np.interp(200, xvalues, y_data))
    yvalues100.append(np.interp(100, xvalues, y_data))
    yvalues50.append(np.interp(50, xvalues, y_data))
    #yvalues = yvalues[idx]
    
    #np.histogram() 
    #xy = line2d[0].get_xydata()
    #xy[200]
    
    count = count +1
    #print [200, yvalues]
 
    

    
    
   
    
plt.legend(loc="lower right", fontsize = 9, ncol=4)
plt.title("IV - Sensors")
plt.xlabel("V [V]")
plt.ylabel("I [A]")
number_sensors = 29

Name_of_File = 'IV_all.png'
Folder = "/home/weisera/afs/trackersensors/data_ld/"
print "File saved under", Folder+Name_of_File
pylab.savefig(Folder+Name_of_File, dpi = 150)

#print yvalues
#label in datalist:
index = np.arange(number_sensors)
index1 = index+1 
print index
bar_width = 0.25
opacity = 0.4
error_config = {'ecolor' : '0.3'}

fig, ax = plt.subplots()

volt50 = plt.bar(index1 - bar_width, yvalues50, bar_width, alpha=opacity, color='g', error_kw = error_config, label= '50V')
volt100 = plt.bar(index1, yvalues100, bar_width, alpha=opacity,error_kw = error_config, color='b', label= '100V')
volt200 = plt.bar(index1 + bar_width, yvalues200, bar_width, alpha=opacity, color='r', error_kw = error_config, label= '200V')

plt.xlabel('Sensors')
plt.ylabel('Current [A]')
plt.title('Current by Sensor and Voltage')
plt.legend(fontsize = 10)
plt.xticks(index1 + 0.5*bar_width, ('31', '32', '33', '34', '35', '36', '37', '38', '39', '40','41', '42', '43', '44', '45', '46', '47', '48', '49', '50','51', '52', '53', '54', '55', '56', '57', '58', '59'))
#values2 = plt.bar(x, yvalues)
#plt.show()
plt.tight_layout()

Name_of_BarPlot = '100-200-50_bar_plot.png'
#Folder = "/home/weisera/afs/trackersensors/data_ld/"
print "File saved under", Folder+Name_of_BarPlot
pylab.savefig(Folder+Name_of_BarPlot, dpi = 150)

#for data, label in datalist: 
   # xdata=data[:,0]
    #ydata=data[:,3]
    
    
#xvalues = line2d[0].get_xdata()
    #yvalues = line2d[0].get_ydata()
    ##idx = np.where(xvalues==xvalues[-2])
    #yvalues[idx] 
    
    #t=[50,100,200,300]
    #ynew = interp_func(t)
#print ynew
