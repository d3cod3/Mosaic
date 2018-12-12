--
--
--	----------------------------------------------------------
--	Mosaic | OF Visual Patching Developer Platform
--
--	Copyright (c) 2018 Emanuele Mazza aka n3m3da
--
--	Mosaic is distributed under the MIT License. This gives everyone the
--  freedoms to use Mosaic in any context: commercial or non-commercial,
--  public or private, open or closed source.
--
--  See https://github.com/d3cod3/Mosaic for documentation
--	----------------------------------------------------------
--
--
--	ColorHsb.lua: A Lua script example for HSB/HSV model color in Mosaic
--
--


-- variables for mouse interaction (DO NOT DELETE)
mouseX = 0
mouseY = 0


c = of.Color()	--  openFrameworks color class
modulW = 0		--  horizontal configuration module
modulH = 0		--  vertical configuration module


function setup()
	modulW = OUTPUT_WIDTH/16   	-- OUTPUT_WIDTH = width of the output window
	modulH = OUTPUT_HEIGHT/6	-- OUTPUT_HEIGHT = height of the output window
	-- Mosaic does not recognize the system variables OUTPUT_WIDHT and OUTPUT_HEIGHT before the setup
end
----------------------------------------------------
function update()

end

----------------------------------------------------
function draw()
	of.background(0)
	
	j = 5  -- local variable to modulate hsb color
	for i = 0, 3 do
		c:setHsb(255,(j/5)*255,255) -- Here j modulates the saturation
		of.setColor(c.r,c.g,c.b) -- Take the values of setHsb
		of.drawRectangle(modulW*i, modulH*i, (OUTPUT_WIDTH/2)-(modulW*2*i), OUTPUT_HEIGHT-(modulH*2*i))
		c:setHsb((j/5)*255,255,255) -- Here j modulates the hue
		of.setColor(c.r,c.g,c.b)
		of.drawRectangle((OUTPUT_WIDTH/2)+modulW*i, modulH*i, (OUTPUT_WIDTH/2)-(modulW*2*i), OUTPUT_HEIGHT-(modulH*2*i))
		j = j-1  -- in each loop of the for structure, j reduces 1 its value
	end
end

----------------------------------------------------
function exit()

end


-- input callbacks

----------------------------------------------------
function keyPressed(key)

end

function keyReleased(key)

end

function mouseMoved(x,y)
	mouseX = x
	mouseY = y
end

function mouseDragged(x,y)
	mouseX = x
	mouseY = y
end

function mouseReleased(x,y)

end

function mouseScrolled(x,y)

end
