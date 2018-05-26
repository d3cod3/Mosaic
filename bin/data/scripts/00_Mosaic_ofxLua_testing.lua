counter = 0
bSmooth = false

----------------------------------------------------
function setup()
	print("script setup")

	of.setCircleResolution(50)
	of.background(255, 255, 255, 255)
	of.setWindowPosition(500,100)
	of.setWindowShape(1024,768)
	
	of.disableSmoothing()
end

----------------------------------------------------
function update()
	counter = counter + 0.033
end

----------------------------------------------------
function draw()

	-- CIRCLES
	-- let's draw a circle
	of.setColor(255, 130, 0)
	local radius = 50 + 10 * math.sin(counter)
	of.fill()
	of.drawCircle(100, 400, radius)

	-- now just an outline
	of.noFill()
	of.setHexColor(0xCCCCCC)
	of.drawCircle(100, 400, 80)

	-- label
	of.setHexColor(0x000000)
	of.drawBitmapString("circle", 75, 500)

	-- RECTANGLES
	of.fill()
	for i=0,200 do
		of.setColor(of.random(0, 255), of.random(0, 255), of.random(0, 255))
		of.drawRectangle(of.random(250, 350), of.random(350, 450),
		                 of.random(10, 20), of.random(10, 20))
	end
	of.setHexColor(0x000000)
	of.drawBitmapString("rectangles", 275, 500)

	-- TRANSPARENCY
	of.setHexColor(0x00FF33)
	of.drawRectangle(400, 350, 100, 100)
	-- alpha is usually turned off - for speed puposes.  let's turn it on!
	of.enableAlphaBlending()
	of.setColor(255, 0, 0, 127)   -- red, 50% transparent
	of.drawRectangle(450, 430, 100, 33)
	of.setColor(255, 0, 0, math.fmod(counter*10, 255))	-- red, variable transparent
	of.drawRectangle(450, 370, 100, 33)
	of.disableAlphaBlending()

	of.setHexColor(0x000000)
	of.drawBitmapString("transparency", 410, 500)

	-- LINES
	-- a bunch of red lines, make them smooth if the flag is set

	if bSmooth then
		of.enableSmoothing()
	end

	of.setHexColor(0xFF0000)
	for i=0,20 do
		of.drawLine(600, 300 + (i*5), 800, 250 + (i*10))
	end

	if bSmooth then
		of.disableSmoothing()
	end

	of.setHexColor(0x000000)
	of.drawBitmapString("lines\npress 's' to toggle smoothness", 600, 500)

end

----------------------------------------------------
function exit()
	print("script finished")
end

-- input callbacks

----------------------------------------------------
function keyPressed(key)
	-- print out key as ascii val & char (keep within ascii 0-127 range)
	print("script keyPressed: "..tostring(key).." \'"..string.char(math.max(math.min(key, 127), 0)).."\'")
	if key == string.byte("s") then
		bSmooth = not bSmooth
	end
end
