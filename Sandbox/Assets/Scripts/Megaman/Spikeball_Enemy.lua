local nDistance

local bDefenceForm

local nCurrentAnimationId
local nMaxIdleAnimationId
local nMaxDefendAnimationId

local nAnimationTime
local nIdleAnimSpeed
local nDefendAnimSpeed

local bDead

local eSelfEnt

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

function OnStart(a_host, a_eEntity)

	eSelfEnt = a_eEntity
	
	nCurrentAnimationId = 1
	nMaxIdleAnimationId = 7
	nMaxDefendAnimationId = 7
	
	nDistance = 12
	
	nAnimationTime = 0.5
	nIdleAnimSpeed = 4
	
	bDefenceForm = false
	bDead = false
	
	anim = tIdleTable[nCurrentAnimationId]
	_SetUV(a_eEntity, anim.x, anim.y, anim.z, anim.w)	
end

function OnUpdate(a_host, a_eEntity, a_nDt)

	
	if nAnimationTime <= 0 then
	
		nAnimationTime = 0.5
		if not bDefenceForm then
			nCurrentAnimationId = nCurrentAnimationId + 1
			if nCurrentAnimationId > nMaxIdleAnimationId then
				nCurrentAnimationId = 1
			end
			
			anim = tIdleTable[nCurrentAnimationId]		
			_SetUV(a_eEntity, anim.x, anim.y, anim.z, anim.w)	
		else
			nCurrentAnimationId = nCurrentAnimationId + 1
			if nCurrentAnimationId > nMaxDefendAnimationId then
				nCurrentAnimationId = 1
			end
			
			anim = tDefendTable[nCurrentAnimationId]		
			_SetUV(a_eEntity, anim.x, anim.y, anim.z, anim.w)	
		end
		
	end	
	
	nAnimationTime = nAnimationTime - nIdleAnimSpeed * a_nDt

	
	ePlayer = _GetEntityByName("Megamen")
	
	if ePlayer > 0 then
		if _GetDistance(a_eEntity, ePlayer) < nDistance then
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
		results = _OnCollision(a_eEntity)

		for i = 0, #results do
			if results[i].hasHit then
				if(results[i].name == "Megamen") then
					_DestroyEnt(results[i].entity)	
				end
			end
		end
	else
		
	end
end

function Kill(a_eCallerEnt)

	if not bDefenceForm then
		_DestroyEnt(eSelfEnt)	
	end
	
	_DestroyEnt(a_eCallerEnt)

end