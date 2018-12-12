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
--	EmptyScriptWithClass.lua: A Basic Lua template script using a custom class for Mosaic,
--	mimicking the standard OF app structure
--
--

-- import required class (IMPORTANT, you'll need the ClassTemplate.lua in the same folder!!!)
require("ClassTemplate")

-- testing:
classObject = ClassTemplate(100)

-- variables for mouse interaction  (DO NOT DELETE)
mouseX = 0
mouseY = 0

-- Mosaic system variable for loading external resources (files)
-- Example:
-- img = of.Image()
-- img:load(SCRIPT_PATH .. "/data/test.jpg")

----------------------------------------------------
function setup()

end

----------------------------------------------------
function update()
    -- testing:
    classObject:update()
end

----------------------------------------------------
function draw()
	of.background(0)

    -- testing:
    classObject:draw()
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
