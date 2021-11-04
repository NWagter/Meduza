local fMoveSpeed
local fLifeTime

local bMoveRight

function OnStart(a_host, a_entity)
	fMoveSpeed = 15
	fLifeTime = 4
	bMoveRight = true
end

function OnUpdate(a_host, a_entity, a_fDT)

	vMove = _CreateVector3()
	
	if bMoveRight then
		vMove.x = fMoveSpeed * a_fDT
	else
		vMove.x = -fMoveSpeed * a_fDT
	end
	
    _Move(a_entity, vMove)
	
	fLifeTime = fLifeTime - a_fDT
	
	if fLifeTime <= 0 then
		_DestroyEnt(a_entity)
	end
	
	enemy = _OnTriggerEntityName(a_entity, "SpikeBall_Enemy")
    if enemy ~= 0 then
		_CallFunction(enemy, "Spikeball_Enemy", "Kill", a_entity)
    end
	
end

function MoveRight(a_callerEnt)
	bMoveRight = true
end

function MoveLeft(a_callerEnt)
	bMoveRight = false	
end