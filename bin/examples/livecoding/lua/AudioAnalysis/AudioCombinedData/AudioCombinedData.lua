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
--	AudioCombinedData.lua: Basic example of receiving combined data from "audio analyzer" object from Mosaic
--
--	you can try running this script in patch example: examples/visualprogramming/AudioAnalysis/AudioAnalysis_toLua.xml
--


-- variables for mouse interaction
mouseX = 0
mouseY = 0

-- _mosaic_data_inlet is the name of the lua table storing data incoming from a Mosaic patch
-- a vector<float> is automatically converted to a lua table, where the index starts from 1, NOT 0
-- so the first position of your table will be accessed like this: _mosaic_data_inlet[1]

tableSize = 0

-- in this example we are using the patch examples/visualprogramming/AudioAnalysis/AudioAnalysis_toLua.xml
-- where the order of tha data table is:
--
-- [1] --> beat
-- [2] --> rms
-- [3] --> pitch
-- [4] --> bpm
-- [5] --> inharmonicity
-- [6 - 6 + 129(FFT data)] --> FFT

beatIndex 		= 1
rmsIndex 		= 2
pitchIndex 		= 3
bpmIndex		= 4
inharmIndex		= 5
startFFTindex	= 6
FFTSize 		= 129	-- (FFT size is extracted from bufferSize, in Mosaic bufferSize is fixed at 256, fftsize = bufferSize/2 + 1)

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

	-- draw something from audio analysis data

	-- The table indexes for data are not fixed, it depends on how you combine the vector data inside
	-- your Mosaic patch, using the "floats to vector" and "vector concat" objects

	-- in this example we are using the patch examples/visualprogramming/AudioAnalysis/AudioAnalysis_toLua.xml
	-- where the order of tha data table is:
	--
	-- [1] --> beat
	-- [2] --> rms
	-- [3] --> pitch
	-- [4] --> bpm
	-- [5] --> inharmonicity
	-- [6 - 6 + 129(FFT data)] --> FFT

	-- beat detection
	if tableSize > beatIndex then
		of.setColor(255,255,255)
		of.drawRectangle(0,OUTPUT_HEIGHT/2,_mosaic_data_inlet[beatIndex]*OUTPUT_WIDTH,_mosaic_data_inlet[beatIndex]*10)
		of.setColor(255,255,255,240)
		of.drawRectangle(0,0,_mosaic_data_inlet[beatIndex]*OUTPUT_WIDTH,_mosaic_data_inlet[beatIndex]*OUTPUT_HEIGHT)
	end

	-- rms (volume)
	if tableSize > rmsIndex then
		correctedRMS = math.abs(_mosaic_data_inlet[rmsIndex]-0.5) * 2
		of.noFill()
		of.drawRectangle(0,OUTPUT_HEIGHT/3,correctedRMS*OUTPUT_WIDTH,OUTPUT_HEIGHT/3)
		of.drawRectangle(OUTPUT_WIDTH,OUTPUT_HEIGHT/3,-correctedRMS*OUTPUT_WIDTH,OUTPUT_HEIGHT/3)
	end

	-- pitch
	if tableSize > pitchIndex then
		normalizedPitch = _mosaic_data_inlet[pitchIndex]/4186 -- pitch detection range from "audio analyzer" object is 0-4186 Hz
		of.setColor(127,64,64)
		of.noFill()
		of.drawRectangle(0,OUTPUT_HEIGHT/3,normalizedPitch*OUTPUT_WIDTH,OUTPUT_HEIGHT/3)
		of.drawRectangle(OUTPUT_WIDTH,OUTPUT_HEIGHT/3,-normalizedPitch*OUTPUT_WIDTH,OUTPUT_HEIGHT/3)
	end

	-- BPM
	if tableSize > bpmIndex then
		of.setColor(127)
		for i=0,math.floor(_mosaic_data_inlet[bpmIndex]) do
			of.pushMatrix()
			of.rotateYRad(of.random(of.PI))
			of.drawRectangle(OUTPUT_WIDTH/_mosaic_data_inlet[bpmIndex]*i,OUTPUT_HEIGHT/2,1,10)
			of.popMatrix()
		end
	end

	-- inharmonicity
	if tableSize > inharmIndex then
		of.setColor(64,64,127)
		of.noFill()
		of.drawRectangle(0,OUTPUT_HEIGHT/3,_mosaic_data_inlet[inharmIndex]*OUTPUT_WIDTH,OUTPUT_HEIGHT/3)
	end

	-- FFT
	if tableSize > startFFTindex+FFTSize-1 then
		of.noFill()
		of.setColor(127)
		for i=0,FFTSize-1 do
			of.pushMatrix()
			of.translate(OUTPUT_WIDTH/2,0,0)
			of.drawRectangle(-OUTPUT_WIDTH*4*_mosaic_data_inlet[startFFTindex+i]/2,0,OUTPUT_WIDTH*4*_mosaic_data_inlet[startFFTindex+i],OUTPUT_HEIGHT/3.01)
			of.drawRectangle(-OUTPUT_WIDTH*3*_mosaic_data_inlet[startFFTindex+i]/2,OUTPUT_HEIGHT,OUTPUT_WIDTH*3*_mosaic_data_inlet[startFFTindex+i],-OUTPUT_HEIGHT/3.02)
			of.popMatrix()
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
