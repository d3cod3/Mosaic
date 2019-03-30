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
--	HaarTracking.lua: Example receiving vector data from Mosaic "haar tracking" object
--
--	you can try running this script in patch example: examples/visualprogramming/ComputerVision/HaarTracking.xml
--


-- variables for mouse interaction
mouseX = 0
mouseY = 0

-- _mosaic_data_inlet is the name of the lua table storing data incoming from a Mosaic patch
-- a vector<float> is automatically converted to a lua table, where the index starts from 1, NOT 0
-- so the first position of your table will be accessed like this: _mosaic_data_inlet[1]

tableSize = 0

-- blobs variables

-- blobs vector from "haar tracking" Mosaic object is constructed as follows:
--
-- REMEMBER, A LUA TABLE START INDEX IS 1, NOT 0 !!!
--
-- [1] -> number of active haar blobs
-- [2] -> blob ID					---> accessible as _mosaic_data_inlet[2 + 8*N] for N blobs
-- [3] -> blob age (milliseconds)
-- [4] -> blob center X
-- [5] -> blob center Y
-- [6] -> blob bounding rect X		---> accessible as _mosaic_data_inlet[6 + 8*N] for N blobs
-- [7] -> blob bounding rect Y
-- [8] -> blob bounding rect Width
-- [9] -> blob bounding rect Height
--

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
		x = _mosaic_data_inlet[6 + 8*j]
		y = _mosaic_data_inlet[7 + 8*j]
		w = _mosaic_data_inlet[8 + 8*j]
		h = _mosaic_data_inlet[9 + 8*j]

		of.setColor(31,165,210)
		of.drawRectangle(x,y,w,h)

		center = of.Vec2f(_mosaic_data_inlet[4 + 8*j],_mosaic_data_inlet[5 + 8*j])

		of.setColor(255)
		of.drawBitmapString(string.format("%s:%s",_mosaic_data_inlet[2 + 8*j],_mosaic_data_inlet[3 + 8*j]),x,y-6)
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
