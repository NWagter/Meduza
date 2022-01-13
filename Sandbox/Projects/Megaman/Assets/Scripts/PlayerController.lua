local nMoveSpeed

local nTimeBetweenBullet
local nXBulletOffset

local bIsMoveRight
local bIsMoving
local eLastBullet

local nAnimationTime
local nMoveAnimationMultiplier

local nCurrentAnimId
local nMaxMoveAnim
local nMaxIdleAnim

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

function OnStart(a_host, a_eEntity)
    nMoveSpeed = 10
	nTimeBetweenBullet = 0
	eLastBullet = -1
	
	bIsMoveRight = true
	
	nCurrentAnimId = 1
	bIsMoving = false
	nMaxIdleAnim = 2
	nMaxMoveAnim = 6
	nAnimationTime = 0.2
	nMoveAnimationMultiplier = 5
	
	
	anim = tIdleAnimationTable[nCurrentAnimId]
	_SetUV(a_eEntity, anim.x, anim.y, anim.z, anim.w)
	nXBulletOffset = 2
end

function OnUpdate(a_host, a_eEntity, a_nDt)
	
	if nAnimationTime <= 0 then
	
		nAnimationTime = 0.2
		nCurrentAnimId = nCurrentAnimId + 1
		
		if bIsMoving then
		
			if nCurrentAnimId > nMaxMoveAnim then
				nCurrentAnimId = 1
			end
			
			anim = tMoveAnimationTable[nCurrentAnimId]
			_SetUV(a_eEntity, anim.x, anim.y, anim.z, anim.w)
		else			
			if nCurrentAnimId > nMaxIdleAnim then
				nCurrentAnimId = 1
			end
			
			anim = tIdleAnimationTable[nCurrentAnimId]
			_SetUV(a_eEntity, anim.x, anim.y, anim.z, anim.w)
		end
	end

	if bIsMoving then
		nAnimationTime = nAnimationTime - (nMoveAnimationMultiplier * a_nDt)	
	else	
		nAnimationTime = nAnimationTime - a_nDt
	end
	
	if eLastBullet >= 0 then
		if bIsMoveRight then
			_CallFunction(eLastBullet, "BulletScript", "MoveRight", a_eEntity)	
			eLastBullet = -1
		else
			_CallFunction(eLastBullet, "BulletScript", "MoveLeft", a_eEntity)	
			_FlipX(eLastBullet)	
			eLastBullet = -1
		end
	end

	vMove = _CreateVector3()
	
	if nTimeBetweenBullet > 0 then
		nTimeBetweenBullet = nTimeBetweenBullet - a_nDt
	end

	if _OnKeyDown(68) == 1 then
        vMove.x = (nMoveSpeed * a_nDt)   
		if not bIsMoveRight then
			bIsMoveRight = true
			_FlipX(a_eEntity)
		end
    elseif _OnKeyDown(65) == 1 then
        vMove.x = vMove.x -(nMoveSpeed * a_nDt) 
		if bIsMoveRight then
			bIsMoveRight = false
			_FlipX(a_eEntity)
		end 
    end  
	
	vVel = _GetVelocity(a_eEntity)
	
	nY = 15
	nX = 10
	
	if not bIsMoveRight then
		nX = -nX
	end
	
	vForce = _CreateVector3(nX, nY, 0)
	
	if _OnKeyDown(32) == 1 and vVel.y == 0 then
		_ApplyForce(a_eEntity, vForce)
    end	
	
	if (_OnKeyDown(80) == 1 and nTimeBetweenBullet <= 0) then
		vLocation = _GetLocation(a_eEntity)
		
		if bIsMoveRight then
			vLocation.x = vLocation.x + nXBulletOffset
		else
			vLocation.x = vLocation.x - nXBulletOffset			
		end
		
		eLastBullet = _InstantiatePrefab("Assets/Prefab/Megamen/Bullet.prefab", vLocation)		
		nTimeBetweenBullet = 0.5
	end
	
	if vMove.x ~= 0 or vMove.y ~= 0 then
		if not bIsMoving then
		bIsMoving = true
			nCurrentAnimId = 1
			anim = moveAnimationTable[nCurrentAnimId]
			_SetUV(a_eEntity, anim.x, anim.y, anim.z, anim.w)
		end
	else
		if bIsMoving then
			bIsMoving = false
			nCurrentAnimId = 1
			anim = idleAnimationTable[nCurrentAnimId]
			_SetUV(a_eEntity, anim.x, anim.y, anim.z, anim.w)
		end
	end
	
    _Move(a_eEntity, vMove)
	
end

function OnDestroy()

	print("OnDestroy")

	nMoveSpeed = nil
	nRotateSpeed = nil
	nTimeBetweenBullet = nil
	bIsMoveRight = nil
	eLastBullet = nil
end