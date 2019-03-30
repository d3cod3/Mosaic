--
--
--	----------------------------------------------------------
--	Mosaic | OF Visual Patching Developer Platform
--
--	Copyright (c) 2019 Emanuele Mazza aka n3m3da
--
--	Mosaic is distributed under the MIT License. This gives everyone the
--  freedoms to use Mosaic in any context: commercial or non-commercial,
--  public or private, open or closed source.
--
--  See https://github.com/d3cod3/Mosaic for documentation
--	----------------------------------------------------------
--
--
--	EmptyScriptWithMosaicTableFROM_LUA.lua: A basic template script for sending a vector<float> data
--  (the "lua script" object third outlet) to a Mosaic patch
--
--


-- variables for mouse interaction (DO NOT DELETE)
mouseX = 0
mouseY = 0

-- Mosaic system variable for loading external resources (files)
-- Example:
-- img = of.Image()
-- img:load(SCRIPT_PATH .. "/data/test.jpg")

-- _mosaic_data_outlet is the name of the lua table storing data outgoing to a Mosaic patch
-- a lua table is automatically converted to a vector<float>. Remember that lua tables index starts from 1, NOT 0
-- so the first position of your table will be accessed like this: _mosaic_data_outlet[1]

----------------------------------------------------
function setup()
	_mosaic_data_outlet[1] = 10
	_mosaic_data_outlet[2] = 30
	_mosaic_data_outlet[3] = 50

end

----------------------------------------------------
function update()
	_mosaic_data_outlet[4] = of.random(1)

end

----------------------------------------------------
function draw()
	of.background(0)


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
