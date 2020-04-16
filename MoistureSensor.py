#!/usr/bin/python3
import RPi.GPIO as GPIO
import time
import paho.mqtt.publish as publish


class Moisture(object):

	host = "ec2-34-198-178-153.compute-1.amazonaws.com" #MQTT Broker IP
	port = 1883 #Unsecure MQTT port
	LED = 23	#GPIO23
	Water = 21	#GPIO21
	GPIO.setmode(GPIO.BCM)
	GPIO.setup(Water, GPIO.IN) #Set pin GPIO21 to IN
	GPIO.setup(LED, GPIO.OUT) #Set pin GPIO23 to out


	def _init_(self): #Set detection on Moisture Sensor and Call callback function
	
		GPIO.add_event_detect(self.Water, GPIO.BOTH, bouncetime=300)
		GPIO.add_event_callback(self.Water, self.callback)
		
		try:
			while True:
				time.sleep(1)
		except KeyboardInterrupt:
				print("Program shutdown") #shutdown program
		finally:
				GPIO.cleanup() 

	def callback(self,Water):           #Prints if water is detected, publishes to MQTT Broker and turns LED on/off
		if GPIO.input(Water):
			print ("NO Water Detected!")
			publish.single("water", "NO Water Detected!", hostname=self.host, port=self.port, auth ={'username':"ubuntu", 'password':"root"})
			GPIO.output(self.LED, GPIO.HIGH)
		else:
			print ("Water Detected!")
			publish.single("water", "Water Detected!", hostname=self.host, port=self.port, auth ={'username':"ubuntu", 'password':"root"})
			GPIO.output(self.LED, GPIO.LOW)

m = Moisture()
m._init_()
