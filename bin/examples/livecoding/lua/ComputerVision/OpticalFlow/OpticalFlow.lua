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
--	OpticalFlow.lua: Example receiving vector data from Mosaic "optical flow" object
--
--	you can try running this script in patch example: examples/visualprogramming/ComputerVision/OpticalFlow.xml
--


-- variables for mouse interaction
mouseX = 0
mouseY = 0

-- _mosaic_data_inlet is the name of the lua table storing data incoming from a Mosaic patch
-- a vector<float> is automatically converted to a lua table, where the index starts from 1, NOT 0
-- so the first position of your table will be accessed like this: _mosaic_data_inlet[1]

tableSize = 0

-- flow variables

-- flow vector from "optical flow" Mosaic object is constructed as follows:
--
-- REMEMBER, A LUA TABLE START INDEX IS 1, NOT 0 !!!
--
-- [1] -> number of rows of flow matrix
-- [2] -> number of cols of flow matrix
-- [3 - 3 + ()(cols*rows / 10) * 4)] -> flow lines


----------------------------------------------------
function setup()


end

----------------------------------------------------
function update()
	----------------------------------------- RECEIVING vector<float> from MOSAIC PATCH
	-- avoid null readings
	if next(_mosaic_data_inlet) == nil then
		return
	end
	-----------------------------------------


end

----------------------------------------------------
function draw()
	of.setColor(0,0,0,10)
	of.drawRectangle(0,0,OUTPUT_WIDTH,OUTPUT_HEIGHT)
	--of.background(0,0,0)
	of.setCircleResolution(50)

	----------------------------------------- RECEIVING vector<float> from MOSAIC PATCH
	-- avoid null readings
	if next(_mosaic_data_inlet) == nil then
		return
	end

	-- get _mosaic_data_inlet size
	tableSize = 0
	for k,v in pairs(_mosaic_data_inlet) do
		tableSize = tableSize + 1
	end
	-----------------------------------------


	----------------------------------------- Drawing convex hulls from contours
	of.setLineWidth(1)
	of.fill()
	of.setColor(255,255,20)

	rows = _mosaic_data_inlet[1]
	cols = _mosaic_data_inlet[2]

	flowSize = (rows*cols)/10 * 4

	of.pushMatrix()
	of.scale(OUTPUT_WIDTH/320,OUTPUT_WIDTH/240,1.0)

	for j=0, flowSize-1, 4 do
		x1 = _mosaic_data_inlet[3+j]
		y1 = _mosaic_data_inlet[3+j+1]
		x2 = _mosaic_data_inlet[3+j+2]
		y2 = _mosaic_data_inlet[3+j+3]
		if x1 and x2 and y1 and y2 then
			of.drawLine(x1,y1,x2,y2)
		end
	end

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
