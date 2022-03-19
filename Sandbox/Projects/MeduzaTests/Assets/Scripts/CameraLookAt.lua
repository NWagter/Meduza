local sTargetEntity
local eTargetEntity

local tCameraSettings
local vCameraPos

function OnStart(a_host, a_eEntity, a_initTable)
    eTargetEntity = a_initTable.eTargetEntity
end

function OnUpdate(a_host, a_eEntity, a_nDt)

    vTargetPos = _GetLocation(a_eEntity)

    if eTargetEntity == nil then
		return
    else 
        vTargetPos.x = _GetLocation(eTargetEntity).x
        vTargetPos.y = vTargetPos.y - _GetLocation(eTargetEntity).y
		
        _LookAt(a_eEntity, vTargetPos)
    end
end

function OnStop(a_host, a_eEntity)

end