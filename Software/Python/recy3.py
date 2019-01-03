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


# abrimos el archivos de configuracion de puerto serie y camara
f1 = open ('puerto.txt','r')
puerto = f1.read()
f1.close()

f2= open ('camara.txt.','r')
camara = f2.read()
f2.close()

#habilitamos puerto serie arduino
arduino = serial.Serial(puerto,115200,timeout=1)
if arduino.isOpen():
     print(arduino.name + ' abierto...')

#iniciamos camara
print(" iniciando camara ")
vs = VideoStream(src=int(camara)).start()
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


frecuencia = 2000
duracion = 100

data = "" # alamacena los datos de los codigos leidos 
data1 = "" # datos de codigos formateados
entrada = "" # buffer de lectura del puerto serie
bloqueo = 0 # bloquea ciertas partes del programa cuando se estan leyendo los codigos de barra.
pesok = 0 #  si el peso es correcto se pone en 1

def decodificar():  # decodifica los codigos de barra y compara con los alamcenados en los archivos
    
   
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
                if data in line:#si el codigo es correcto acepta la botella
                    print("azul")
                    Beep(frecuencia, duracion)
                    bloqueo = 1
                    arduino.write("aa")
                    return
	
            for line in buscarVerdes:
                if data in line:#si el codigo es correcto acepta la botella
                    Beep(frecuencia, duracion)
                    print("verde")
                    bloqueo = 1
                    arduino.write("av")
                    return
	
            for line in buscarCristal:
                if data in line: #si el codigo es correcto acepta la botella
                    print("cristal")
                    Beep(frecuencia, duracion)
                    bloqueo = 1
                    arduino.write("at")
                    return
      
            
                              
    return
         


def main(): 
    
    global ocupado
    global entrada
    global data
    global bloqueo
    global pesok
    
    while True: #bucle principal, lee el puerto serie desde arduino
		#o espera a que se presione alguna tecla
         if bloqueo == 0:
              if pesok == 1:
                   decodificar()
			
         key = cv2.waitKey(1)
         if arduino.inWaiting() > 0:
              entrada = arduino.readline()
              print(entrada)
         
         if(entrada == "pok\n"): #peso correcto
              pesok = 1
              entrada = ""
         if(entrada == "pno\n"): #peso incorrecto
              pesok = 0
              entrada = ""
         if(entrada == "px\n"):#botella rechazada
              pesok = 0
              entrada = ""
         if(entrada ==  "ok\n"): #Botella almacenada con exito
              bloqueo = 0
              entrada = ""
		
                  
                          
         if key==ord('q'):
              vs.stop()
              VideoStream(src=camara).stop()
              arduino.close()
              cv2.destroyAllWindows()
              break
         
	              

		
        
    

if __name__ =='__main__':
    main()

