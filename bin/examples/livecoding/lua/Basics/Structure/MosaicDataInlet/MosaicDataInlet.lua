--
--
--	----------------------------------------------------------
--	Mosaic | OF Visual Patching Developer Platform
--
--	Copyright (c) 2019 Emanuele Mazza aka n3m3da
--
--	Mosaic is distributed under the MIT License. This gives everyone the
--    freedoms to use Mosaic in any context: commercial or non-commercial,
--    public or private, open or closed source.
--
--    See https://github.com/d3cod3/Mosaic for documentation
--	----------------------------------------------------------
--
--
--	MosaicDataInlet.lua: A basic template script for receiving the vector data
--  (the "lua script" object inlet) from Mosaic patch
--
--	you can try running this script in patch example: examples/visualprogramming/Structure/DataVectorComposer.xml
--


-- variables for mouse interaction
mouseX = 0
mouseY = 0

-- _mosaic_data_inlet is the name of the lua table storing data incoming from a Mosaic patch
-- a vector<float> is automatically converted to a lua table, where the index starts from 1, NOT 0
-- so the first position of your table will be accessed like this: _mosaic_data_inlet[1]

tableSize = 0
lastTableSize = 0

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

	-- check _mosaic_data_inlet size changes
	if lastTableSize ~= tableSize then
		lastTableSize = tableSize
		of.log(of.LOG_NOTICE,string.format("_mosaic_data_inlet size: %i",tableSize))
	end
	-----------------------------------------

	-- draw something using _mosaic_data_inlet data
	of.setColor(255,255,255,10)
	if tableSize > 1 then
		of.pushMatrix()
		of.translate(OUTPUT_WIDTH/2,OUTPUT_HEIGHT/2,0)
		of.drawCircle(0,0,_mosaic_data_inlet[1]*OUTPUT_HEIGHT/2)
		of.popMatrix()
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
