local nMoveSpeed
local ePlayerEntity
local fYOffset
local vDir

function OnStart(a_host, a_entity)
	ePlayerEntity = _GetEntityByName("Megamen")
	nMoveSpeed = 7
	vDir = _CreateVector3()
end

function OnUpdate(a_host, a_eEntity, a_nDt)

	vPlayerLocation = _GetLocation(ePlayerEntity)
	vOwnLocation = _GetLocation(a_eEntity)
	
	vDir.x = ((vPlayerLocation.x - vOwnLocation.x) * nMoveSpeed) * a_nDt
	
	_Move(a_eEntity, vDir)
end