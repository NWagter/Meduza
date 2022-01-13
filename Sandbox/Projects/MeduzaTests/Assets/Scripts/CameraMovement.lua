local nMoveSpeed
local nRotateSpeed

local tCameraSettings

-- W = 87
-- S = 83
-- A = 65
-- D = 68

function OnStart(a_host, a_eEntity)
    print("Camera Start!")
    nMoveSpeed = 20
    nRotateSpeed = 2
end

function OnUpdate(a_host, a_eEntity, a_nDt)

    vMovement = _CreateVector3()
    vRotation = _CreateVector3()

    if _OnKeyDown(65) == 1 then
        vMovement.x = vMovement.x - (nMoveSpeed * a_nDt)
    elseif _OnKeyDown(68) == 1 then
        vMovement.x = vMovement.x + (nMoveSpeed * a_nDt)
    end   

    if _OnKeyDown(16) == 1 then
        vMovement.y = vMovement.y - (nMoveSpeed * a_nDt) 
    elseif _OnKeyDown(32) == 1 then
        vMovement.y = vMovement.y + (nMoveSpeed * a_nDt)        
    end

    if _OnKeyDown(87) == 1 then
        vMovement.z = vMovement.z + (nMoveSpeed * a_nDt)        
    elseif _OnKeyDown(83) == 1 then
        vMovement.z = vMovement.z - (nMoveSpeed * a_nDt)        
    end
      
    if _OnKeyDown(69) == 1 then
        vRotation.y = vRotation.y + (nRotateSpeed * a_nDt)        
    elseif _OnKeyDown(81) == 1 then
        vRotation.y = vRotation.y - (nRotateSpeed * a_nDt)        
    end

    _Move(a_eEntity, vMovement)
    _Rotate(a_eEntity, vRotation)
end

function OnStop(a_host, a_eEntity)

end