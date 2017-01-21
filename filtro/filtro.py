#Requisitos instlar OpenCV y Numpy

import cv2
import numpy as np

#Descriptor de una imagen usando la media de colores y desvicación estándar

archivon = open("nombres.txt","r+") #En este archivo se guardan los nombres de las imagenes
archivov = open("vectores.txt","r+") #Aquí se guardan los vectores de las imagenes, cada linea es una imagen

abrir = "IMG/IMG ("
cerrar = ").jpg"
n = 258 # si son 250 imagenes n = 251
for i in range(1,n): 
	nombre = abrir + str(i) + cerrar
	image = cv2.imread(nombre)
	(means, stds) = cv2.meanStdDev(image)
	stats = np.concatenate([means,stds]).flatten()
	archivon.write(nombre + '\n')
	cadena = str(stats[0])+" "+str(stats[1])+" "+str(stats[2])+" "+str(stats[3])+" "+str(stats[4])+" "+str(stats[5]) 
	archivov.write(cadena+ '\n')
archivov.close
archivon.close

#Si ven por conveniente multiplicar los elementos de los vectores
#por 10000000000 porque tiene esta forma 0.197381714357 sería mejor 