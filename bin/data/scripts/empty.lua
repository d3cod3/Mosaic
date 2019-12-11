--
--
--	----------------------------------------------------------
--	Mosaic | OF Visual Patching Developer Platform
--
--	Copyright (c) 2019 Emanuele Mazza aka n3m3da
--
--	Mosaic is distributed under the MIT License.
--	This gives everyone the freedoms to use Mosaic in any context:
--	commercial or non-commercial, public or private,
--	open or closed source.
--
--  See https://github.com/d3cod3/Mosaic for documentation
--	----------------------------------------------------------
--
--
--	empty.lua: A Lua script template for Mosaic,
--	mimicking the standard OF app structure

---------------------------------- MOSAIC SPECIFIC CODING INFO

-- Mosaic system variable for loading external resources (files)
-- Example:
-- img = of.Image()
-- img:load(SCRIPT_PATH .. "/data/test.jpg")

---------------------------------- MOSAIC SPECIFIC CODING INFO


----------------------------------- MOSAIC VARS (DO NOT TOUCH)

-- variables for mouse interaction
mouseX = 0
mouseY = 0

-- variable for storing _mosaic_data_inlet size
mosaic_data_inlet_size = 0
----------------------------------- MOSAIC VARS (DO NOT TOUCH)

----------------------------------- MY VARS

-- add here your variables

----------------------------------- MY VARS

----------------------------------------------------

-- main methods

----------------------------------------------------
function setup()

	------------------------------------------------ MY CODE

	-- add here your setup code

	------------------------------------------------ MY CODE

end

----------------------------------------------------
function update()

	------------------------------------------------ MOSAIC CODE
	mosaic_data_inlet_size = getMosaicDataInletSize()

	-- send data to _mosaic_data_outlet if needed
	-- we are using here just the first position of the table
	-- but you can expand it with numerical data as you need it
	_mosaic_data_outlet[1] = of.random(10)
	------------------------------------------------ MOSAIC CODE

	------------------------------------------------ MY CODE

	-- add here your update code

	------------------------------------------------ MY CODE

end

----------------------------------------------------
function draw()

	------------------------------------------------ MOSAIC CODE
	checkMosaicDataInlet()
	------------------------------------------------ MOSAIC CODE

	------------------------------------------------ MY CODE

	-- draw background first
	mosaicBackground(0,0,0,255)

	-- add here your draw code

	------------------------------------------------ MY CODE


end

----------------------------------------------------
function exit()

end

----------------------------------------------------

-- input callbacks

----------------------------------------------------
function keyPressed(key)

end

----------------------------------------------------
function keyReleased(key)

end

----------------------------------------------------
function mouseMoved(x,y)
	mouseX = x
	mouseY = y
end

----------------------------------------------------
function mouseDragged(x,y)
	mouseX = x
	mouseY = y
end

----------------------------------------------------
function mouseReleased(x,y)

end

----------------------------------------------------
function mouseScrolled(x,y)

end

----------------------------------------------------

-- MOSAIC custom methods

function mosaicBackground(r,g,b,a)
	of.setColor(r,g,b,a)
	of.drawRectangle(0,0,OUTPUT_WIDTH,OUTPUT_HEIGHT)
end

function checkMosaicDataInlet()
	-- first check if we are using the data inlet
	if USING_DATA_INLET then
		-- avoid null readings
		if next(_mosaic_data_inlet) == nil then
			return
		end
	end
end

function getMosaicDataInletSize()
	if USING_DATA_INLET then
		checkMosaicDataInlet()
		-- get _mosaic_data_inlet size
		tableSize = 0
		for k,v in pairs(_mosaic_data_inlet) do
			tableSize = tableSize + 1
		end
		return tableSize
	else
		return 0
	end
end

----------------------------------------------------

-- MY custom methods

-- add here your custom methods if needed
