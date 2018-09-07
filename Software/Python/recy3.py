import numpy as np
import cv2
import matplotlib as plt
import os
import csv
import serial
from imutils.video import VideoStream
from pyzbar import pyzbar
from time import sleep, gmtime, strftime
import time
import imutils
from PIL.FontFile import WIDTH
import matplotlib.image as mpimg
from winsound import Beep

f1 = open ('puerto.txt','r')
puerto = f1.read()
f1.close()

f2= open ('camara.txt.','r')
camara = f2.read()
f2.close()
            
arduino = serial.Serial(puerto,115200,timeout=1)
if arduino.isOpen():
     print(arduino.name + ' abierto...')


print(" iniciando camara ")
vs = VideoStream(src=2).start()
sleep(2.0)
found = []

b = -80 # brightness
c = 100  # contrast
frame = vs.read()
th2 = imutils.resize(frame, 600)
#th2 = cv2.blur(frame,(1,1))
#th2 = cv2.addWeighted(th2, 1. + c/127., th2, 0, b-c)
th2 = cv2.cvtColor(th2, cv2.COLOR_BGR2GRAY)
barcodes = pyzbar.decode(th2)
th2 = imutils.resize(th2,600)
cv2.imshow("video", th2)

contadorpantallas = 0
frequencia = 2000
duracion = 100

data = ""
data1 = ""
tipo = ""
correcto = 0
cantidadbotellas = 0
botellasrechazadas = 0
cantidadreembolso = 0.00
ocupado = 0
entrada = ""
bloqueo = 0
pesok = 0
counter = 0
contador2 = 0;
bottomLeftCornerOfText2 = (600,365)
cv2.startWindowThread()

def decodificar():
    global counter
    global ocupado
    global correcto
    global data
    global data1
    global bloqueo
    global pesok
    global b
    global c
    

    frame = vs.read()
    th2 = imutils.resize(frame, 400)
    #th2 = cv2.blur(frame,(1,1))
    #th2 = cv2.addWeighted(th2, 1. + c/127., th2, 0, b-c)
    th2 = cv2.cvtColor(th2, cv2.COLOR_BGR2GRAY)
    barcodes = pyzbar.decode(th2)
    #th2 = imutils.resize(th2,300)
    #cv2.imshow("video", th2)
    
    
    for obj in barcodes:
        data = obj.data
        #print("Data : "+data+"\n")
        data1 = "PT"+data[:-1]
        if data != "":
            buscarAzules = open("azules.txt")
            buscarVerdes = open("verdes.txt")
            buscarCristal = open("cristal.txt")
            for line in buscarAzules:
                if data in line:
                    print("azul")
                    Beep(frequencia, duracion)
                    bloqueo = 1
                    correcto = 1
                    ocupado = 1
                    arduino.write("aa")
                    counter = 0                        
                    correcto = 0
                    return
            for line in buscarVerdes:
                if data in line:
                    Beep(frequencia, duracion)
                    print("verde")
                    bloqueo = 1
                    correcto = 1
                    ocupado = 1
                    arduino.write("av")
                    counter = 0
                    correcto = 0
                    return
            for line in buscarCristal:
                if data in line:
                    print("cristal")
                    Beep(frequencia, duracion)
                    bloqueo = 1
                    correcto = 1
                    ocupado = 1
                    arduino.write("at")
                    counter = 0                        
                    correcto = 0
                    return
      
            else:
                 correcto = 0
                              
    return
         


def main():
    global counter
    global ocupado
    global correcto
    global entrada
    global data
    global bloqueo
    global pesok
    global contador2
    while True:
         if bloqueo == 0:
              if pesok == 1:
                   decodificar()
         key = cv2.waitKey(1)
         if arduino.inWaiting() > 0:
              entrada = arduino.readline()
              print(entrada)
         if key== ord('a'): #aceptar
              entrada == "pok\n"
         if key== ord('r'): #rechazar
              entrada == "pno\n"
         if(entrada == "pok\n"):
              counter = 0
              contador2 = 0
              pesok = 1
              entrada = ""
         if(entrada == "pno\n"):
              pesok = 0
              entrada = ""
         if(entrada == "px\n"):
              pesok = 0
              entrada = ""
         if(entrada ==  "ok\n"):
              bloqueo = 0
              entrada = ""
         if key== ord('9'):
              ocupado = 1
              decodificar()
              if correcto == 1:
                   correcto = 0
              else:
                   correcto = 0
                
                          
         if key==ord('q'):
              vs.stop()
              VideoStream(src=camara).stop()
              arduino.close()
              cv2.destroyAllWindows()
              break
         counter += 1
	              

		
        
    

if __name__ =='__main__':
    main()
    

