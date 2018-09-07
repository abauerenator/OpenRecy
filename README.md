# OpenRecy

![modulo partes principales](https://user-images.githubusercontent.com/732609/45230758-495ad080-b2a0-11e8-9006-b90b9770b76c.png)



Modulo de reconocimiento de envases descartables basado en Arduino, python y openCV.

Este modulo es capaz de leer los codigos de barra en los envases y seprar estos por color o por tipo, por medio de una camara y openCV. 

Cuenta con un mecanismo de transporte para poder ingresar las botellas o envases al una cinta transportadora interna y en ella unas compuertas, dirigen cada envase a un contenedor diferente. 

El objetivo de este proyecto es crear una maquina de venta en reversa o maquina expendedora en reversa, (RVM) para la recuperacion de envases descartables y reciclables como botellas de pet, latitas de aluminio u otros envases. 

El funcionamiento se basa en un script en python que se encarga de la deteccion de los codigos de barra que puede correr tanto en un raspberry pi, o un pc. Para la lectura de los sensores y el control de motores y servos usamos arduino uno. 

Todas las partes del modulo fueron diseñadas para ser cortadas con router cnc, plasma, o laser y otras se pueden fabricar por medio de impresion 3d. 

Los objetivos mas importantes son que se pueda fabricar con partes economicas y faciles de conseguir, otra meta importante es que sea de bajo consumo energetico, y de un tamaño reducido. 

https://www.texolab.net
