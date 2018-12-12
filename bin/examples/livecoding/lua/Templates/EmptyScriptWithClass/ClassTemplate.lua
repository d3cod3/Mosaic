---------------------------------------------------
------- class ClassTemplate

-- constructor
ClassTemplate = class(
	function(this,x)
		-- create here all the needed class variables, is necessary to use this. when creating a new variable
		this.posX 	= x
		this.rand 	= math.random()
		-- .......
	end
)

-- After defining the class Constructor, we can access every defined class variable with self.variableName
-- Example: self.posX or self.rand in this case

function ClassTemplate:update()

end

function ClassTemplate:draw()
    of.drawCircle(self.posX,OUTPUT_HEIGHT/2, 100*self.rand)
end

---------------------------------------------------
------- end class ClassTemplate
