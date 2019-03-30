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
--	ContourTracking_convexHull.lua: Example receiving vector data from Mosaic "contour tracking" object
--  fourth outlet (tracked convex hulls)
--
--	you can try running this script in patch example: examples/visualprogramming/ComputerVision/ContourTracking.xml
--


-- variables for mouse interaction
mouseX = 0
mouseY = 0

-- _mosaic_data_inlet is the name of the lua table storing data incoming from a Mosaic patch
-- a vector<float> is automatically converted to a lua table, where the index starts from 1, NOT 0
-- so the first position of your table will be accessed like this: _mosaic_data_inlet[1]

tableSize = 0

-- contours variables

-- convex hull vector from "contour tracking" Mosaic object is constructed as follows:
--
-- REMEMBER, A LUA TABLE START INDEX IS 1, NOT 0 !!!
--
-- [1] -> number of active blobs
-- [2] -> number of contour vertices
-- [3] -> blob ID
-- [4] -> blob age (milliseconds)
-- [5 - 5+(_mosaic_data_inlet[2] * 2)] -> blob contour vertices

numBlobs = 0

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
	of.background(0,0,0)
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
	of.setColor(31,165,210)

	numBlobs = _mosaic_data_inlet[1]

	nextIndex = 2
	for j=0, numBlobs-1 do

		numVertices = _mosaic_data_inlet[nextIndex]*2

		contour = of.Polyline()

		if numVertices then
			for i=0, numVertices-1, 2 do
				x = _mosaic_data_inlet[nextIndex+3+i]
				y = _mosaic_data_inlet[nextIndex+3+i+1]
				if x and y then
					contour:addVertex(x,y,0)
				end
			end

			contour:draw()

			nextIndex = nextIndex + numVertices + 3
		end

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
