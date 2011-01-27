local frame = 0
local nparticulas = 0

local bordex = 4.5
local bordey = 3.2
local bordec = 3
local tindex = 0
local bx = 0
local by = 0

function this.Init(this)
    this:PushDebugString("Init parts OK")
    tindex = this:GetTrackerSystemData()
    if ( tindex == -1 ) then
	this:PushDebugString("Warning no tracker index")
    end
end


function this.Run(this)
    --this:PushDebugString("Hello from Run")
end


function this.RunSystem(this, nparts )

end

function this.RunParticle(this, i)

	--posicion de la particula i
	x,y,z = this:GetParticlePosition( i )

	--velocidad de la particula i
	vx,vy,vz = this:GetParticleVelocity( i )

	--edad , visibilidad, masa de la particula i
	age,visible,mass = this:GetParticle( i )
	
	--ticks = this:GetTicks();
	
	--this:PushDebugString("texto que se puede ver en el Log")

	--this:UpdateParticlePosition( i, x2, y2, z )	
	if ( x > bordex  or x<-bordex  ) then
		this:UpdateParticleVelocity( i, -vx, vy, vz )
	end

	if ( y>bordey  ) then
		this:UpdateParticleVelocity( i, vx, -vy, vz )
	end

	dc = math.sqrt((bx-x)*(bx-x)+(by-y)*(by-y))

	if ( 0.4 < dc and dc < 0.5 and vy<0 ) then
		this:UpdateParticleVelocity( i, -vx, -vy, vz )
	end
	
end


--nparts: cantidad de particulas
--nfeats: cantidad maxima de marcas sensadas
--nvalids: cantidad marcas sensadas

function this.Update(this, nparts, nfeats, nvalids )

	nparticulas = nparts

	--this:PushDebugString("features")
	--this:PushDebugString( nfeats )

	--Actualizamos la posicion del baricentro
	if ( tindex > -1 ) then
		bx,by = this:GetTrackerBarycenter(tindex)
		bx = (bx - 0.5 ) * 10.0
		by = - (by - 0.5 ) * 10.0 * 3 / 4
	end

end


function this.Finish(this)
    --this:PushDebugString("Hello from Finish")
end

