local sName

function OnStart(a_host, a_eEntity)
    sName = "SadBox"
end

function OnUpdate(a_host, a_eEntity, a_nDt)

    local eEnt = _OnTriggerEntityName(a_eEntity, sName)
    if eEnt ~= 0 then
        _DestroyEnt(eEnt)
    end

end