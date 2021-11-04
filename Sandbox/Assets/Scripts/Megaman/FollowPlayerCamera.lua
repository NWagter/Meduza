local fMoveSpeed
local playerEntity
local fYOffset
local vDir

function OnStart(a_host, a_entity)
	playerEntity = _GetEntityByName("Megamen")
	fMoveSpeed = 7
	vDir = _CreateVector3()
end

function OnUpdate(a_host, a_entity, a_dt)

	playerLocation = _GetLocation(playerEntity)
	ownLocation = _GetLocation(a_entity)
	
	vDir.x = ((playerLocation.x - ownLocation.x) * fMoveSpeed) * a_dt
	
	_Move(a_entity, vDir)
end