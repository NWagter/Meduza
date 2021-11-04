local fDistance

local bDefenceForm

local iCurrentAnimationId
local iMaxIdleAnimationId
local iMaxDefendAnimationId

local fAnimationTime
local fIdleAnimSpeed
local fDefendAnimSpeed

local bDead

local selfEnt

local tIdleTable = {
	{x = 6, y = 43, z = 35, w = 42},
	{x = 42, y = 43, z = 39, w = 42},
	{x = 82, y = 43, z = 43, w = 42},
	{x = 126, y = 43, z = 44, w = 42},
	{x = 171, y = 43, z = 47, w = 42},
	{x = 219, y = 43, z = 51, w = 42},
	{x = 271, y = 43, z = 47, w = 42}
}

local tDefendTable = {
	{x = 18, y = 8, z = 41, w = 31},
	{x = 60, y = 8, z = 41, w = 31},
	{x = 102, y = 8, z = 41, w = 31},
	{x = 146, y = 8, z = 37, w = 31},
	{x = 185, y = 8, z = 36, w = 31},
	{x = 222, y = 8, z = 37, w = 31},
	{x = 260, y = 8, z = 32, w = 31}
}

function OnStart(a_host, a_entity)

	selfEnt = a_entity
	
	iCurrentAnimationId = 1
	iMaxIdleAnimationId = 7
	iMaxDefendAnimationId = 7
	
	fDistance = 12
	
	fAnimationTime = 0.5
	fIdleAnimSpeed = 4
	
	bDefenceForm = false
	bDead = false
	
	anim = tIdleTable[iCurrentAnimationId]
	_SetUV(a_entity, anim.x, anim.y, anim.z, anim.w)	
end

function OnUpdate(a_host, a_entity, a_fDT)

	
	if fAnimationTime <= 0 then
	
		fAnimationTime = 0.5
		if not bDefenceForm then
			iCurrentAnimationId = iCurrentAnimationId + 1
			if iCurrentAnimationId > iMaxIdleAnimationId then
				iCurrentAnimationId = 1
			end
			
			anim = tIdleTable[iCurrentAnimationId]		
			_SetUV(a_entity, anim.x, anim.y, anim.z, anim.w)	
		else
			iCurrentAnimationId = iCurrentAnimationId + 1
			if iCurrentAnimationId > iMaxDefendAnimationId then
				iCurrentAnimationId = 1
			end
			
			anim = tDefendTable[iCurrentAnimationId]		
			_SetUV(a_entity, anim.x, anim.y, anim.z, anim.w)	
		end
		
	end	
	
	fAnimationTime = fAnimationTime - fIdleAnimSpeed * a_fDT

	
	pEnt = _GetEntityByName("Megamen")
	
	if pEnt > 0 then
		if _GetDistance(a_entity, pEnt) < fDistance then
			bDefenceForm = true
		else
			bDefenceForm = false
		end
	else
		if bDefenceForm then
			bDefenceForm = false	
		end
	end
	
	if bDefenceForm then
		-- Check for Player
		player = _OnCollisionEntityName(a_entity, "Megamen")
		if player ~= 0 then
			_DestroyEnt(player)		
		end
	else
		
	end
end

function Kill(a_callerEnt)

	if not bDefenceForm then
		_DestroyEnt(selfEnt)	
	end
	
	_DestroyEnt(a_callerEnt)

end