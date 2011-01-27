local frame = 0
local nparticulas = 0

local bordex = 7
local bordey = 5
local bordec = 2
local tindex = 0
local bx = 0
local by = 0

function this.Init(this)
    this:PushDebugString("Init parts OK")
end


function this.Run(this)
    --this:PushDebugString("Hello from Run")
end


function this.RunSystem(this, nparts )

end

function this.RunParticle(this, i)

	x,y,z = this:GetParticlePosition( i )
	vx,vy,vz = this:GetParticleVelocity( i )
	age,visible,mass = this:GetParticle( i )
	
	--ticks = this:GetTicks();
	
	if ( x > bordex  or x<-bordex  ) then
		this:UpdateParticleVelocity( i, -vx, vy, vz )
	end

	if ( y>bordey or y<-bordey  ) then
		this:UpdateParticleVelocity( i, vx, -vy, vz )
	end

	dc = math.sqrt(x*x+y*y+z*z)

	if ( bordec < dc and  dc < bordec+0.1  ) then
		this:UpdateParticleVelocity( i, -vx, -vy, -vz )
	end

end


function this.Update(this, nparts, nfeats, nvalids )

	nparticulas = nparts


end


function this.Finish(this)
    --this:PushDebugString("Hello from Finish")
end

