local sName

function OnStart(a_host, a_entity)
    sName = "SadBox"
end

function OnUpdate(a_host, a_entity, a_dt)

    local ent = _OnTriggerEntityName(a_entity, sName)
    if ent ~= 0 then
        _DestroyEnt(ent)
    end

end