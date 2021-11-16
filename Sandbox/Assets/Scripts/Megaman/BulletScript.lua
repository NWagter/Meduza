local nMoveSpeed
local nLifeTime

local bMoveRight

function OnStart(a_host, a_eEntity)
	nMoveSpeed = 15
	nLifeTime = 4
	bMoveRight = true
end

function OnUpdate(a_host, a_eEntity, a_nDt)

	vMove = _CreateVector3()
	
	if bMoveRight then
		vMove.x = nMoveSpeed * a_nDt
	else
		vMove.x = -nMoveSpeed * a_nDt
	end
	
    _Move(a_eEntity, vMove)
	
	nLifeTime = nLifeTime - a_nDt
	
	if nLifeTime <= 0 then
		_DestroyEnt(a_eEntity)
	end
	
	results = _OnTrigger(a_eEntity)
	for i = 0, #results do
		if results[i].hasHit then
			if results[i].name == "SpikeBall_Enemy" then
				_CallFunction(results[i].entity, "Spikeball_Enemy", "Kill", a_eEntity)
			end		
			_DestroyEnt(a_eEntity)
		end
	end
end

function MoveRight(a_eCallerEnt)
	bMoveRight = true
end

function MoveLeft(a_eCallerEnt)
	bMoveRight = false	
end