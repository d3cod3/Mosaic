'''
	----------------------------------------------------------
	Mosaic | OF Visual Patching Developer Platform

	Copyright (c) 2018 Emanuele Mazza aka n3m3da

	Mosaic is distributed under the MIT License. This gives everyone the
    freedoms to use Mosaic in any context: commercial or non-commercial,
    public or private, open or closed source.

    See https://github.com/d3cod3/Mosaic for documentation
	----------------------------------------------------------


	empty.py: A Python script template for Mosaic,
	mimicking the standard OF app structure

'''

from openframeworks import *
from ofxaddons import *

class mosaicApp(object):
	def __init__(self):
		self.mouseX = 0
		self.mouseY = 0

	def update(self):
		pass

	def draw(self):
		ofBackground(0)

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
