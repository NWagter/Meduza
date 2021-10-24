local moveSpeed
local rotateSpeed

local tCameraSettings

-- W = 87
-- S = 83
-- A = 65
-- D = 68

function OnStart(a_host, a_entity)
    print("Camera Start!")
    moveSpeed = 20
    rotateSpeed = 2
end

function OnUpdate(a_host, a_entity, a_dt)

    x = 0
    y = 0
    z = 0
    yaw = 0

    if _OnKeyDown(65) == 1 then
        x = x - (moveSpeed * a_dt)
    elseif _OnKeyDown(68) == 1 then
        x = x + (moveSpeed * a_dt)
    end   

    if _OnKeyDown(16) == 1 then
        y = y - (moveSpeed * a_dt) 
    elseif _OnKeyDown(32) == 1 then
        y = y + (moveSpeed * a_dt)        
    end

    if _OnKeyDown(87) == 1 then
        z = z + (moveSpeed * a_dt)        
    elseif _OnKeyDown(83) == 1 then
        z = z - (moveSpeed * a_dt)        
    end
      
    if _OnKeyDown(69) == 1 then
        yaw = yaw + (rotateSpeed * a_dt)        
    elseif _OnKeyDown(81) == 1 then
        yaw = yaw - (rotateSpeed * a_dt)        
    end

    _Move(a_entity, x, y ,z)
    _Rotate(a_entity, 0, yaw ,0)
end

function OnStop(a_host, a_entity)
    print("Camera Stop!")
end