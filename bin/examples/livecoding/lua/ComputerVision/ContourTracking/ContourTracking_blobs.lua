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
--	ContourTracking_blobs.lua: Example receiving vector data from Mosaic "contour tracking" object
--  second outlet (tracked blobs data)
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

-- blobs variables

-- blobs vector from "contour tracking" Mosaic object is constructed as follows:
--
-- REMEMBER, A LUA TABLE START INDEX IS 1, NOT 0 !!!
--
-- [1] -> number of active blobs
-- [2] -> blob ID					---> accessible as _mosaic_data_inlet[2 + 16*N] for N blobs
-- [3] -> blob age (milliseconds)
-- [4] -> blob centroid X
-- [5] -> blob centroid Y
-- [6] -> blob average X
-- [7] -> blob average Y
-- [8] -> blob center X
-- [9] -> blob center Y
-- [10] -> blob velocity X
-- [11] -> blob velocity Y
-- [12] -> blob area
-- [13] -> blob perimeter
-- [14] -> blob bounding rect X		---> accessible as _mosaic_data_inlet[14 + 16*N] for N blobs
-- [15] -> blob bounding rect Y
-- [16] -> blob bounding rect Width
-- [17] -> blob bounding rect Height
--

numBlobs = 0

-- for visualizing velocity vector
ground = of.Vec2f(1,0)

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


	----------------------------------------- Drawing blobs
	of.setLineWidth(3)
	of.noFill()

	numBlobs = _mosaic_data_inlet[1]

	for j=0, numBlobs-1 do
		x = _mosaic_data_inlet[14 + 16*j]
		y = _mosaic_data_inlet[15 + 16*j]
		w = _mosaic_data_inlet[16 + 16*j]
		h = _mosaic_data_inlet[17 + 16*j]

		of.setColor(31,165,210)
		of.drawRectangle(x,y,w,h)

		center = of.Vec2f(_mosaic_data_inlet[4 + 16*j],_mosaic_data_inlet[5 + 16*j])
		vel = of.Vec2f(_mosaic_data_inlet[10 + 16*j]*10,_mosaic_data_inlet[11 + 16*j]*10)

		of.setColor(255)
		drawVector(vel,center,1)

		of.drawBitmapString(string.format("%s:%s",_mosaic_data_inlet[2 + 16*j],_mosaic_data_inlet[3 + 16*j]),x,y-6)
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


-- custom functions

----------------------------------------------------
function drawVector(v,loc,scayl)
	of.pushMatrix()
	arrowSize = 10
	of.translate(loc.x,loc.y,0)
	of.rotateDeg(-v:angle(ground)) -- heading2D -->  -v:angle(ofVec2f(1,0))
	len = v:length()*scayl
	of.drawLine(0,0,len,0)
	of.drawLine(len,0,len-arrowSize,arrowSize/2)
	of.drawLine(len,0,len-arrowSize,-arrowSize/2)
	of.popMatrix()
end
