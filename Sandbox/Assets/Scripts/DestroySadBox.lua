local left = false
local time = 1

function OnUpdate(a_host, a_entity, a_dt)

    local ent = _OnTriggerEntityName(a_entity, "SadBox")
    if ent ~= 0 then
        _DestroyEnt(ent)
    end

end