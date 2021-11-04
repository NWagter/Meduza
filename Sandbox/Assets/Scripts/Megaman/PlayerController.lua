local fMoveSpeed

local fTimeBetweenBullet
local fXBulletOffset

local bIsMoveRight
local bIsMoving
local lastBullet

local fAnimationTime
local fMoveAnimationMultiplier

local iCurrentAnimId
local iMaxMoveAnim
local iMaxIdleAnim

local tIdleAnimationTable = {
	{x = 0.5, y = 0.5, z = 36, w = 52},
	{x = 39, y = 0.5, z = 38, w = 52},
}

local tMoveAnimationTable = {
	{x = 79, y = 0.5, z = 51, w = 52},
	{x = 132, y = 0.5, z = 50, w = 52},
	{x = 184, y = 0.5, z = 48, w = 52},
	{x = 234, y = 0.5, z = 45, w = 52},
	{x = 281, y = 0.5, z = 44, w = 52},
	{x = 330, y = 0.5, z = 40, w = 52},
}

function OnStart(a_host, a_entity)
    fMoveSpeed = 10
	fTimeBetweenBullet = 0
	lastBullet = -1
	
	bIsMoveRight = true
	
	iCurrentAnimId = 1
	bIsMoving = false
	iMaxIdleAnim = 2
	iMaxMoveAnim = 6
	fAnimationTime = 0.2
	fMoveAnimationMultiplier = 5
	
	
	anim = tIdleAnimationTable[iCurrentAnimId]
	_SetUV(a_entity, anim.x, anim.y, anim.z, anim.w)
	fXBulletOffset = 2
end

function OnUpdate(a_host, a_entity, a_fDT)
	
	if fAnimationTime <= 0 then
	
		fAnimationTime = 0.2
		iCurrentAnimId = iCurrentAnimId + 1
		
		if bIsMoving then
		
			if iCurrentAnimId > iMaxMoveAnim then
				iCurrentAnimId = 1
			end
			
			anim = tMoveAnimationTable[iCurrentAnimId]
			_SetUV(a_entity, anim.x, anim.y, anim.z, anim.w)
		else			
			if iCurrentAnimId > iMaxIdleAnim then
				iCurrentAnimId = 1
			end
			
			anim = tIdleAnimationTable[iCurrentAnimId]
			_SetUV(a_entity, anim.x, anim.y, anim.z, anim.w)
		end
	end

	if bIsMoving then
		fAnimationTime = fAnimationTime - (fMoveAnimationMultiplier * a_fDT)	
	else	
		fAnimationTime = fAnimationTime - a_fDT
	end
	
	if lastBullet >= 0 then
		if bIsMoveRight then
			_CallFunction(lastBullet, "BulletScript", "MoveRight", a_entity)	
			lastBullet = -1
		else
			_CallFunction(lastBullet, "BulletScript", "MoveLeft", a_entity)	
			_FlipX(lastBullet)	
			lastBullet = -1
		end
	end

	vMove = _CreateVector3()
	
	if fTimeBetweenBullet > 0 then
		fTimeBetweenBullet = fTimeBetweenBullet - a_fDT
	end

	if _OnKeyDown(68) == 1 then
        vMove.x = (fMoveSpeed * a_fDT)   
		if not bIsMoveRight then
			bIsMoveRight = true
			_FlipX(a_entity)
		end
    elseif _OnKeyDown(65) == 1 then
        vMove.x = vMove.x -(fMoveSpeed * a_fDT) 
		if bIsMoveRight then
			bIsMoveRight = false
			_FlipX(a_entity)
		end 
    end  
	
	vVel = _GetVelocity(a_entity)
	
	nY = 50
	nX = nY * 0.1
	
	if not bIsMoveRight then
		nX = -nX
	end
	
	vForce = _CreateVector3(nX, nY, 0)
	
	if _OnKeyDown(32) == 1 and vVel.y == 0 then
		_ApplyForce(a_entity, vForce)
    end	
	
	if (_OnKeyDown(80) == 1 and fTimeBetweenBullet <= 0) then
		location = _GetLocation(a_entity)
		
		if bIsMoveRight then
			location.x = location.x + fXBulletOffset
		else
			location.x = location.x - fXBulletOffset			
		end
		
		lastBullet = _InstantiatePrefab("Assets/Prefab/Megamen/Bullet.prefab", location)		
		fTimeBetweenBullet = 0.5
	end
	
	if vMove.x ~= 0 or vMove.y ~= 0 then
		if not bIsMoving then
		bIsMoving = true
			iCurrentAnimId = 1
			anim = moveAnimationTable[iCurrentAnimId]
			_SetUV(a_entity, anim.x, anim.y, anim.z, anim.w)
		end
	else
		if bIsMoving then
			bIsMoving = false
			iCurrentAnimId = 1
			anim = idleAnimationTable[iCurrentAnimId]
			_SetUV(a_entity, anim.x, anim.y, anim.z, anim.w)
		end
	end
	
    _Move(a_entity, vMove)
	
end

function OnDestroy()

	print("OnDestroy")

	moveSpeed = nil
	rotateSpeed = nil
	timeBetweenBullet = nil
	isMoveRight = nil
	lastBullet = nil
end