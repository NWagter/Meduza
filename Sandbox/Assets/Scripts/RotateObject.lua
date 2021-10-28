local fYRotSpeed = 50

function OnUpdate(a_host, a_entity, a_fDT)

    vRotation = _CreateVector3()
    vRotation.y = fYRotSpeed * a_fDT;
    _Rotate(a_entity, vRotation)
end