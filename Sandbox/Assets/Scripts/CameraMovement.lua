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

    fX = 0
    fY = 0
    fZ = 0
    fYaw = 0

    if _OnKeyDown(65) == 1 then
        fX = fX - (fMoveSpeed * a_fDT)
    elseif _OnKeyDown(68) == 1 then
        fX = fX + (fMoveSpeed * a_fDT)
    end   

    if _OnKeyDown(16) == 1 then
        fY = fY - (fMoveSpeed * a_fDT) 
    elseif _OnKeyDown(32) == 1 then
        fY = fY + (fMoveSpeed * a_fDT)        
    end

    if _OnKeyDown(87) == 1 then
        fZ = fZ + (fMoveSpeed * a_fDT)        
    elseif _OnKeyDown(83) == 1 then
        fZ = fZ - (fMoveSpeed * a_fDT)        
    end
      
    if _OnKeyDown(69) == 1 then
        fYaw = fYaw + (fRotateSpeed * a_fDT)        
    elseif _OnKeyDown(81) == 1 then
        fYaw = fYaw - (fRotateSpeed * a_fDT)        
    end

    _Move(a_entity, fX, fY , fZ)
    _Rotate(a_entity, 0, fYaw ,0)
end

function OnStop(a_host, a_entity)
    print("Camera Stop!")
end