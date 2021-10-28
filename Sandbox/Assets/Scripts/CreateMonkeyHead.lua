
function OnStart(a_host, a_entity)
    vLocation = _CreateVector3(0,2,10)
    _InstantiatePrefab("Assets/Prefab/MonkeyHead.prefab", vLocation);
end

function OnUpdate(a_host, a_entity, a_fDT)
end

function OnStop(a_host, a_entity)
end