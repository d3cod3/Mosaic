--
--
--	----------------------------------------------------------
--	Mosaic | OF Visual Patching Developer Platform
--
--	Copyright (c) 2018 Emanuele Mazza aka n3m3da
--
--	Mosaic is distributed under the MIT License. This gives everyone the
--    freedoms to use Mosaic in any context: commercial or non-commercial,
--    public or private, open or closed source.
--
--    See https://github.com/d3cod3/Mosaic for documentation
--	----------------------------------------------------------
--
--
--	DrawBox.lua: This example show how to draw the box primitives and a basic use of
--	lights in a 3D environment.
--
--


-- variables for mouse interaction
mouseX = 0
mouseY = 0


ambient = of.FloatColor(0.6,1.0,1.0,1.0)
diffuse = of.FloatColor(0.8,0.6,0.0,1.0)
light = of.Light()

----------------------------------------------------
function setup()

end

----------------------------------------------------
function update()

end

----------------------------------------------------
function draw()
	of.setColor(0,0,0,12)
	of.drawRectangle(0,0,OUTPUT_WIDTH,OUTPUT_HEIGHT)

	of.pushMatrix()

    of.translate(OUTPUT_WIDTH/2,OUTPUT_HEIGHT/2,0.0)
    of.rotateXDeg(mouseY/OUTPUT_HEIGHT * 360 + of.randomuf()/3)
    of.rotateYDeg(mouseX/OUTPUT_WIDTH * 360 + of.randomuf()/3)
    of.rotateZDeg(of.getElapsedTimef())

    light:enable()
    light:setAmbientColor(ambient)
    light:setDiffuseColor(diffuse)

    of.setColor(255)
    of.noFill()
    of.setLineWidth(3)
    of.drawBox(300)

    light:disable()

    of.drawAxis(300)

    of.popMatrix()
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
