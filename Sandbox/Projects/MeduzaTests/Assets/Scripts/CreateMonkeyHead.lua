
function OnStart(a_host, a_eEntity)
    vLocation = _CreateVector3(0,2,10)
    _InstantiatePrefab("Projects/MeduzaTests/Assets/Prefab/MonkeyHead.prefab", vLocation);
end

function OnUpdate(a_host, a_eEntity, a_nDt)
end

function OnStop(a_host, a_eEntity)
end