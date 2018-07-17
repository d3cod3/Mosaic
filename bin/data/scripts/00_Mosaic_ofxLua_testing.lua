counter = 0

mouseX = 0
mouseY = 0

sender  = ofx.OscSender()

----------------------------------------------------
function setup()

  sender:setup("127.0.0.1",57999)

end

----------------------------------------------------
function update()
  --message = ofx.OscMessage()
  --message:setAddress("/fader")
  --message:addIntArg(mouseX)

  --sender:sendMessage(message)
end

----------------------------------------------------
function draw()


  of.setColor(0,0,0,10)
	of.drawRectangle(0,0,OUTPUT_WIDTH,OUTPUT_HEIGHT)
	--of.background(255, 255, 255)
	of.setCircleResolution(50)
	-- CIRCLE
	of.setColor(255,0,0,100)
	local radius = 500 + 10 * math.sin(counter)
	of.fill()
	of.drawCircle(mouseX, mouseY, radius)

	-- RECTANGLES
	of.setColor(255)
	of.noFill()
	h = OUTPUT_HEIGHT/#_mosaic_data_table
	for k,v in pairs(_mosaic_data_table) do
		randW = of.random(_mosaic_data_table[k]*OUTPUT_WIDTH)
		of.drawRectangle((OUTPUT_WIDTH/2) - (randW/2), (k-1)*h,randW, h)
	end

end

----------------------------------------------------
function exit()

end

-- input callbacks

----------------------------------------------------
function keyPressed(key)
	--print("script keyPressed: "..tostring(key).." \'"..string.char(math.max(math.min(key, 127), 0)).."\'")
	if key == string.byte("s") then

	end
end
----------------------------------------------------
function mouseMoved(x,y)
	mouseX = x
	mouseY = y
end

function oscReceived(message)
	-- print received message
	--print(tostring(message))
end
