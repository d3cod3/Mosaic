#test
import random
import urllib
from openframeworks import *
from ofxaddons import *

class mosaicApp(object):
	def __init__(self):
		self.x = 50.0
		self.y = 50.0
		self.d = 80

		self.mouseX = 0
		self.mouseY = 0

		self.fhand = urllib.urlopen('https://www.d3cod3.org/badboys.json')

		self.sender = ofxOscSender()
		self.sender.setup("127.0.0.1",57999)

	def update(self):
		self.x = ofRandom(OUTPUT_WIDTH)
		self.y = ofRandom(OUTPUT_HEIGHT)

	def draw(self):
		#ofBackground(0)

		ofSetColor(0,0,0,10)
		ofDrawRectangle(0,0,OUTPUT_WIDTH,OUTPUT_HEIGHT)

		ofSetColor(255)
		ofDrawBitmapString(self.fhand.read(),20,20)
		ofSetCircleResolution(60)


		color = ofColor(255,0,0,100)
		ofFill()
		ofSetColor(color)
		ofDrawCircle(self.mouseX,self.mouseY,self.d)

		ofNoFill()
		ofSetColor(255)
		i = 0
		h = (OUTPUT_HEIGHT* 1.0)/len(_mosaic_data_list)
		for data in _mosaic_data_list:
			randW = ofRandom(data*OUTPUT_WIDTH)
			ofDrawRectangle((OUTPUT_WIDTH/2) - (randW/2), i*h,randW, h)
			i += 1



	def mouseMoved(self, x, y):
		self.mouseX = x
		self.mouseY = y

	def mousePressed(self, x, y, button):
		pass

	def mouseDragged(self, x, y, button):
		pass

	def mouseReleased(self, x, y, button):
		pass

	def mouseScrolled(self, x, y, scrollX, scrollY):
		pass

	def keyPressed(self, key):
		pass

	def keyReleased(self, key):
		pass
