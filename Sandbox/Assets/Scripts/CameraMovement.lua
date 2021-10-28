local fMoveSpeed
local fRotateSpeed

local tCameraSettings

-- W = 87
-- S = 83
-- A = 65
-- D = 68

function OnStart(a_host, a_entity)
    print("Camera Start!")
    fMoveSpeed = 20
    fRotateSpeed = 2
end

function OnUpdate(a_host, a_entity, a_fDT)

    vMovement = _CreateVector3()
    vRotation = _CreateVector3()

    if _OnKeyDown(65) == 1 then
        vMovement.x = vMovement.x - (fMoveSpeed * a_fDT)
    elseif _OnKeyDown(68) == 1 then
        vMovement.x = vMovement.x + (fMoveSpeed * a_fDT)
    end   

    if _OnKeyDown(16) == 1 then
        vMovement.y = vMovement.y - (fMoveSpeed * a_fDT) 
    elseif _OnKeyDown(32) == 1 then
        vMovement.y = vMovement.y + (fMoveSpeed * a_fDT)        
    end

    if _OnKeyDown(87) == 1 then
        vMovement.z = vMovement.z + (fMoveSpeed * a_fDT)        
    elseif _OnKeyDown(83) == 1 then
        vMovement.z = vMovement.z - (fMoveSpeed * a_fDT)        
    end
      
    if _OnKeyDown(69) == 1 then
        vRotation.y = vRotation.y + (fRotateSpeed * a_fDT)        
    elseif _OnKeyDown(81) == 1 then
        vRotation.y = vRotation.y - (fRotateSpeed * a_fDT)        
    end

    _Move(a_entity, vMovement)
    _Rotate(a_entity, vRotation)
end

function OnStop(a_host, a_entity)
    print("Camera Stop!")
end