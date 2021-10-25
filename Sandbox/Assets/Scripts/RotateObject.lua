local fYRotSpeed = 50

function OnUpdate(a_host, a_entity, a_fDT)

    _Rotate(a_entity, 0, fYRotSpeed * a_fDT, 0)
end