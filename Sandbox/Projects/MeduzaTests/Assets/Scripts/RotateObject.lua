local fYRotSpeed = 50

function OnUpdate(a_host, a_eEntity, a_nDt)

    vRotation = _CreateVector3()
    vRotation.y = fYRotSpeed * a_nDt;
    _Rotate(a_eEntity, vRotation)
end