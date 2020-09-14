-------------------------------------------------
-- MOSAIC Util Classes
-------------------------------------------------

-- DraggableVertex

DraggableVertex = class()

function DraggableVertex:__init(x, y, r)
	self.x = x
	self.y = y
	self.bBeingDragged = false
	self.bOver = false
	self.radius = r
end

function DraggableVertex:setPosition(x,y)
	self.x = x
	self.y = y
end

function DraggableVertex:setRadius(r)
	self.radius = r
end

function DraggableVertex:update(x,y,r)
	self:setPosition(x,y)
	self:setRadius(r)
end

function DraggableVertex:draw()
	if self.bOver then
		of.fill()
	else
		of.noFill()
	end
	of.drawCircle(self.x, self.y, self.radius)
end

function DraggableVertex:mouseMoved(x,y)
	local diffx = x - self.x
	local diffy = y - self.y
	local dist = math.sqrt(diffx*diffx + diffy*diffy)
		if dist < self.radius then
			self.bOver = true
		else
			self.bOver = false
		end
end

function DraggableVertex:mouseDragged(x,y)
	if self.bBeingDragged == true then
		self.x = x
		self.y = y
	end
end

function DraggableVertex:mousePressed(x,y)
	local diffx = x - self.x
	local diffy = y - self.y
	local dist = math.sqrt(diffx*diffx + diffy*diffy)
	if dist < self.radius then
		self.bBeingDragged = true
	else
		self.bBeingDragged = false
	end
end

function DraggableVertex:mouseReleased(x,y)
	self.bBeingDragged = false
end
-------------------------------------------------


-------------------------------------------------
-------------------------------------------------
-------------------------------------------------

-- MOSAIC core methods
-------------------------------------------------


-------------------------------------------------
function mosaicBackground(r,g,b,a)
	of.setColor(r,g,b,a)
	of.drawRectangle(0,0,OUTPUT_WIDTH,OUTPUT_HEIGHT)
end

-------------------------------------------------
function checkMosaicDataInlet()
	-- first check if we are using the data inlet
	if USING_DATA_INLET then
		-- avoid null readings
		if next(_mosaic_data_inlet) == nil then
			return
		end
	end
end

-------------------------------------------------
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

-------------------------------------------------
-------------------------------------------------
-------------------------------------------------

-- MOSAIC trigonometry methods
-------------------------------------------------

-------------------------------------------------
function getPointOnCircle(angleRadians, radius)
	p = of.Point()
	p.x = radius*math.cos(angleRadians)
	p.y = radius*math.sin(-angleRadians)
	return p
end

-------------------------------------------------
function getHeading(p, anchor)
	p = p - anchor
	return math.atan2(p.y, -p.x)+of.PI -- radians
end

------------------------------------------------- Distance between two points
function mosaicDist(ax, ay, az, bx, by, bz)
	return math.sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) + (z2-z1)*(z2-z1))
end

-------------------------------------------------
-------------------------------------------------
-------------------------------------------------

-- MOSAIC graphics methods
-------------------------------------------------

------------------------------------------------- Color Match with tolerance [0 - 255]
function mosaicColorMatch(colorA, colorB, tolerance)
	dist = mosaicDist(colorA.r,colorA.g,colorA.b,colorB.r,colorB.g,colorB.b)
	if dist <= tolerance then
		return true
	else
		return false
	end
end

-------------------------------------------------
-------------------------------------------------
-------------------------------------------------

-- MOSAIC string methods
-------------------------------------------------

-------------------------------------------------
