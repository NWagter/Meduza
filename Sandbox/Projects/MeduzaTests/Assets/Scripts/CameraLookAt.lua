local sTargetEntity
local eTargetEntity

local tCameraSettings
local vCameraPos

function OnStart(a_host, a_eEntity, a_initTable)
    sTargetEntity = a_initTable.sTargetEntityName
    eTargetEntity = nil

    vCameraPos = _GetLocation(a_eEntity)
end

function OnUpdate(a_host, a_eEntity, a_nDt)

    vTargetPos = vCameraPos

    if eTargetEntity == nil then
        eTargetEntity = _GetEntityByName(sTargetEntity)
    else 
        vTargetPos.x = _GetLocation(eTargetEntity).x
        _LookAt(a_eEntity, vTargetPos)
    end
end

function OnStop(a_host, a_eEntity)

end