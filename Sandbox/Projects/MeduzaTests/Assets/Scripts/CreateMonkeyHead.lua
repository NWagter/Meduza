
function OnStart(a_host, a_eEntity, a_initTable)
    vLocation = _CreateVector3(0,2,10)
    _InstantiatePrefab(a_initTable.MonkeyHeadPrefab, vLocation);
end

function OnUpdate(a_host, a_eEntity, a_nDt)
end

function OnStop(a_host, a_eEntity)
end